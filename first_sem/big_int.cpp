#include <iostream>
#include "big_int.h"

#define CHANGE_SIGN(n1, n2, function) big_int* n3 = big_int_change_sgn(n1); \
					   big_int* t = function(n2, n3); \
					   big_int_free(n3); \
					   return t;

#define CLEAR_BIG_INT(n) n->number = (unsigned char*)realloc(n->number, 1); \
						 if (n->number) n->number[0] = 0; \
						 n->length = 1; n->sgn = 1; 


const int NUM_LEN = 8;
const int NUM_MAX = 0xFF;

//Done
big_int* big_int_get(const char* num_bi) {
	int num_length = strlen(num_bi) - (num_bi[0] == '-');
	int length = (num_length / NUM_LEN) + (int)((num_length % NUM_LEN) != 0);
	big_int* result = (big_int*)malloc(sizeof(big_int));
	if (result) {
		result->length = length;
		if (num_bi[0] == '-')
			result->sgn = -1;
		else
			result->sgn = 1;
		result->number = (unsigned char*)malloc(length);
		int index = strlen(num_bi) - 1;
		for (int i = 0; i < length; ++i)
		{
			int temp = 0;
			for (int j = 0; j < NUM_LEN; ++j)
			{
				temp += ((int)num_bi[index] - (int)('0')) << j;
				--index;
				if (index < 0 + int(result->sgn == -1)) break;
			}
			if (result->number)
				result->number[i] = (unsigned char)(temp);
		}
	}
	return result;
}
big_int* big_int_zero() {
	big_int* zero = (big_int*)malloc(sizeof(big_int));
	zero->length = 1;
	zero->sgn = 1;
	zero->number = (unsigned char*)malloc(sizeof(unsigned char));
	zero->number[0] = 0;
	return zero;
}
void big_int_print(big_int* n) {
	if ((n->sgn == -1) && (n->length == 1 ? (int)n->number[0] != 0 : true))
		std::cout << "-";
	for (int i = n->length - 1; i >= 0; --i)
	{
		int index = NUM_LEN - 1;
		int temp = n->number[i];
		int line[NUM_LEN] = { 0 };
		while (temp > 0)
		{
			line[index] = temp & 1;
			temp >>= 1;
			--index;
		}
		int t = 0;
		if (i == n->length - 1)
			while (line[t] == 0) { ++t; /*std::cout << " ";*/ }
		for (int j = t; j < NUM_LEN; j++)
			std::cout << line[j];
		std::cout << " ";
	}
	if (n->length == 1 && n->number[0] == (unsigned char)(0))
		std::cout << 0;
	std::cout << std::endl;
}
void big_int_free(big_int* n) {
	free(n->number);
	free(n);
}
void big_int_assign(big_int* n1, const big_int* n2) {
	CLEAR_BIG_INT(n1)
	n1->number = (unsigned char*)realloc(n1->number, n2->length);
	n1->length = n2->length;
	n1->sgn = n2->sgn;
	memcpy((void*)n1->number, (void*)n2->number, n2->length);
}
big_int* big_int_change_sgn(const big_int* n) {
	big_int* result = big_int_get("0");
	big_int_assign(result, n);
	result->sgn = 1 * int(result->sgn == -1) - 1 * int(result->sgn == 1);
	return result;
}
big_int* big_int_add(const big_int* n1, const big_int* n2) { //n1 + n2
	if (n1->sgn == n2->sgn) {
		if (n1->length >= n2->length) {
			big_int* result = (big_int*)malloc(sizeof(big_int));
			result->sgn = n1->sgn;
			if (result) {
				result->length = n1->length;
				result->number = (unsigned char*)malloc(result->length);
				int delta = 0;
				for (int i = 0; i < n2->length; ++i) {
					int temp = int(n1->number[i] + n2->number[i]) + delta;
					if (temp > NUM_MAX) {
						delta = 1;
						result->number[i] = (unsigned char)(temp - NUM_MAX - 1);
					}
					else {
						delta = 0;
						result->number[i] = (unsigned char)(temp);
					}
				}
				for (int i = n2->length; i < n1->length; ++i) {
					int temp = int(n1->number[i]) + delta;
					if (temp > NUM_MAX) {
						delta = 1;
						result->number[i] = (unsigned char)(temp - NUM_MAX - 1);
					}
					else {
						delta = 0;
						result->number[i] = (unsigned char)(temp);
					}
				}
				if (delta == 1) {
					result->length++;
					result->number = (unsigned char*)realloc(result->number, result->length);
					result->number[n1->length] = (unsigned char)(delta);
				}
			}
			return result;
		}
		else {
			return big_int_add(n2, n1);
		}
	}
	else {
		if (n1->sgn == -1) {
			CHANGE_SIGN(n1, n2, big_int_sub);
		}
		else {
			CHANGE_SIGN(n2, n1, big_int_sub);
		}
	}
}
int big_int_abs_compare(const big_int* n1, const big_int* n2) {  //if n1>n2 : 1 if n1==n2 : 0 else : -1
	if (n1->length > n2->length)
		return 1;
	else if (n1->length == n2->length) {
		int temp = 0;
		for (int i = n1->length - 1; i >= 0; --i) {
			if (n1->number[i] > n2->number[i])
				return 1;
			else if (n1->number[i] == n2->number[i])
				temp++;
			else
				return -1;
		}
		if (temp == n1->length)
			return 0;
	}
	return -1;
}
big_int* big_int_sub(const big_int* n1, const big_int* n2) { //n1 - n2
	if ((n1->sgn == n2->sgn) && (big_int_abs_compare(n1, n2) + 1)) {
		big_int* result = big_int_get("0");
		if (n1->length >= n2->length) {
			big_int_assign(result, n1);
			int delt = 0;
			for (int i = 0; i < result->length; ++i)
			{
				int temp = 0;
				if (i < n2->length) {
					temp = int(result->number[i] - n2->number[i]) + delt;
					if (temp < 0 && (int)n2->number[i] != 0) {
						delt = -1;
						result->number[i] = (unsigned char)
							((NUM_MAX + 1 + temp) * (i + 1 < result->length) +
								temp * (-1 * (i + 1 == result->length)));
					}
					else {
						delt = 0;
						result->number[i] = (unsigned char)(temp);
					}
				}
				else {
					if (delt == -1) {
						temp = int(result->number[i]) + delt;
						if (temp < 0)
							result->number[i] = (unsigned char)
							(((NUM_MAX + 1 + temp) * (i + 1 < result->length) +
								temp * (-1 * (i + 1 == result->length))) * (temp != 0));
						else {
							result->number[i] = (unsigned char)(temp);
							delt = 0;
						}
					}
				}
			}
			for (int i = result->length - 1; i > 0; --i) {
				if (result->number[i] == (unsigned char)(0)) {
					result->length--;
				}
				else
					break;
			}
			result->number = (unsigned char*)realloc(result->number, result->length);
			if (delt == -1) return big_int_change_sgn(result);
			return result;
		}
	}
	else if (big_int_abs_compare(n2, n1)) {
		big_int* copy1 = big_int_change_sgn(n1), * copy2 = big_int_change_sgn(n2);
		big_int* result = big_int_sub(copy2, copy1);
		big_int_free(copy1);
		big_int_free(copy2);
		return result;
	}
	else
		if (n1->sgn == -1) {
			CHANGE_SIGN(n2, n1, big_int_add)
		}
		else {
			CHANGE_SIGN(n2, n1, big_int_add)
		}
}


