#include "Network.hpp"
#include "Neuron.hpp"
#include "stdio.h"

Network::Network(Matrix<int> *weightMatrix)
    : size(weightMatrix->GetLength())
{
  printf("Network::Network()\n");
  // Loop through the weightMatrix to ensure that it is square.
  // TODO: IS THIS NECESSARY

  // bool weightMatrixIsSquare = true;
  // for (long unsigned int i = 0; i < size; ++i)
  // {
  //   weightMatrixIsSquare =
  //       weightMatrixIsSquare &&
  //       (weightMatrix->at(i)->size() == size);
  // }
  // if (weightMatrixIsSquare)
  // {
    // If weightMatrix is square, then construct a number of new neurons to
    // match the dimensions of weightMatrix.
    for (long unsigned int i = 0; i < size; ++i)
    {
      neurons.emplace_back(new Neuron(weightMatrix->GetRow(i)));
    }
  // }
  // else
  // {
  //   // If weightMatrix is not square, then do not construct any new neurons, set
  //   // network's size to zero, and log the error.
  //   size = 0;
  //   printf("ERROR: No neurons constructed, due to unsquare weight matrix.\n");
  // }
}

Network::~Network()
{
  printf("Network::~Network()");
  for (auto neuron : neurons)
  {
    delete neuron;
    neuron = nullptr;
  }
  neurons.clear();
}

void Network::Run(std::vector<int> *inputs, std::vector<int> *outputs)
{
  printf("Network::Run()\n");

  // Terminate run if weightMatrix is empty.
  if (!size)
  {
    printf("ERROR: Run terminated, due to empty weight matrix.\n");
    return;
  }

  // Terminate run if size mismatch between inputs and weightsMatrix.
  if (size != inputs->size())
  {
    printf("ERROR: Run terminated, due to size mismatch b/w inputs & weights");
    return;
  }

  // Clear the outputs vector (remove all elements leaving container at size 0).
  outputs->clear();

  // Loop through neurons initially to fill empty outputs vector using inputs.
  for (long unsigned int i = 0; i < size; ++i)
  {
    outputs->emplace_back(neurons[i]->Run(inputs));
  }

  // Repeatly loop through the neurons until the cycle's input & output match.
  bool willRunAgain = true;
  while (willRunAgain)
  {
    // Assume no need to re-run, unless there is a bitwise mismatch detected.
    willRunAgain = false;
    for (long unsigned int i = 0; i < size; ++i)
    {
      // Run each neuron using the preceding cycle's outputs as inputs.
      int output = neurons[i]->Run(outputs);
      // Compare cycle's output with the prior, to check for bitwise mismatch.
      willRunAgain = (willRunAgain || output != outputs->at(i));
      // Update outputs vector with the individual neuron's output this cycle.
      outputs->at(i) = output;
    }
  }
}
