#pragma once

#include <iostream>
#include <vector>
// generate positive definition matrix
template <typename T>
using Matrix = std::vector<std::vector<T>>;

template <typename T>
std::vector<T> generate_pascal_matrix(const int n) {
  Matrix<T> matrix(n, std::vector<T>(n, static_cast<T>(0)));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i == 0 || j == 0) {
        matrix[i][j] = static_cast<T>(1);
      } else {
        matrix[i][j] = matrix[i][j - 1] + matrix[i - 1][j];
      }
    }
  }

  std::vector<T> flattenedVector;
  for (const auto& row : matrix) {
    flattenedVector.insert(flattenedVector.end(), row.begin(), row.end());
  }
  return std::move(flattenedVector);
}
