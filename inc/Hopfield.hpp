#pragma once
#include "Matrix.hpp"

class Hopfield
{
public:
  // Run all provided input data through network created with provided weights.
  static int Run(char *weightsFile, char *inputsFile);

  // Derive weights matrix for specified patterns and write to specified file.
  static int WriteWeightsMatrix(char *patternsFile, char *weightsFile);

private:
  // Manage memory by deleting each row of a matrix.
  static void DeleteMatrixRows(Matrix<int> &matrix);

  // Print matrix.
  static void PrintMatrix(Matrix<int> &matrix);

  // Read specified file into specified matrix (of integers).
  // If the matrix is not empty, new data will be appended.
  static bool ReadFileToMatrix(char *fileName, Matrix<int> &matrix);
};
