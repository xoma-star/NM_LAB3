#include <vector>
#include <fstream>
#include <sstream>
#include "MatrixInit.h"
#include "Gauss.h"
#include "Common.h"
#include "LUDecomposition.h"
#include "SquareRoot.h"
#include "MatrixFive.h"

void DrawGraphic(const std::string& data) {
	std::ofstream file("file");
	file << "plot " << data << "; pause mouse keypress" << "\n";
	file.close();
	std::system("\"C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\"  -persist file");
}

int main() {
	//Задание 1
	std::vector<double> x = { -0.5, -0.1, 0.3, 0.70, 1.10, 1.50 };
	std::vector<double> y = { -2.8276, -0.24862, -0.72244, -1.9749, -1.1225, -0.59738 };
	int dim = 6;
	std::vector<std::vector<double>> A;

	MatrixInit(A, dim, x, y);
	std::cout << "Extended matrix of the system: " << std::endl;
	PrintMatrix(A);
	std::vector<double> answer = Gauss(A);
	std::cout << "Gauss answer: " << std::endl;
	PrintVector(answer);
	int N = 100;
	double a = x[0];
	double b = x[dim - 1];
	double h = (b - a) / N;
	std::ofstream task1("task1.txt");
	for (int i = 0; i <= N; ++i) {
		double x_i = a + i * h;
		double f = (answer[0] + answer[1] * x_i + answer[2] * pow(x_i, 2)) / (1 + answer[3] * x_i + answer[4] * pow(x_i, 2) + answer[5] * pow(x_i, 3));
		task1 << x_i << " " << f << std::endl;
	}
	task1.close();
	std::stringstream graphic_info;
	graphic_info << "\"task1.txt\" using 1:2 title \"Interpolation task 1\" with lines, '-' using 1:2 title \"Points\"\n";
	for (int i = 0; i < dim; ++i) {
		graphic_info << x[i] << " " << y[i] << std::endl;
	}
	graphic_info << "e\n";
	DrawGraphic(graphic_info.str());
	
	//Задание 2
	answer = LUDecomposition(A);
	std::cout << "LUDecomposition answer: " << std::endl;
	PrintVector(answer);
	std::ofstream task2("task2.txt");
	for (int i = 0; i <= N; ++i) {
		double x_i = a + i * h;
		double f = (answer[0] + answer[1] * x_i + answer[2] * pow(x_i, 2)) / (1 + answer[3] * x_i + answer[4] * pow(x_i, 2) + answer[5] * pow(x_i, 3));
		task2 << x_i << " " << f << std::endl;
	}
	task2.close();
	std::stringstream graphic_info2;
	graphic_info2 << "\"task2.txt\" using 1:2 title \"Interpolation task 2\" with lines, '-' using 1:2 title \"Points\"\n";
	for (int i = 0; i < dim; ++i) {
		graphic_info2 << x[i] << " " << y[i] << std::endl;
	}
	graphic_info2 << "e\n";
	DrawGraphic(graphic_info2.str());

	//Задание 3
	a = 0;
	b = 3;
	int n = 20;
	x.clear();
	y.clear();

	h = (b - a) / n;
	for (int i = 0; i < n; ++i) {
		double p = a + i * h;
		x.push_back(p);
		y.push_back(f(p));
	}
	std::vector<std::vector<double>> answers;
	std::vector<std::vector<double>> matrix;
	//Polynoms with max degree 1...12
	for (int m = 2; m < 14; ++m) {
		matrix.clear();
		matrix.resize(m);
		for (int i = 0; i < m; ++i) {
			matrix[i].resize(m + 1);
			for (int j = 0; j < m; ++j) {
				for (int k = 0; k < n; ++k) {
					matrix[i][j] += pow(x[k], i + j);
				}
			}
			for (int k = 0; k < n; ++k) {
				matrix[i][m] += y[k] * pow(x[k], i);
			}
		}
		std::cout << "Matrix:" << std::endl;
		PrintMatrix(matrix);
		answer = SquareRootMethod(matrix);
		std::cout << "Square root method answer: " << std::endl;
		PrintVector(answer);
		answers.push_back(answer);
	}
	

	N = 100;
	h = (b - a) / N;
	std::ofstream task3("task3.txt");
	for (int i = 0; i <= N; ++i) {
		double x = a + i * h;
		double f = 0;
		int count = 0;
		task3 << x << " ";
		for (int k = 0; k < 12; ++k) {
			f = 0;
			for (int j = 0; j < k + 2; ++j) {
				f += answers[k][j] * pow(x, j);
			}
			task3 << f << " ";
		}
		task3 << std::endl;
	}
	task3.close();
	std::stringstream graphic_info3;
	for (int i = 0; i < 12; ++i) {
		graphic_info3 << "\"task3.txt\" using 1:" << i + 2 << " title \"Approximation with n = " << i + 1 << "\" with lines,";
	}
	graphic_info << " '-' using 1:2 title \"Points\"\n";
	for (int i = 0; i < n; ++i) {
		graphic_info3 << x[i] << " " << y[i] << std::endl;
	}
	graphic_info << "e\n";
	DrawGraphic(graphic_info3.str());
	//Find polynom degree with best approximation
	std::cout << "Polynom degree with best approximation = " << std::endl;
	std::vector<double> sum_of_squares_of_deviations(12);
	for (int i = 0; i < x.size(); ++i) {
		for (int k = 0; k < 12; ++k) {
			double f = 0;
			for (int j = 0; j < k + 2; ++j) {
				f += answers[k][j] * pow(x[i], j);
			}
			sum_of_squares_of_deviations[k] += pow(abs(f - y[i]), 2);
		}
	}
	double min_value = sum_of_squares_of_deviations[0];
	double min_n = 0;
	std::cout << "n = " << 1 << " Sum of squares of deviations: " << sum_of_squares_of_deviations[0] << std::endl;
	for (int i = 1; i < 12; ++i) {
		if (sum_of_squares_of_deviations[i] < min_value) {
			min_value = sum_of_squares_of_deviations[i];
			min_n = i;
		}
		std::cout << "n = " << (i + 1) << " Sum of squares of deviations: " << sum_of_squares_of_deviations[i] << std::endl;
	}
	std::cout << "Best: " << std::endl;
	std::cout << "  n = " << (min_n + 1) << " Sum of squares of deviations: " << min_value << std::endl;

	//Задание 4
	A.clear();
	std::srand(std::time(nullptr));
	std::cout << "Extended matrix of the system: " << std::endl;
	MatrixInitFive(A, 7);
	std::cout << "Answer: " << std::endl;
	answer = FiveDiagonalMethod(A);
	PrintVector(answer);
	std::cout << "Check answer: " << std::endl;
	CheckAnswer(answer, A);
	return 0;
}