#pragma once
#include <vector>
#include <iostream>

void PrintVector(const std::vector<double>& vector) {
	for (int i = 0; i < vector.size(); ++i) {
		std::cout << vector[i] << "\t";
	}
	std::cout << "\n\n";
}

void PrintMatrix(const std::vector<std::vector<double>>& matrix) {
	for (int i = 0; i < matrix.size(); ++i) {
		for (int j = 0; j < matrix[i].size(); ++j) {
			std::cout << matrix[i][j] << "\t";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

int RandomInt(int min, int max) {
	int random_num = rand() % (max - min + 1) + min;
	return random_num;
}

double RandomDouble(double min, double max) {
	double f = (double)rand() / RAND_MAX;
	return min + (double)rand() / RAND_MAX * (max - min);
}