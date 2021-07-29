#include "Math.hpp"

void Math::AddSquareMatrix(Matrix<int> &matrix1, Matrix<int> &matrix2, Matrix<int> &newMatrix)
{
  int matrixSize = newMatrix.GetRowLength(0);
  for (int x = 0; x < matrixSize; ++x)
  {
    for (int y = 0; y < matrixSize; ++y)
    {
      newMatrix.SetData(matrix1.GetData(x, y) + matrix2.GetData(x, y), x, y);
    }
  }
}

void Math::MultiplyVector(std::vector<int> vec1, std::vector<int> vec2, Matrix<int> &newVec) // Assume vector that is passed is already bipolar
{
  int vecLength = newVec.GetRowLength(0);
  for (int x = 0; x < vecLength; ++x)
  {
    for (int y = 0; y < vecLength; ++y)
    {
      if (x == y)
      {
        newVec.SetData(0, x, y);
        continue;
      }
      newVec.SetData(vec1[x] * vec2[y], x, y);
    }
  }
}

/*
  Assumes the output vector is empty
*/
void Math::ConvertToBipolar(std::vector<int> vector, std::vector<int> &output)
{
  for (size_t i = 0; i < vector.size(); ++i)
  {
    output.emplace_back(vector[i] * 2 - 1);
  }
}

/*
  Assumes the output vector is empty
*/
void Math::ConvertToBinary(std::vector<int> vector, std::vector<int> &output)
{
  for (size_t i = 0; i < vector.size(); ++i)
  {
    output.emplace_back((vector[i] + 1) * 0.5);
  }
}