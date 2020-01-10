#include <iostream>
#include <cstdlib>
#include <cmath>
#include <gmpxx.h>
using namespace std;

/* Bernoulli Trials Simulator */
//MONTE CARLO
#define MAX_LUCK 10
#define TRIALS 100 
#define FLIPS 40
#define PERCENT_PER_STAR 1

// below flips a biased coin. besides rand()
bool coin_flip(mpz_class bias, gmp_randclass &RNG) {
	mpz_class roll = RNG.get_z_range(MAX_LUCK); //Generates a number from 0 to 9
	if (roll < bias) return true;
	return false;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
mpz_class fact(mpz_class x) {
	mpz_class temp;
	if (x<=1) return 1;
	temp = x * fact(x-1);
	return temp;
}

mpz_class nChoosek(unsigned n, unsigned k) {
	mpz_class n_fact = fact(n);
	mpz_class k_fact = fact(k);
	mpz_class nsubk_fact - fact(n-k);
	mpz_class result = (n_fact/(k_fact*nsubk_fact));
	return result;
}
string asterisk(int count) {
	string retval = "";
	for (int z = 0; z < count; z++)
		retval+= "*"l
	return retval;
}
int main() {
	cout << "Please input a random seed: ";
	mpz_class my_seed;
	cin >> my_seed;
	gmp_randclass RNG(gmp_randinit_mt);
	RNG.seed(my_seed);

	//luck score controls how likely you are to get a heads on a flip
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


	int bins[FLIPS+1] = {}; //Holds how many times we get each result, initialized to zero
	//For example, after TRIALS times, bins[20] holds how many times we got exactly 20 heads out of 40 flips
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	for (int i = 0; i < TRIALS; i++){
		int count = 0;
		for (int j = 0; j < FLIPS; j++) {
			bool success = coin_flip(luck, RNG);
			if(success) count++;
		}
		bins[count] += 1;
	}
	for (unsigned long int bin = 0; bin <= FLIPS; bin++){
		mpz_class nChk = nChoosek(FLIPS, bin);
		mpf_class p = luck;
		p = p * .1;
		mpf_class oneSubp = 1 - p;
		unsigned long int nSubk = (FLIPS-bin);
		mpf_class reg_1 =0;
		mpf_pow_ui(reg_1.get_mpf_t(), p.get_mpf_t(), bin);
		mpz_class total;
		total=100 * (nChk * reg_1 * reg_2);
		cout << "Bin " << setw(2) << setfill('0') << bin << ": " << setw(2) << asterisk(bins[bin]); // line not completed.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~


	bool success = coin_flip(luck, RNG); 

	return 0;

