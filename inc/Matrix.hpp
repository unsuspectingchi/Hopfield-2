#pragma once

#include <vector>
#include <iostream>

template<typename T>
class Matrix {
public:
  Matrix(int numRows, int numCols, T fill);
  Matrix();
  ~Matrix();

  T GetData(int row, int col);
  std::vector<T> *GetRow(int row);
  void SetData(T value, int row, int col);
  void SetRow(std::vector<T> *value, int row);
  void AppendRow(std::vector<T> *value);
  Matrix<T> *RotateCW();
  Matrix<T> *RotateCCW();
  int GetRowLength(int row);
  int GetLength();
private:
  int numRows;
  int numCols;
  T fill;
  std::vector<std::vector<T> *> data;
};

template<typename T>
Matrix<T>::Matrix(int numRows, int numCols, T fill)
    : numRows(numRows), numCols(numCols), fill(fill)
{
  for (int row = 0; row < numRows; ++row)
  {
    data.emplace_back(new std::vector<T>);
    for (int col = 0; col < numCols; ++col)
    {
        data[row]->emplace_back(fill);
    }
  }
}

template<typename T>
Matrix<T>::Matrix() {
  numRows = numCols = 0;
}

template<typename T>
Matrix<T> *Matrix<T>::RotateCW()
{
  Matrix<T> *matrix = new Matrix<T>(numCols, numRows, fill);
  for (int rowOld = 0; rowOld < numRows; ++rowOld)
  {
    for (int colOld = 0; colOld < numCols; ++colOld)
    {
      matrix->SetData(GetData(rowOld, colOld), colOld, numRows - rowOld - 1);
    }
  }
  return matrix;
}

template<typename T>
Matrix<T> *Matrix<T>::RotateCCW()
{
  Matrix<T> *matrix = new Matrix<T>(numCols, numRows, fill);
  for (int rowOld = 0; rowOld < numRows; ++rowOld)
  {
    for (int colOld = 0; colOld < numCols; ++colOld)
    {
      matrix->SetData(GetData(rowOld, colOld), numCols - colOld - 1, rowOld);
    }
  }
  return matrix;
}

template<typename T>
Matrix<T>::~Matrix()
{
  for (int row = 0; row < numRows; ++row)
  {
    delete data[row];
    data[row] = nullptr;
  }
}

template<typename T>
T Matrix<T>::GetData(int row, int col)
{
  return data[row]->at(col);
}

template<typename T>
std::vector<T> *Matrix<T>::GetRow(int row)
{
  return data[row];
}

template<typename T>
void Matrix<T>::SetRow(std::vector<T> *value, int row)
{
  data[row] = value;
}

template<typename T>
void Matrix<T>::AppendRow(std::vector<T> *value)
{
  if (!numCols)
  {
    numCols = (int) value->size();
  }
  data.emplace_back(value);
  numRows++;
}

template<typename T>
int Matrix<T>::GetLength()
{
  return numRows;
}

template<typename T>
void Matrix<T>::SetData(T value, int row, int col)
{
  data[row]->at(col) = value;
}

template<typename T>
int Matrix<T>::GetRowLength(int row)
{
  return data[row]->size();
}
