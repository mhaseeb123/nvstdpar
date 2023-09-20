// Cholesky Decomposition: stdpar
#include "argparse/argparse.hpp"
#include "commons.hpp"

#include <algorithm>
#include <execution>  // Include the execution header
#include <experimental/mdspan>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

struct Multiply {
  int operator()(int a, int b) const { return a * b; }
};

template <typename T>
void Cholesky_Decomposition(std::vector<T>& vec, int n) {
  std::vector<std::vector<T>> lower(n, std::vector<T>(n, 0));

  using view_2d = std::extents<T, std::dynamic_extent, std::dynamic_extent>;
  auto matrix = std::mdspan<T, view_2d, std::layout_right>(vec.data(), n, n);

  Multiply multiplier;
  // Decomposing a matrix into Lower Triangular
  for (int i = 0; i < matrix.extent(0); i++) {
    for (int j = 0; j <= i; j++) {
      int sum = 0;

      if (j == i)  // summation for diagonals
      {

        // apply transform_reduce for the first [lower[j].cbegin(), lower[j].cbegin() +j )
        // sum = std::transform_reduce(std::execution::par, lower[j].cbegin(), lower[j].cbegin() +j, 0, std::plus{}, Square());

        sum = std::transform_reduce(std::execution::par, lower[j].cbegin(),
                                    lower[j].cbegin() + j, 0, std::plus{},
                                    [=, i = i, j = j](int n) { return n * n; });

        lower[j][j] = std::sqrt(matrix(i, j) - sum);

      } else {
        // Evaluating L(i, j) using L(j, j)

        sum = std::transform_reduce(std::execution::par, lower[j].cbegin(),
                                    lower[j].cbegin() + j, lower[i].cbegin(), 0,
                                    std::plus<>(), multiplier);

        lower[i][j] = (matrix(i, j) - sum) / lower[j][j];
      }
    }
  }

  // Displaying Lower Triangular and its Transpose
  cout << setw(6) << " Lower Triangular" << setw(30) << "Transpose" << endl;
  for (int i = 0; i < n; i++) {

    // Lower Triangular
    for (int j = 0; j < n; j++)
      cout << setw(6) << lower[i][j] << "\t";
    cout << "\t";

    // Transpose of Lower Triangular
    for (int j = 0; j < n; j++)
      cout << setw(6) << lower[j][i] << "\t";
    cout << endl;
  }
}

// Driver Code for testing
int main() {
  constexpr int n = 3;
  std::vector<int> v{4, 12, -16, 12, 37, -43, -16, -43, 98};
  Cholesky_Decomposition(v, n);

  return 0;
}
