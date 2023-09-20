// Cholesky Decomposition:  mdspan
#include <bits/stdc++.h>
#include <experimental/mdspan>
#include <vector>

using namespace std;

template <typename T>
void Cholesky_Decomposition(std::vector<T>& vec, int n) {
  int lower[n][n];
  memset(lower, 0, sizeof(lower));

  using view_2d = std::extents<T, std::dynamic_extent, std::dynamic_extent>;
  auto matrix = std::mdspan<T, view_2d, std::layout_right>(vec.data(), n, n);

  // Decomposing a matrix into Lower Triangular
  for (int i = 0; i < matrix.extent(0); i++) {
    for (int j = 0; j <= i; j++) {
      int sum = 0;

      if (j == i)  // summation for diagonals
      {
        for (int k = 0; k < j; k++)
          sum += pow(lower[j][k], 2);

        lower[j][j] = sqrt(matrix(i, j) - sum);
      } else {

        // Evaluating L(i, j) using L(j, j)
        for (int k = 0; k < j; k++)
          sum += (lower[i][k] * lower[j][k]);
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
