#include <iostream>
#include <cstdlib>
#include <cmath>
#include <gmpxx.h>
#include <iomanip>

using namespace std;

/* Bernoulli Trials Simulator */
//B: APPLY MONTE CARLO
//You can change these for debugging, but reset them before the deadline
#define MAX_LUCK 10
#define TRIALS 100 //before turning in, reset back to 100 trials
#define FLIPS 40 //40 DEFAULT
#define PERCENT_PER_STAR 1

//Some sample code on how to flip a biased coin. You MUST use this code, and not the normal rand() function
bool coin_flip(mpz_class bias, gmp_randclass &RNG) {
	mpz_class roll = RNG.get_z_range(MAX_LUCK); //Generates a number from 0 to 9
	if (roll < bias) return true;
	return false;
}

mpz_class factorial(mpz_class a) { //Does Factorial
	mpz_class temp;
	if (a <= 1) return 1; //Factorial of <= 1 is 1
	temp = a * factorial(a-1);
	return temp;
}

mpz_class nChoosek(unsigned n, unsigned k) { //Does part of the bernoulli eqtn math
	mpz_class n_factorial = factorial(n);
	mpz_class k_factorial = factorial(k);
	mpz_class nsubk_factorial = factorial(n-k);
	mpz_class result = (n_factorial/(k_factorial*nsubk_factorial));
	return result;
}

string totalHeadsTrial(int count) {//Prints out the # of times you got a certain totals # of heads per Trial
	string totalHeads = ""; 
	for (int i = 0; i < count; i++)
		totalHeads+= "*";
	return totalHeads;
}

int main() {
	//Remember not to modify these prompts, or you'll break the autograder and get no points
	cout << "Please input a random seed: ";
	mpz_class my_seed;
	cin >> my_seed;
	gmp_randclass RNG(gmp_randinit_mt);
	RNG.seed(my_seed);

	//Your luck score controls how likely you are to get a heads on a flip
	//At 0, you have a 0% chance, at 10 you have a 100% chance.
	//By default, it should be 5 for a 50/50 chance.
	//(This is called a "bias" on a coin flip)
	cout << "Please enter your luck score (from 0 to " << MAX_LUCK << "): ";
	mpz_class luck;
	cin >> luck;
	if (luck < 0 || luck > MAX_LUCK) {
		cout << "Bad input.\n";
		exit(1);
	}

	//YOU: Now, you're going to flip a coin FLIPS (default: 40) times, and count how many heads you get
	//You will do this whole process TRIALS (default: 100) times
	int bins[FLIPS+1] = {}; //Holds how many times we get each result, initialized to zero
	//For example, after TRIALS times, bins[20] holds how many times we got exactly 20 heads out of 40 flips
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	for (int i = 0; i < TRIALS; i++){
		int count = 0;
		for (int j = 0; j < FLIPS; j++) {
			bool success = coin_flip(luck, RNG); //Does the coin flip with "Luck" taken into account #bernoulli
			if(success) count++; //Every success = heads + 1
		}

		bins[count] += 1; //Says how many times(represented with *)  you achieved a certain number of heads per trial
	}

	//	Equatoion for expected Probability (n choose k) * p^k * (1-p)^(n-k)
	for (unsigned long int bin = 0; bin <= FLIPS; bin++){
		mpf_class eqtnPt1 = 0; // eqtnPt1 = p^k
		mpf_class eqtnPt2 = 0; // eqtnPt2 = (1-p)^(n-k)
		mpz_class exptProbability; //Expected Probability 
		mpz_class nChooseK = nChoosek(FLIPS, bin);
		mpf_class prob = luck; //Luck is 0-10
		prob = prob * .1; //P is from 0-1 
		mpf_class oneMinusP = 1 - prob; // oneMinusP = (1-p)
		unsigned long int nSubk = (FLIPS-bin); //nSubk = ^(n-k)
		mpf_pow_ui(eqtnPt2.get_mpf_t(),oneMinusP.get_mpf_t(),nSubk); // Sets eqtnPt2 = nSubk^eqtnPt2Pow
		mpf_pow_ui(eqtnPt1.get_mpf_t(), prob.get_mpf_t(), bin); //Sets eqtnPt1 = prob^bin
		exptProbability = 100 * (nChooseK * eqtnPt2 * eqtnPt1); //Times 100 to get a % base 100
		cout <<"Bin " <<  setw(2) << setfill('0') << bin << ": " << setw(2) << setfill('0') << exptProbability << "% vs " << setw(2) << setfill('0') << bins[bin] << "%: " <<totalHeadsTrial(bins[bin]) << endl;; // line not completed.
	}
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	//Here's how you flip a coin.
	//You'll need to put it inside a loop or two to make it work with LOOPS and TRIALS
	bool success = coin_flip(luck, RNG); //The higher your luck, the higher the chance of success


	//YOU: After you have done all 100 coin flips, you will print your results
	//The format is as such:
	// bin number: expected percent vs actual percent: stars equal to the actual percent
	//Example:
	// ...
	// 19: 11% vs 10%: **********
	// 20: 12% vs 15%: ***************
	// 21: 11% vs 13%: *************
	// ...
	//Explanation:
	// The bin number is how many heads came up, which will range from 0 to FLIPS
	// The expected percent is the expected probability, given by (n choose k) * p^k * (1-p)^(n-k)
	// The actual percent is how many actually got rolled (which will rarely match the expected number)
	// 

	return 0;
	
	}
