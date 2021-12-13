#include<stdio.h>
#include<math.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

int CheckSize(string str)
{
	int size = 0;
	for (int i = 0; i < str.size(); i++)
		if (str[i] != ' ' && str[i + 1] == ' ')
			size++;
	return size + 1;
}

bool TrashFilter(string& str)
{
	int minus_f = 0, dot_f;
	dot_f = 0;
	str += ' ';
	if (str[0] == '-')
		minus_f = 1;
	for (int i = minus_f; i < str.size() - 1; i++)
	{
		if (!(str[i] <= '9' && str[i] >= '0') || dot_f == 2)
			return false;
		if (str[i + 1] == ',' || str[i + 1] == '.')
		{
			if (str[i + 1] == ',')
				str[i + 1] = '.';
			i++;
			dot_f++;
		}
	}
	return true;
	//////////////////////////
}

double** CreateMatrix(int size)
{
	ifstream finTest("test.txt");
	if (!finTest.is_open())
	{
		cout << "Failed to open file!\n";
	}
	else
	{
		cout << "Test file successfully opened for reading!\n";

		string num;
		double** matrix = new double* [size];
		for (int i = 0; i <= size; i++)
		{
			matrix[i] = new double[size];
			for (int j = 0; j < size; j++)
				matrix[i][j] = 0;
		}
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				finTest >> num;

				if (TrashFilter(num))
				{
					matrix[i][j] = stod(num);
					num = "";
				}
				else
				{
					cout << "\nFile is filled up incorrectly!";
					cout << "\n!!! The expression may contain only: \"0\", \"1\", \"2\", \"3\", \"4\", \"5\", \"6\", \"7\", \"8\", \"9\" !!!\n\n";
					break;
				}

			}
		}
		finTest.close();
		return matrix;
	}
}

void Matr(double** matr, int n, double eps)
{
	float w0[100], w[100], summ = 0, w0norm[100], e, d, d0;
	int i, j, k, iterations = 0;
	for (i = 0; i < n; i++)
		w0[i] = 0;
	w0[0] = 1;
	do
	{
		for (i = 0; i < n; i++)
			summ = summ + w0[i] * w0[i];
		d0 = sqrt(summ);
		for (i = 0; i < n; i++)
			w0norm[i] = w0[i] / d0;
		for (i = 0; i < n; i++)
		{
			w[i] = 0;
			for (j = 0; j < n; j++)
				w[i] = w[i] + matr[i][j] * w0norm[j];
		}
		summ = 0;
		for (i = 0; i < n; i++)
			summ = summ + w[i] * w[i];
		d = sqrt(summ);
		e = fabs(d - d0);
		for (i = 0; i < n; i++)
			w0[i] = w[i];
		summ = 0;
		iterations = iterations++;
	} while (e > eps);
	cout << "Delta:"; cout << d << endl;;


	cout << "Matrix" << endl;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << matr[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;

	for (i = 0; i < n; i++)
	{
		cout << "eigenvalues"; cout << w0norm[i] << "\n" << endl;
	}
	cout << "Iterations:" << iterations;



}

void main()
{
	ifstream finTest("test.txt");
	int n;
	string line;
	getline(finTest, line);
	n = CheckSize(line);
	finTest.seekg(0);
	double eps;
	cout << "Set precision: ";
	cin >> eps;
	double** matrix = CreateMatrix(n);	
	Matr(matrix, n, eps);
}
