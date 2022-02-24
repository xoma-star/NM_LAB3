#pragma once
#include <vector>
#include "Common.h"

double f(const double& x) {
	return exp(-x * x);
}

std::vector<double> SquareRootMethod(const std::vector<std::vector<double>>& matrix) {
	int dim = matrix.size();
	std::vector<std::vector<double>> U(dim);
	for (int i = 0; i < dim; ++i) {
		U[i].resize(dim);
		U[i][i] = matrix[i][i];
		for (int k = 0; k <= i - 1; ++k) {
			U[i][i] -= U[k][i] * U[k][i];
		}
		U[i][i] = sqrt(U[i][i]);
		for (int j = 1; j < dim; ++j) {
			if (j > i) {
				U[i][j] = matrix[i][j];
				for (int k = 0; k <= i - 1; ++k) {
					U[i][j] -= U[k][i] * U[k][j];
				}
				U[i][j] /= U[i][i];
			}
		}
	}
	std::cout << "U:" << std::endl;
	PrintMatrix(U);
	std::vector<double> y(dim);
	for (int i = 0; i < dim; ++i) {
		y[i] = matrix[i][dim];
		for (int k = 0; k <= i - 1; ++k) {
			y[i] -= U[k][i] * y[k];
		}
		y[i] /= U[i][i];
	}
	std::vector<double> x(dim);
	for (int i = dim - 1; i >= 0; --i) {
		x[i] = y[i];
		for (int k = i + 1; k < dim; ++k) {
			x[i] -= U[i][k] * x[k];
		}
		x[i] /= U[i][i];
	}
	return x;
}