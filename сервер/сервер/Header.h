#pragma once
#include "winsock2.h"
#include "process.h"
#include "locale.h"
#include <iostream>
#include <fstream>
#include "time.h"
#include "conio.h"
#include <vector>
#include <list>
#include <iomanip>
#include <cmath>

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)



using namespace std;

class Enter {
private:
	SOCKET s2;
	char log[20];
	char pass[20];
public:
	string Login;
	string Password;
	int status;
	Enter() {
		status = 0;
	}
	char* get_log() {
		return log;
	};
	char* get_pass() {
		return pass;
	};
	void set(char* l, char* p) {
		strcpy(log, l);
		strcpy(pass, p);
	};
	int registration(char*, char*, char*);
	int check(char*, char*, char*);
	friend ifstream &operator >> (ifstream& a, Enter& b);
	friend ostream &operator<<(ostream& a, Enter& b);
	~Enter();
};

class Exception : public exception {
protected:
	int numbEr;
public:
	Exception();
	Exception(int);
	int show();
	~Exception();
};
class LogicError : Exception
{
public:LogicError() {}
};
class InvalidArgument : LogicError
{
public:InvalidArgument() { cout << "Передано неверное значение" << endl; }
};
class LengthError : LogicError
{
public:LengthError() { cout << "Выход за пределы массива" << endl; }
};

class Matrix
{
public:
	static const int size = 3;
	
	int **R;
	int **C;
	double r[size];
	double D[size];
	double Ck[size];
	double Dc[size];

	void output();
	void input_matrix(Matrix&);

	void calc_coeff();


	Matrix() {
		R = new int*[size];
		for (int i = 0; i < size; i++)
			R[i] = new int[size];
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++)
			{
				R[i][j] = 0;
			}
		}
		C = new int*[size];
		for (int i = 0; i < size; i++)
			C[i] = new int[size];
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++)
			{
				C[i][j] = 0;
			}
		}
		for (int j = 0; j < size; j++)
		{
			r[j] = 0;
			D[j] = 0;
			Ck[j] = 0;
			Dc[j] = 0;
		}

	}
	~Matrix() {
		for (int i = 0; i < size; i++)
		{
			delete[] R[i];
		}
		delete[]R;
		for (int i = 0; i < size; i++)
		{
			delete[] C[i];
		}
		delete[]C;
	}
};

void Matrix::output()
{
	ofstream fout("mat.txt");
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			fout << R[i][j] << endl;
		}
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			fout << C[i][j] << endl;
		}
	}

	fout.close();
}

void Matrix::input_matrix(Matrix &mat)
{

	ifstream fin("mat.txt");

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			fin >> mat.R[i][j];
		}
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			fin >> mat.C[i][j];
		}
	}

	fin.close();
}

void Matrix::calc_coeff()
{
	int t = 0;
	int t1 = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			t = R[i][j] + t;
			
		}
	}
	
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			double k = 0;
			k = (double)R[i][j] / (double)t;
			r[i] = r[i] + k;
		}		
		
	}

	double R1[size] = {0,0,0};
	for (int i = 0; i < size; i++)
	{

		for (int j = 0; j < size; j++)
		{
			double k = 0;
			k = (double)R[i][j] / (double)(size - 1);
			R1[i] = R1[i] + k;
			
		}
		
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			double k = 0;
			if (i == j) continue;
		
			k = R[i][j] - R1[i];
			
			D[i] = D[i] + pow(k, 2) / (size - 2);
		}
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			t1 = t1 + r[i]*C[i][j];
		}
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			Ck[i] = Ck[i] + (r[i] * C[i][j]/t1);
		}
	}

	double C1[size] = {0,0,0};
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			double k = 0;
			k = (double)C[i][j] / (double)(size - 1);
			C1[i] = C1[i] + k;
		}
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			double k = 0;
		
			k = C[i][j] - C1[i];
			Dc[i] = Dc[i] + (pow(k,2) / (size - 2));
		}
	}
}

