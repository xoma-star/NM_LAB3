#pragma once
#include <vector>
#include <iostream>
#include "Common.h"

std::vector<double> LUDecomposition(const std::vector<std::vector<double>>& matrix) {
	int dim = matrix.size();
	std::vector<std::vector<double>> L(dim);
	std::vector<std::vector<double>> U(dim);
	for (int i = 0; i < dim; ++i) {
		L[i].resize(dim);
		U[i].resize(dim);
		L[i][i] = 1;
		for (int j = 0; j < dim; ++j) {
			if (i <= j) {
				U[i][j] = matrix[i][j];
				for (int k = 0; k <= i - 1; ++k) {
					U[i][j] -= L[i][k] * U[k][j];
				}
			}
			else {
				L[i][j] = matrix[i][j];
				for (int k = 0; k <= j - 1; ++k) {
					L[i][j] -= L[i][k] * U[k][j];
				}
				L[i][j] /= U[j][j];
			}
		}
	}
	std::cout << "L:" << std::endl;
	PrintMatrix(L);
	std::cout << "U:" << std::endl;
	PrintMatrix(U);
	std::vector<double> y(dim);
	for (int i = 0; i < dim; ++i) {
		y[i] = matrix[i][dim];
		for (int k = 0; k <= i - 1; ++k) {
			y[i] -= L[i][k] * y[k];
		}
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