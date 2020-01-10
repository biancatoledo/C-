#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

using namespace std;

void handle_alarm(int sig) {

}

int main() {

	struct sigaction handle_sigalrm;

	handle_sigalrm.sa_flags = 0;
	handle_sigalrm.sa_handler = handle_alarm;

	sigemptyset(&handle_sigalrm.sa_mask);
	sigaction(SIGALRM, &handle_sigalrm, NULL);	
			
	clock_t start, end;
	int counter = 0, max = 1000000, divby2=0, temp=0;
	double cpu_time_used, new_cpu=0;

	while(1) {
		start = clock();
		for (int i = 0; i < max; i++){
			counter++;
		// if 2 seconds have passed interrupt loop with raise(SIGALRM);
			if (divby2 % 2 == 0 && temp!=divby2 && divby2!=0) {
				raise(SIGALRM);
				cout << "CPU Time Used: " << new_cpu << endl;
				temp = divby2;
			}
		}
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		new_cpu+=cpu_time_used;
		divby2 = new_cpu;

/*
		cout << "CPU Time Used: " << cpu_time_used << endl
		<< "Counter: "<< counter << endl;
*/
		counter = 0;	

		srand(time(NULL)); // initialize random seed

		long long generator = rand() % (2 + 1) ; // sets range for rand with max 2 inclusive of 2 (0-2)
		
//		cout << "Randomly generated number: " <<  generator << endl;

		if (generator == 0) max = 1000000;		
		if (generator == 1) max = 2000000;
		if (generator == 2) max = 3000000;

//		cout << "New Max: " << max << endl;	
	}
}
