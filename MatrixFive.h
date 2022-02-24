#pragma once
#include <vector>
#include "Common.h"

void MatrixInitFive(std::vector<std::vector<double>>& a, int dim) {
	a.resize(dim);
	for (int i = 0; i < dim; ++i) {
		a[i].resize(dim + 1);
		double sum = 0;
		for (int j = 0; j < dim; ++j) {
			if (abs(i - j) <= 2 && i != j) {
				double value = RandomDouble(5, 10);
				a[i][j] = value;
				sum += abs(value);
			}
		}
		a[i][i] = 4 * pow(-1, RandomInt(0, 1)) * sum;
		a[i][dim] = RandomDouble(-1, 1);
	}
	PrintMatrix(a);
}

void CheckAnswer(std::vector<double>& answer, std::vector<std::vector<double>>& matrix) {
	int dim = matrix.size();
	for (int i = 0; i < dim; ++i) {
		double sum = 0;
		for (int j = 0; j < dim; ++j) {
			sum += matrix[i][j] * answer[j];
		}
		std::cout << "i = " << i << " sum = " << sum << " f = " << matrix[i][dim] << std::endl;
	}
}

double helpful(int i, std::vector<std::vector<double>>& a, int key) {
	switch (key) {
	case 0:
		if (i < 2) return 0;
		return a[i][i - 2];
	case 1:
		if (i < 1) return 0;
		return -a[i][i - 1];
	case 2:
		return a[i][i];
	case 3:
		if (i > a.size() - 2) return 0;
		return -a[i][i + 1];
	case 4:
		if (i > a.size() - 3) return 0;
		return a[i][i + 2];
	case 5:
		return a[i][a.size()];
	default:
		return 0;
	}
}

std::vector<double> FiveDiagonalMethod(std::vector<std::vector<double>> matrix) {

	int dim = matrix.size();
	std::vector<double> alpha(dim + 3), beta(dim + 3), gamma(dim + 3);
	alpha[1] = helpful(0, matrix, 3) / helpful(0, matrix, 2);
	beta[1] = helpful(0, matrix, 4) / helpful(0, matrix, 2);
	gamma[1] = helpful(0, matrix, 5) / helpful(0, matrix, 2);
	double delta1 = helpful(1, matrix, 2) - helpful(1, matrix, 1) * alpha[1];
	alpha[2] = (helpful(1, matrix, 3) - beta[1] * helpful(1, matrix, 1)) / delta1;
	gamma[2] = (helpful(1, matrix, 5) + helpful(1, matrix, 1) * gamma[1]) / delta1;
	beta[2] = helpful(1, matrix, 4) / delta1;
	for (int i = 2; i <= dim - 1; ++i) {
		double delta = helpful(i, matrix, 2) - helpful(i, matrix, 0) * beta[i - 1] + alpha[i] * (helpful(i, matrix, 0) * alpha[i - 1] - helpful(i, matrix, 1));
		if (i <= dim - 2) {
			alpha[i + 1] = (helpful(i, matrix, 3) + beta[i] * (helpful(i, matrix, 0) * alpha[i - 1] - helpful(i, matrix, 1))) / delta;
		}
		if (i <= dim - 3) {
			beta[i + 1] = helpful(i, matrix, 4) / delta;
		}
		gamma[i + 1] = (helpful(i, matrix, 5) - helpful(i, matrix, 0) * gamma[i - 1] - gamma[i] * (helpful(i, matrix, 0) * alpha[i - 1] - helpful(i, matrix, 1))) / delta;
	}
	std::vector<double> answer(dim + 3);
	answer[dim - 1] = gamma[dim];
	answer[dim - 2] = alpha[dim - 1] * answer[dim - 1] + gamma[dim - 1];
	for (int i = dim - 3; i >= 0; --i) {
		answer[i] = alpha[i + 1] * answer[i + 1] - beta[i + 1] * answer[i + 2] + gamma[i + 1];
	}
	answer.pop_back();
	answer.pop_back();
	answer.pop_back();
	return answer;
}