//in work

big_int* big_int_multi(const big_int* n1, const big_int* n2) { //n1 * n2
	big_int* result = big_int_get("0");
	result->sgn = n1->sgn * n2->sgn;
	for (int i = 0; i < n1->length; ++i) {
		big_int* temp1 = (big_int*)malloc(sizeof(big_int));
		if (temp1) {
			temp1->sgn = 1;
			temp1->length = n2->length + i; //temp1->sgn = 1;
			temp1->number = (unsigned char*)malloc(n2->length + i);
			int temp = 0, delta = 0;
			for (int j = 0; j < i; ++j)
				temp1->number[j] = (unsigned char)(0);
			for (int j = 0; j < n2->length; ++j) {
				temp = (int)(n1->number[i]) * (int)(n2->number[j]) + delta;
				delta = 0;
				while (temp > NUM_MAX) {
					delta++;
					temp -= (NUM_MAX + 1);
				}
				temp1->number[j + i] = (unsigned char)(temp);
			}
			if (delta > 0) {
				temp1->length++;
				temp1->number = (unsigned char*)realloc(temp1->number, temp1->length);
				temp1->number[temp1->length - 1] = (unsigned char)delta;
			}
			//big_int* summ = big_int_get("0");
			//big_int_assign(summ, big_int_add(result, temp1));
			//big_int_assign(result, summ);
			big_int_assign(result, big_int_add(result, temp1));

			//big_int_print(big_int_add(result, temp1));
			//big_int_free(summ);
			big_int_free(temp1);
		}
	}
	return result;
}

