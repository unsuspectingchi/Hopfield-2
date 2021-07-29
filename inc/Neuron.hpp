#pragma once
#include <vector>

class Neuron
{
public:
  /**
   * Constructs a neuron with a specified weight vector.
   * 
   * Notes:
   * -  weights is a pointer to a vector of integers stored elsewhere; no copy
   *    will be created here.
   * -  Size of weights needs to match the size of inputs provided at Run().
   */
  Neuron(std::vector<int> *weights);

  /**
   * Runs the individual neuron.
   * 
   * Notes: 
   * -  inputs is a pointer to a vector of integers stored elsewhere; no copy
   *    will be created here.
   * -  Size of inputs needs to match size of weights provided at construction.
   *    For efficient speed of calculation, no size check will be performed.
   */
  int Run(std::vector<int> *inputs);

private:
  // Activates the neuron (when run) according to its inputs and weights.
  int Activate(std::vector<int> *inputs);

  // Tests the neuron's activation against threshold conditions.
  int ApplyThreshold(int activation);

  // Neuron's weights, as received at construction.
  std::vector<int> *weights;

  // Size of neuron's weights, which must match inputs size.
  long unsigned int size;
};
