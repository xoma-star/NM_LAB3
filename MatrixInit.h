#pragma once
#include <vector>
#include <math.h>

void MatrixInit(std::vector<std::vector<double>> &a, int size, std::vector<double> &x, std::vector<double> &y) {
	a.resize(size);
	int p = 2;
	int q = 3;
	for (int i = 0; i < size; ++i) {
		a[i].resize(size + 1);
		for (int j = 0; j < size; ++j) {
			if (j <= p) {
				a[i][j] = pow(x[i], j);
			}
			else {
				a[i][j] = -y[i] * pow(x[i], j - p);
			}
		}
		//b_0 = 1
		a[i][size] = y[i];
	}
}