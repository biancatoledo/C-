//Yep, let's get coding
#include <iostream>
#include <deque>
using namespace std;

int main() {
	while (cin) {
		unsigned char ch;
		unsigned int base = 2;
		deque<int> bitfield;
		cin >> ch;
		for (int i = 0; i < 8; i++) {
			int lastbit = ch % base;
			ch = ch >> 1;
			bitfield.push_front(lastbit);
		}
		for (int i : bitfield) {
			cout << i;
		}
		cout << endl;
	}
}
