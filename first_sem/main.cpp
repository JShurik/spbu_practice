#include <iostream>
#include "big_int.h"
#include "euclid.h"

using namespace std;

int main()
{
	const char* num1 = "111111101010111101111101111010111001111111111";
	const char* num2 = "101100000011010010011000101111110010000101000110010101000"; //99194853094755496
	const char* num3 = "101100000011010010011000101111110010000101000110010101001"; //99194853094755497
	//const char* num1 = "111111101010111101111101111010111001111111111";
	//const char* num2 = "111111111101111111111110";
	//const char* num3 = "111111111101111111111111";
	big_int* n1 = big_int_get(num1);
	big_int* n2 = big_int_get(num2);
	big_int* n3 = big_int_get(num3);
	cout << "      n1: ";
	big_int_print(n1);
	cout << "      n2: ";
	big_int_print(n2);
	cout << "      n3: ";
	big_int_print(n3);
	cout << endl;
	/*big_int* summ = big_int_add(n1, n2);
	cout << " n1 + n2: ";
	big_int_print(summ);
	big_int* delta = big_int_sub(n1, n2);
	cout << " n1 - n2: ";
	big_int_print(delta);
	//cout << delta->length << endl;
	cout << "    2*n1: ";
	big_int_print(big_int_add(summ, delta));
	big_int* mult = big_int_multi(n1, n2);
	cout << " n1 * n2: ";
	big_int_print(mult); */
	big_int* lsh = big_int_left_shift(n1, 5);
	cout << "n1 << 16: ";
	big_int_print(lsh);
	big_int* rsh = big_int_right_shift(n1,1);
	cout << " n1 >> 1: ";
	big_int_print(rsh); 
	big_int* reminder = big_int_get("0");
	big_int* division = big_int_euclidean_division(n1, n2, reminder);
	cout << endl;
	cout << "n1 / n2: ";
	big_int_print(division); 
	cout << " remind: ";
	big_int_print(reminder);
	cout << endl;
	big_int* mod = big_int_mod_pow(n1, n2, n3);
	cout << "(n1^n2) % n3: ";
	big_int_print(mod);

}
