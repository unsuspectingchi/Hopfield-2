#include "Hopfield.hpp"
#include <iostream>
#include <string>

using std::cerr;
using std::endl;

int main(int argc, char **argv)
{
  if (argc < 3)
  {
    cerr << "Failure to specify command line arguments." << endl
         << "Expected 'Main <mode> <file1> <file2>" << endl
         << "if (mode == write) file1 = patterns (source) && file2 = weights (output)" << endl
         << "if (mode == run) file1 = weights (source) && file2 = inputs (source)" << endl;
    return 1;
  }
  if (std::string(argv[1]) == "write")
  {
    std::cout << "Write" << endl;
    return Hopfield::WriteWeightsMatrix(argv[2], argv[3]);
  }
  else if (std::string(argv[1]) == "run")
  {
    std::cout << "Run" << endl;
    return Hopfield::Run(argv[2], argv[3]);
  }
  else
  {
    cerr << "Failure to specify command line arguments." << endl
         << "Expected 'Main <mode> <file1> <file2>" << endl
         << "if (mode == write) file1 = patterns (source) && file2 = weights (output)" << endl
         << "if (mode == run) file1 = weights (source) && file2 = inputs (source)" << endl;
    return 1;
  }
  return 0;
}
