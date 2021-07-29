#include <vector>
#include "Matrix.hpp"

namespace Math
{
  void MultiplyVector(std::vector<int> vec1, std::vector<int> vec2, Matrix<int> &newVec);
  void AddSquareMatrix(Matrix<int> &matrix1, Matrix<int> &matrix2, Matrix<int>  &newMatrix2);
  void ConvertToBipolar(std::vector<int> vector, std::vector<int> &output);
  void ConvertToBinary(std::vector<int> vector, std::vector<int> &output);
}