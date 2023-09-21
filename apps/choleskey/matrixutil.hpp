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

// #include <cmath>
// #include <iostream>
// #include <random>
// #include <type_traits>
// #include <vector>

// template <typename T>
// std::vector<T> generateRandomPositiveDefiniteMatrix(int n) {
//   static_assert(std::is_arithmetic<T>::value,
//                 "Only numeric types are allowed.");

//   std::vector<std::vector<T>> matrix(n, std::vector<T>(n, static_cast<T>(0)));
//   std::random_device rd;
//   std::mt19937 gen(rd());

//   if constexpr (std::is_floating_point<T>::value) {
//     std::uniform_real_distribution<T> realDist(-1.0, 1.0);

//     for (int i = 0; i < n; ++i) {
//       for (int j = 0; j <= i; ++j) {
//         T randomValue = realDist(gen);
//         matrix[i][j] = randomValue;
//         matrix[j][i] = randomValue;  // Symmetric property
//       }
//     }
//   } else if constexpr (std::is_integral<T>::value) {
//     std::uniform_int_distribution<T> intDist(-100, 100);

//     for (int i = 0; i < n; ++i) {
//       for (int j = 0; j <= i; ++j) {
//         T randomValue = intDist(gen);
//         matrix[i][j] = randomValue;
//         matrix[j][i] = randomValue;  // Symmetric property
//       }
//     }
//   }

//   // Perform Cholesky decomposition to ensure positive-definiteness
//   std::vector<std::vector<T>> lower(n, std::vector<T>(n, static_cast<T>(0)));

//   for (int i = 0; i < n; ++i) {
//     for (int j = 0; j <= i; ++j) {
//       T sum = static_cast<T>(0);
//       if (j == i) {
//         for (int k = 0; k < j; ++k) {
//           sum += lower[j][k] * lower[j][k];
//         }
//         lower[j][j] = std::sqrt(matrix[i][j] - sum);
//       } else {
//         for (int k = 0; k < j; ++k) {
//           sum += lower[i][k] * lower[j][k];
//         }
//         lower[i][j] = (matrix[i][j] - sum) / lower[j][j];
//       }
//     }
//   }

//   std::vector<T> flattenedVector;
//   for (const auto& row : matrix) {
//     flattenedVector.insert(flattenedVector.end(), row.begin(), row.end());
//   }

//   return flattenedVector;
// }
