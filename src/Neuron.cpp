#include "Neuron.hpp"

Neuron::Neuron(std::vector<int> *weights)
    : weights(weights),
      size(weights->size()) {}

int Neuron::Activate(std::vector<int> *inputs)
{
  int activation = 0;
  // Note that no verification is being performed to prevent size mismatch.
  for (long unsigned int i = 0; i < size; ++i)
  {
    // Activation is the dot product of inputs and weights.
    activation += inputs->at(i) * weights->at(i);
  }
  return activation;
}

int Neuron::ApplyThreshold(int activation)
{
  // Note: 1 is returned even if activation = 0 (i.e. nonnegative activation).
  return (activation < 0 ? 0 : 1);
}

int Neuron::Run(std::vector<int> *inputs)
{
  // Use the private helper methods to return the neuron's output this cycle.
  return ApplyThreshold(Activate(inputs));
}