big_int* big_int_left_shift(const big_int* n1, int n2) { //n1 << n2
	big_int* result = big_int_get("0");
	if (big_int_abs_compare(result, n1) == 0)
		return result;
	int r = n2 % NUM_LEN;
	n2 /= NUM_LEN;
	result->sgn = n1->sgn;
	result->length = n2 + n1->length;
	result->number = (unsigned char*)calloc(result->length, sizeof(unsigned char));
	memcpy((void*)(result->number+n2), (void*)n1->number, n1->length);
	for (int i = 0; i < r; ++i) {
		int transf = 0, temp = (int)result->number[0] << 1;
		for (int j = 0; j < result->length; ++j) {
			transf = (temp & (NUM_MAX+1))>>NUM_LEN;
			result->number[j] = temp;// % (2 << NUM_LEN);
			if (j + 1 < result->length) 
				temp = ((int)result->number[j + 1] << 1) | transf;
		}
		if (transf) {
			result->length++;
			result->number = (unsigned char*)realloc(result->number, result->length);
			result->number[result->length - 1] = (unsigned char)transf;
		}
	}
	return result;
}

big_int* big_int_right_shift(const big_int* n1, int step) { //n1 >> n2
	big_int* result = big_int_get("0");
	int r = step % NUM_LEN;
	step /= NUM_LEN;
	if (step >= n1->length)
		return result;
	result->sgn = n1->sgn;
	result->length = n1->length - step;
	memcpy((void*)result->number, (void*)(n1->number+step), result->length);
	for (int i = 0; i < r; ++i) {
		int transf = 0, temp = 0;
		for (int j = 0; j < result->length; ++j) {
			temp = (int)result->number[j] >> 1;
			if (j + 1 < result->length)
				transf = ((int)result->number[j + 1]) & 1;
			else
				transf = 0;
			temp = temp + transf * (1 << (NUM_LEN - 1));
			result->number[j] = (temp | transf * (1 << (NUM_LEN - 1)));
		}
		if (result->number[result->length-1] == 0) {
			if (result->length == 1) 
				return result;
			--result->length;
			unsigned char* temp_int = (unsigned char*)malloc(sizeof(unsigned char)*result->length);
			memcpy((void*)temp_int, (void*)result->number, result->length);
			result->number = (unsigned char*)realloc(temp_int, result->length);
			//free(temp_int);
		}
	}
	return result;
}

big_int* big_int_euclidean_division(const big_int* n1, const big_int* n2, big_int* reminder) { 
	// n1 = result * n2 + r || result = (n1 / n2)
	CLEAR_BIG_INT(reminder) //clear reminder
	big_int* result = big_int_get("0");
	if (big_int_abs_compare(result, n1) == 0) {
		return result;
	}
	if (big_int_abs_compare(result, n2) == 0) {
		//std::cout << "Division by zero";
		big_int_free(result);
		return NULL;
	}
	result->sgn = n1->sgn*n2->sgn; //позже решить вопрос со знаком в процессе алгоритма
	if (big_int_abs_compare(n1, n2) == 1) { //n1 > n2	
		int index = 1;
		while (big_int_abs_compare(n2, reminder) == 1) {
			big_int_assign(reminder, big_int_left_shift(reminder, NUM_LEN));
			reminder->number[0] = n1->number[n1->length - index];
			index++;
		}
		for (int i = index; i <= n1->length; ++i) {
			int digit = 0;
			while (big_int_abs_compare(reminder, n2)+1) {
				++digit;
				big_int_assign(reminder, big_int_sub(reminder, n2));
			}
			result->number[0] = digit;
			big_int_assign(result, big_int_left_shift(result, NUM_LEN));
			big_int_assign(reminder, big_int_left_shift(reminder, NUM_LEN));
			reminder->number[0] = n1->number[n1->length - i];
		}
		int digit = 0;
		while (big_int_abs_compare(reminder, n2) + 1) {
			++digit;
			big_int_assign(reminder, big_int_sub(reminder, n2));
		}
		result->number[0] = (unsigned char)digit;
	}
	else if (big_int_abs_compare(n1, n2) == -1) { //n1 < n2
		big_int_assign(reminder, n1);
	}
	else { //n1 == n2
		big_int_assign(reminder, big_int_get("0"));
		big_int_assign(result, big_int_get("1"));
	}
	return result;
}

big_int* big_int_mod_pow(big_int* x, big_int* y, const big_int* p) {
	const big_int* zero = big_int_zero();
	big_int* result = big_int_get("1");
	while (big_int_abs_compare(y, zero)) {
		big_int* t = big_int_zero();
		if ((int)y->number[0] & 1)
		{
			big_int_assign(result, big_int_multi(result, x));
			big_int_euclidean_division(result, p, t);
			big_int_assign(result, t);
		}
		big_int_assign(x, big_int_multi(x, x));
		CLEAR_BIG_INT(t);
		big_int_euclidean_division(x, p, t);
		big_int_assign(x, t);
		big_int_assign(y, big_int_right_shift(y, 1));
		big_int_free(t);
	}
	big_int* t = big_int_zero();
	big_int_euclidean_division(result, p, t);
	big_int_assign(result, t);
	big_int_free(t);
	return result;
}