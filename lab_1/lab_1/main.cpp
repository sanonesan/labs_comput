#include <iostream>

#include "Matrix_public.h"
#include "method_gauss.h"
#include "QR_method.h"
#include <clocale>

using namespace std;



int main(int args, char** argv){

	setlocale(LC_ALL, "Rus");


	size_t n; //vector size
	//string path = "C:\\Code\\labs_comput\\lab_1\\input.txt";
	//string path_dis = "C:\\Code\\labs_comput\\lab_1\\input_disturbed.txt";

	string path = "C:\\Code\\labs_comput\\lab_1\\P_DATA6.txt";
	string path_dis = "C:\\Code\\labs_comput\\lab_1\\P_DATA6_D.txt";

	double** A = readMatrixFromFile(path, n); //Matrix A|b of sys Ax=b
	
	cout << "--------------------------------\n";
	cout << "--------------------------------\n";

	cout << "System:\n";

	print_Sys_Matrix(A, n);

	double* x = new double [n]; //Answer for: Ax=b or QRx=b
	double* x_save = new double[n];

	cout << "\nGauss-method:\n";


	int check = method_gauss(A, n, x);


	if (check == 0) {
		print_Sys_Matrix(A, n);
		cout << "Result: \n";
		print_Vector(x, n);		

		for (size_t i = 0; i < n; ++i)
			x_save[i] = x[i];
	}


	double** Q = new double* [n];
	double** R = new double* [n];
	for (size_t j = 0; j < n; ++j) {
		Q[j] = new double[n];
		R[j] = new double[n];
	}
		

	A = readMatrixFromFile(path, n);
	cout << "--------------------------------\n";
	cout << "--------------------------------\n";

	cout << "\nSystem:\n";

	print_Sys_Matrix(A,n);

	cout << "\nQR-method:\n";
	check = QR_method_find_Q_and_R(
		Q, 
		R, 
		A, n, x);
	if (check == 0) {
		print_Sys_Matrix(A, n);
		cout << "Q: \n";
		print_Matrix(Q, n);
		cout << "R: \n";
		print_Matrix(R, n);

		cout << "Result: \n";
		print_Vector(x, n);
	}

	A = readMatrixFromFile(path, n);

	cout << "--------------------------------\n";
	cout << "--------------------------------\n";

	cout << "\n\n��������� �������: \n";
	print_Vector(x, n);
	cout << "\n �������: \n";

	double dis_1, dis_inf; 
	discrepancy(A, x, dis_1, n, 1);
	discrepancy(A, x, dis_inf, n, 0);

	cout << "  norm_1: " << dis_1 << "\n" << "norm_inf: " << dis_inf << "\n\n";
	cout << "������ �������� ����� ���������������: \n";

	double cond1 = 0.0, condinf = 0.0;
	cond_matrix(A, cond1, n, 1);
	//cout << "a: \n";
	cond_matrix(A, condinf, n, 0);



	//cout << "a: \n";

	cout << "  norm_1: " << cond1 << "\n" << "norm_inf: " << condinf << "\n";
	
	cout << "\n\n������� ������� � ����������� ������ ������: \n";



	A = readMatrixFromFile(path_dis, n); //Matrix A|b of sys Ax=b

	cout << "--------------------------------\n";
	cout << "--------------------------------\n";

	cout << "System:\n";

	print_Sys_Matrix(A, n);

	


	cout << "\nGauss-method:\n";


	check = method_gauss(A, n, x);


	if (check == 0) {
		print_Sys_Matrix(A, n);
		cout << "Result: \n";
		print_Vector(x, n);
	}


	double** A_save = readMatrixFromFile(path, n);

	A = readMatrixFromFile(path_dis, n);
	cout << "--------------------------------\n";
	cout << "--------------------------------\n";

	cout << "\nSystem:\n";

	print_Sys_Matrix(A, n);

	cout << "\nQR-method:\n";
	check = QR_method_find_Q_and_R(
		Q,
		R,
		A, n, x);
	if (check == 0) {
		print_Sys_Matrix(A, n);
		cout << "Q: \n";
		print_Matrix(Q, n);
		cout << "R: \n";
		print_Matrix(R, n);

		cout << "Result: \n";
		print_Vector(x, n);
	}

	A = readMatrixFromFile(path_dis, n);

	cout << "--------------------------------\n";
	cout << "--------------------------------\n";

	cout << "\n\n��������� �������: \n";
	print_Vector(x, n);
	cout << "\n �������: \n";
	
	discrepancy(A, x, dis_1, n, 1);
	discrepancy(A, x, dis_inf, n, 0);
	cout << "  norm_1: " << dis_1 << "\n" << "norm_inf: " << dis_inf << "\n\n";
	cout << "������ �������� ����� ���������������: \n";
	
	cond_matrix(A, cond1, n, 1);
	cond_matrix(A, condinf, n, 0);
	
	cout << "  norm_1: " << cond1 << "\n" << "norm_inf: " << condinf << "\n\n";


	double delta_x = 0.0, delta_b = 0.0;

	vector_valuation(x_save, x, delta_x, n, 1);
	vector_valuation_Sys(A_save, A, delta_b, n, 1);

	cout << "������ ����� ���������������: \n";
	cout << "  norm_1: delta_x / delta_b = " << delta_x << " / " << delta_b  << " = " << delta_x / delta_b << endl;

	vector_valuation(x_save, x, delta_x, n, 0);
	vector_valuation_Sys(A_save, A, delta_b, n, 0);

	cout << "norm_inf: delta_x / delta_b = " << delta_x << " / " << delta_b << " = " << delta_x / delta_b << endl;


	for (size_t j = 0; j < n + 1; ++j) {
		delete[] A[j];
		delete[] A_save[j];
	}

	delete[] A;
	delete[] A_save;
	delete[] x;
	delete[] x_save;

	return 0;
}
