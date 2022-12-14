#include "method_gauss.h"

#include "Matrix_public.h"

#define eps 1e-16

#include <iomanip>
#include <cmath>
#include <iostream>


bool inv_check(double**& A, size_t& n){

	int check = 0;

	double** A_save = new double* [n];
	for(size_t i = 0; i < n; ++i){
		A_save[i] = new double [n+1];
	}

	copy_Sys_A_to_B(A, A_save, n);

	check = straight_course(A_save, n);

	if (check == 1){
		return false;
	}
	else{
		return true;
	}

}

int method_gauss(double**& A, size_t& n, double*& x) {

	int check = 0;

	double** A_save = new double* [n];
	for(size_t i = 0; i < n; ++i){
		A_save[i] = new double [n+1];
	}

	copy_Sys_A_to_B(A, A_save, n);

	check = straight_course(A_save, n);
	
	int oper = 0;

	if (check != -1){
		oper += check;
		oper += reverse_course(A_save, n, x);	
	}	
	else if(check == -1)
		return 1;

	for (size_t j = 0; j < n; ++j){
        delete [] A_save[j];
    }
    delete [] A_save;

	return oper;
}

//---subfunctions1---//

int straight_course(double**& A, size_t& n) {
	//printMatrix(A, n);
	int oper = 0;
	major_element(A, n);
	//printMatrix(A, n);
	for (size_t k = 0; k < n; ++k) {

		if (fabs(A[k][k]) < eps)
		{
			cout << "\nMatrix is singular (non-invertible)\n";
			return -1;

		}	
		oper += remove_MatrixColumnElements_UnderLine(k, A, n);

		//print_Sys_Matrix(A, n);
	}
	return oper;

}

int reverse_course(double**& A, size_t& n, double*& x) {

	int oper = 0;
	for (size_t i = 0; i < n; ++i) {
		//normalize_Sys_MatrixLine(i, A, n);
		x[i] = A[i][n];
	}
	x[n - 1] /= A[n - 1][n - 1];
	++oper;
	for (size_t i = 0; i <= n - 2; ++i) {

		for (size_t j = n - 2 - i + 1; j < n; ++j) {
			x[n - 2 - i] -= x[j] * A[n - 2 - i][j];
			oper += 1;
		}
		x[n - 2 - i] /= A[n - 2 - i][n - 2 - i];
		oper += 1;

	}

	check_vector_zero(x, n);
	
	return oper;
}

//---subfunctions2---//

int major_element(double**& A, size_t& n) {

	size_t i_max = 0;

	for (size_t k = 0; k < n; ++k) {
		i_max = k;
		for (size_t i = k; i < n; ++i) {
			if (fabs(fabs(A[i_max][k]) - fabs(A[i][k])) > eps) {
				if (fabs(A[i_max][k]) < fabs(A[i][k])) {
					i_max = i;
				}

			}

		}
		swap(A[i_max], A[k]);
	}
	return 0;
}

int remove_MatrixColumnElements_UnderLine(size_t& k, double**& A, size_t& n) {

	double tmp1 = 0.0;
	int oper = 0;
	for (size_t i = k + 1; i < n; ++i) {


		if (fabs(A[i][k]) > eps) {

			tmp1 = A[i][k]/A[k][k];
			++oper;

			for (size_t j = k; j < n + 1; ++j) {

				A[i][j] -= A[k][j] * tmp1;
				++oper;
				//printMatrix(A, n);
				//solving -0 problem
				if (fabs(A[i][j]) < eps) {
					A[i][j] *= (1 / A[i][j] > 0) ? (1) : (-1);
				}
			}
		}
		else {
			A[i][k] = 0.0;
			if (fabs(A[i][k]) < eps) {
				A[i][k] *= (1 / A[i][k] > 0) ? (1) : (-1);
			};
		}

	}

	return oper;
}