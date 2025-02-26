#include <iostream>
#include "Matrix.h"

int main()
{
	Matrix matrix_0(3, 3);
	matrix_0.FillByRandom();

	matrix_0.Print();

	std::cout << "\n\n---------------------------------------------------------------------------\n\n";

	Matrix matrix_1(3,3);
	matrix_1 = matrix_0; 

	matrix_1.Print();


	return 0;
}