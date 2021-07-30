#include <fstream>
#include <iostream>
#include "Network.hpp"
#include "Runner.hpp"
#include <string>
#include <sstream>

using std::cerr;
using std::cout;
using std::fstream;
using std::ios;
using std::string;
using std::stringstream;
using std::vector;

void Runner::DeleteMatrixRows(Matrix<int> &matrix)
{
  matrix.~Matrix();
}

void Runner::PrintMatrix(Matrix<int> &matrix)
{
  cout << "==================\n";
  for (int row = 0; row < matrix.GetLength(); ++row)
  {
    for (int col = 0; col < matrix.GetRowLength(row); ++col)
    {
      cout << matrix.GetData(row, col) << " ";
    }
    cout << "\n";
  }
  cout << "==================\n";
}

bool Runner::ReadFileToMatrix(char *fileName, Matrix<int> &matrix)
{
  int parsedInt;
  string line;
  fstream fs;
  stringstream ss;
  vector<int> *rowOfInts = nullptr;
  // int numRow = 0;

  // Open the specified file into a file stream.
  fs.open(fileName, ios::in);
  if (!fs.is_open())
  {
    cerr << "ERROR: Cannot open specified weights data file.\n";
    // Inform client that there was an error.
    return false;
  }

  // Read the file stream one line at a time.
  while (getline(fs, line))
  {
    // Create a new vector to hold each line of integers.
    rowOfInts = new std::vector<int>;
    // Clear the stringstream.
    ss.clear();
    // Set line's content in the stringstream.
    ss.str(line);
    // Stream the line one value at a time into the parsedInt variable.
    while (ss >> parsedInt)
    {
      // Emplace that parsedInt into rowOfInts
      rowOfInts->emplace_back(parsedInt);
    }
    // Emplace the rowOfInts into the specified matrix.
    matrix.AppendRow(rowOfInts);
    // TODO: rowOfInts deleted???
  }

  // Close the file stream.
  fs.close();

  // Inform client that there were no errors.
  return true;
}

int Runner::Run(int argc, char **argv)
{
  // Ensure that expected command line arguments were provided.
  if (argc < 2)
  {
    cerr << "ERROR: Failure to specify weights and inputs data files.\n"
         << "Start program by 'Main <weights-file> <inputs-file>'.\n";
    return 1;
  }

  // Read weights file into a vector matrix.
  Matrix<int> weightsMatrix;
  if (!ReadFileToMatrix(argv[1], weightsMatrix))
  {
    cerr << "ERROR: Cannot open specified weights data file.\n";
    return 1;
  }

  // Ensure that the weightsMatrix is not empty.
  if (!weightsMatrix.GetRowLength(0))
  {
    cerr << "ERROR: Empty weights matrix.\n";
    return 1;
  }

  // Display the weightsMatrix.
  cout << "\nWEIGHTS MATRIX:\n";
  PrintMatrix(weightsMatrix);

  // Confirm that the weightsMatrix is square.
  if (weightsMatrix.GetRowLength(0) != weightsMatrix.GetLength())
  {
    cerr << "ERROR: Weights matrix is not square.\n";
    DeleteMatrixRows(weightsMatrix);
    return 1;
  }

  // Read inputs file into a vector matrix.
  Matrix<int> inputsMatrix;
  if (!ReadFileToMatrix(argv[2], inputsMatrix))
  {
    cerr << "ERROR: Cannot open specified inputs data file.\n";
    return 1;
  }

  // Ensure that the inputsMatrix is not empty.
  if (!inputsMatrix.GetLength())
  {
    cerr << "ERROR: Empty inputs matrix.\n";
    DeleteMatrixRows(weightsMatrix);
    return 1;
  }

  // Display the inputsMatrix.
  cout << "\nINPUTS MATRIX:\n";
  PrintMatrix(inputsMatrix);

  // Confirm that the size of each inputs vector matches size of weightsMatrix.
  if (weightsMatrix.GetRowLength(0) != weightsMatrix.GetLength())
  {
    cerr << "ERROR: Size mismatch between inputs vector and weightsMatrix.\n";
    DeleteMatrixRows(inputsMatrix);
    DeleteMatrixRows(weightsMatrix);
    return 1;
  }

  // Create a network using weightsMatrix.
  Network network(&weightsMatrix);
  // Create a resusable outputs vector.
  vector<int> outputs;
  // Create a cycle counter.
  long unsigned int cycleCount = 0;

  // Present inputs to the network for recall, one row at a time.
  for (int row = 0; row < inputsMatrix.GetLength(); ++row)
  {
    network.Run(inputsMatrix.GetRow(row), &outputs);
    cout << "---------------------------------\n";
    cout << "TRIAL # " << ++cycleCount << "\n";
    cout << " input:";
    for (int col = 0; col < inputsMatrix.GetRowLength(row); ++col)
    {
      cout << " " << inputsMatrix.GetData(row, col);
    }
    cout << "\n";
    cout << "output:";
    for (auto output : outputs)
    {
      cout << " " << output;
    }
    cout << "\n";
  }
  cout << "---------------------------------\n";
  cout << "FINISHED\n";
  return 0;
}
