#include <iostream>
#include <sstream>
#include <vector>
#include <cctype>
#include <cstdlib>
using namespace std;

void uppercaseify(string &str) {
	for (char &ch : str) ch = toupper(ch);
}

void die() {
	cout << "Invalid Input!\n";
	exit (EXIT_FAILURE);
}

class Inventory {
		vector<string> cars;
		string name;
	public:
		Inventory (string new_name) {
			name = new_name;
			uppercaseify(new_name);
			if (name != new_name) die();
		}
		bool is_in(string search) {
			for (string car : cars)
				if (car==search) return true;
			return false;
	}
		void insert(string new_car) {
			string temp = new_car;
			uppercaseify(temp);
			if (temp != new_car) die();
			if (is_in(new_car)) return; //Don't allow duplicates
			cars.push_back(new_car);
		}

		Inventory intersect(const Inventory &other) {
			Inventory retval(name + " INTERSECT " + other.name);
			for (string car : cars)
					for (string other_car : other.cars) //for each loop (are we going through 
						if (car == other_car)
							retval.insert(car);
			return retval;
		}

		Inventory unionize (const Inventory &other) {
			Inventory retval (name + " UNION " + other.name);
			for (string car: cars)
				retval.insert(car);
			for (string other_car : other.cars)
				retval.insert(other_car);
			return retval;
		}
		Inventory in (const Inventory &other) {
			Inventory retval(name);
			for (string car : cars) 
				retval.insert(car);
			for (string other_car : other.cars)
				retval.insert (other_car);
			return retval;
		}
		int size(){
			return cars.size();
		}
		string get_name () {
			return name;
		}
		friend istream& operator>> (istream &ins, Inventory &other);
		friend ostream& operator<< (ostream &outs, Inventory &other);
}; // End of Inventory
int count = 0;
class SuperSet {
	vector<Inventory> set;
	public:
	void insert(Inventory new_inv) {
		set.push_back(new_inv);
	}
	//It will return the inventory matching name
	Inventory &search(string name) {
		for (Inventory &inv : set)
			if (inv.get_name() == name)
				return inv;
			cout << "NO MATCH\n";
			die();
		//	return Inventory("NO MATCH");
		}
		bool searchtable(string name) {
			for (Inventory inv : set)
				if (inv.get_name() == name)
					return true;
			else false;
		}
		int special() {
			int counter = 0;
			Inventory booger("BOOGIE");
			for (Inventory inv : set) {
				Inventory &z = inv;
				booger = booger.in(z);
			}
			counter = booger.size();
			return counter;
			}

		void print_all() {
			for (Inventory inv : set)
				//Tally up the count of all cars here
				cout << inv.get_name() << ": " << inv;

		//Print out the count here
		if (count == 0) cout<<endl;
		cout<<count<<endl;
		}
		void poset() {
			//Do partial ordering of the sets here
		}
};

SuperSet superduperset; 

int main() {
	string command, value, id1, id2;

	while(true) {
		string temp;
		getline (cin, temp);
		if (cin.eof()) break;
		istringstream input(temp);
		input >> command;
		if (command == "CREATE") {
			input >> command;
			if (command =="TABLE") {
				input >> id1;
				if (superduperset.searchtable(id1)) die(); //if it has a duplicate
				Inventory table(id1);
				superduperset.insert(table);
			}
		if (command != "TABLE") die();
		} // the end of the create table section
	
		else if (command == "INSERT") {
			input >> command;
			if (command == "INTO") {
				input >> id1;
				if (superduperset.searchtable(id1)) {
					Inventory &table = superduperset.search(id1);
					input >> command;
					if (command == "VALUES") {
						ws(input);
						getline(input, value);
						istringstream val_stream(value);
						val_stream >> table;
					}
					if (command != "VALUES") die();
					}
				if (!superduperset.searchtable(id1)) die();
				}
			else if (command != "INTO") die();
			}//END OF INSERT SECTION
		else if (command == "SELECT")
		{
			input >> command;
			string temp2 = command;
			uppercaseify(temp2);

			if (command == "FROM") {
				input >> id1;
				if (superduperset.searchtable(id1)) {
					Inventory rikka = superduperset.search(id1);
					input >> command;

					if (command == "UNION") {
					input >> id2;
					if (superduperset.searchtable(id2)) {
						Inventory cloud = superduperset.search(id2);
						Inventory lulu = rikka.unionize(cloud);
						cout << lulu;
					}
					else die();
					}

				else if (command !="UNION") die();
				}
				else die();
			}
			else if (command == "*") {
				input >> command;
				
				if (command == "FROM") {
					input >> command;
					if (command == "*") {
						count = superduperset.special();
						superduperset.print_all();
					}
					else if (superduperset.searchtable(command)) {
						Inventory rikka = superduperset.search(command);
						input >> command;
						if (command == "INNER") {
							input >> command;
							if (command == "JOIN") {
							input >> id2;
							
							if (superduperset.searchtable(id2)) {
								Inventory cloud = superduperset.search(id2);
								Inventory lulu = rikka.intersect(cloud);

								cout << lulu;
							}
							else if (!superduperset.searchtable(id1)) die();
							}
							else if (command!= "JOIN") die();
						}
						else if (command != "INNER") die();
					}
					else if (!superduperset.searchtable(command)) die();
				}
				else if (command !="FROM") die();
			}
			else if (command != "*") die();
	}
else return 0;
}
}
istream& operator>> (istream &ins, Inventory &other) {
	string temp;
	getline(ins,temp);
	istringstream input(temp); //turns list separated by commas into a string
	while (input) {
		string car;
		getline(input, car, ','); // skips whitespace
		if (superduperset.searchtable(car)) {
			Inventory z = superduperset.search(car);
			if (car !=other.name) other = other.in(z);
			else die;
		}
		if (car.length() <=0) break;
		if (!superduperset.searchtable(car))
			other.insert(car);
	}
	return ins;
}

ostream& operator << (ostream &outs, Inventory &other) {
	for (int i=0; i < other.size(); i++) {
		outs << other.cars.at(i);
		if (i != other.size() -1) outs << ", ";
		else outs << endl;
	}
	return outs;
}


