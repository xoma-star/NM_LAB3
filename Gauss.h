#pragma once
#include <vector>
#include <iostream>

std::vector<double> Gauss(std::vector<std::vector<double>> &matrix) {
	int dim = matrix.size();
	for (int i = 0; i < dim; ++i) {
		//выбор главного элемента
		for (int k = 0; k < dim - 1; ++k) {
			double max = 0;
			double m_index = 0;
			for (int m = k; m < dim; ++m) {
				if (abs(matrix[m][k]) > max) {
					max = abs(matrix[m][k]);
					m_index = m;
				}
			}
			if (max == 0) {
				std::cout << "There is no single solution" << std::endl;
				return { -1 };
			}
			for (int i = 0; i <= dim; ++i) {
				double temp = matrix[k][i];
				matrix[k][i] = matrix[m_index][i];
				matrix[m_index][i] = temp;
			}
		}
		//std::cout << "The result of the shuffle of rows: " << std::endl;
		//PrintMatrix(matrix);
		//исключение
		for (int j = i + 1; j < dim; ++j) {
			double coeff = -matrix[j][i] / matrix[i][i];
			for (int k = 0; k <= dim; ++k) {
				matrix[j][k] += coeff * matrix[i][k];
			}
		}
		//PrintMatrix(matrix);
	}
	//std::cout << "The result of a direct process:  " << std::endl;
	//PrintMatrix(matrix);
	//обратный ход
	std::vector<double> answer(dim);
	answer[dim - 1] = matrix[dim - 1][dim] / matrix[dim - 1][dim - 1];
	for (int i = dim - 2; i >= 0; --i) {
		answer[i] = matrix[i][dim];
		for (int j = i + 1; j < dim; ++j) {
			answer[i] -= matrix[i][j] * answer[j];
		}
		answer[i] /= matrix[i][i];
	}
	return answer;
}