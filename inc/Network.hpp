#pragma once
#include <vector>
#include "Matrix.hpp"

class Network
{
public:
  /**
   * Constructs a network with a specified weight matrix.
   * 
   * Notes:
   * -  weightMatrix is a 2D vector pointer, i.e. a pointer to a vector of
   *    pointers to vectors of integers comprising the network's weight matrix.
   * -  weightMatrix should be square, i.e. having equal number of rows & cols
   *    to match the vector size of any input pattern to be recalled.
   */
  Network(Matrix<int> *weightMatrix);

  // Destructs the network, including memory management of its neurons.
  ~Network();

  /**
   * Runs the network.
   * 
   * Notes: 
   * -  inputs is a pointer to a vector of integers, and its size needs to match
   *    the size of weightMatrix.
   * -  outputs is a pointer to a vector of integers, and it will be cleared
   *    initially (i.e., reduced to size 0) regardless of its starting value.
   * -  If the size of inputs does not match the size of weightMatrix, then the
   *    size of outputs will remain 0 when Run() returns, signaling an error.
   */
  void Run(std::vector<int> *inputs, std::vector<int> *outputs);

private:
  // Holds the network's neurons, equal in number to size of the weight matrix.
  std::vector<class Neuron *> neurons;

  // The network's size, i.e. number of neurons and dimensions of weightMatrix.
  long unsigned int size;
};
