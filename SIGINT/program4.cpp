/*
Name: Bianca Toledo
Date: 3/12/2018
Class: Systems Programming [CSCI 440]
Description: Integer addition program that can be interrupted by a SIGINT written in C++ on Ubuntu VM

*/

#include <iostream>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

volatile sig_atomic_t flag = 0;

void sigintHandler(int sig_num) {
	signal(SIGINT, sigintHandler);
	printf("\nCannot be terminated using Ctrl+C.\nPlease enter a large integer: \n");
	fflush(stdout);

}

void sigintHandlerExit(int sig_num) {
	printf("Caught signal %d. User terminated addition. Program exiting.\n", sig_num);
	exit(sig_num);	
}
int main() {
	
	int num, sum = 1;
	
	while(1) {

		signal(SIGINT, sigintHandler);	
		//prompt user for large positive integer
		cout << "Please enter a large integer: ";
		cin >> num;

		//add program from 1 until integer is reached
	
		signal(SIGINT, sigintHandlerExit);
		for (int i = 0; i < num; i++) {
			cout << sum << endl; 
			sum++;
		}
		sum = 1;
	}

//ASSIGNMENT DIRECTIONS 
	//program should not be interrupted by signals including SIGINT when waiting for integer to be entered by user
		//however it can be interrupted by SIGINT when adding

	// when SIGINT is caught it should be handled by a signal handler that will print whatever has been done at the time when the program was interrupted by the signal and terminate the program

	//if addition is complted without interruption
		//1. repeat process by prompting new large integer
		//2. calculate the summation for the integer
		//3. reinitialize the summation variable to 0 before process starts over

	return 0;
}
