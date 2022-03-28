#include <iostream>
#include "calculator.h"
#include "poly.h"
#include "trees.h"

using namespace std;

int main() 
{
	char* str = (char*)malloc(sizeof(char*));
	char* str2 = (char*)malloc(sizeof(char*));

	/*printf("Enter expression: ");
	fgets(str, 256, stdin);
	char* pol_form = shuting_yard(str);
	int res = calculation(pol_form);
	cout << pol_form << endl;
	cout << res << endl;*/

	/*cout << "Enter polynom: ";
	fgets(str, 256, stdin);
	exeption ex = { 0, E0 };
	poly* poly1 = poly_get(str, &ex);
	if (poly1 != NULL) poly_print(poly1); else {
		print_exeption(&ex);
	}
	printf("\n");
	cout << "Enter polynom: ";
	fgets(str2, 256, stdin);
	poly* poly2 = poly_get(str2, &ex);
	if (poly2 != NULL) poly_print(poly2);
	printf("\n");
	printf("Summ: ");
	poly_print(poly_add(poly1, poly2));
	printf("Multy: ");
	poly_print(poly_multy(poly1, poly2));*/

	printf("Enter eleemnts: ");
	fgets(str, 256, stdin);
	tree_print(tree_sort(str));
}