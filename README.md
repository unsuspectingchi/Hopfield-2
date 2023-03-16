# Hopfield-02

Hopfield-02 is an example of a Hopfield network implemented in C++.

This simple example consists of four neurons mutually connected to one another. The connections have weights, which can be positive or negative. The network is already trained to recall either of two input patterns. These inputs are in the form of binary patterns having in each component a 0 or 1:

A = (1, 0, 1, 0)
B = (0, 1, 0, 1)

Note that these inputs are orthogonal (i.e., their dot product is zero).

The network uses the weight matrix W =
0 -3 3 -3
-3 0 -3 3
3 -3 0 -3
-3 3 -3 0

Note that the weight matrix has zeros in its principal diagonal, which can be regarded as there being no self-connected neurons (or that there are self-connected neurons, but with weights of zero).

The threshold function is f(t) =
1 if t >= 0
0 if t < 0

The activation of each neuron is the weighted sum of its inputs. The activation at the first node is the dot product of the input vector and the first column of the weight matrix (0, -3, 3, -3). Etc.

The output of a neuron is then calculated by evaluating the threshold function at the activation of the neuron.

When the network is presented with input patterns A or B, it should perfectly recall those patterns.  Other presented patterns will also result in output of either A or B, depending on which pattern is "closer" to the input pattern.  For example, if C = (0, 1, 0, 0) is presented, then the output should be B = (0, 1, 0, 1) because C is "closer" to B than A.

Note that the Hopfield network is a recurrent network, meaning outputs from the network are fed back as inputs. We desire that the Hopfield network should always stabalize to a fixed point, but this will not necessarily happen unless the network is updated "asynchronously." This means that changes do not occur simultaneously to outputs that are fed back as inputs, but rather occur for one vector component at a time.

More specifically, the asynchronous Hopfield algorithm is:

1. Apply an input, Invec, to the network, and initialize Outvec = Invec.
2. Start with i = 1.
3. Calculate Value_i = DotProduct(Invec_i, Column_i of Weight matrix).
4. Calculate Outvec_i = f(Value_i), where f is the threshold function.
5. Update the input to the network with component Outvec_i.
6. Increment i, and repeat steps 3, 4, 5, and 6 until Invec = Outvec. (Note that when i reaches its maximum value, it is then reset to 1 for the cycle to continue.)

So if we have input E = (1, 0, 0, 1) equal distance from A and B, the first run of a synchronized Hopfield algorithm would result in F = (0, 1, 1, 0), which when fed back into the network as an input will flip the result back to E, then flipping back to F, and so on. In contrast, the asynchronous Hopfield algorithm ensure that the eventual output is either A or B (and, in fact, B here), and the algorithm erminates once Invec = Outvec.

Notes on terminology:
-- There are four "neurons" in the only "layer" of the "network".
-- "Neurons" may also be referred to as "nodes".
-- A node's "output" is the output of the "threshold function".
-- The argument for the threshold function is the "activation" of the node.
-- The "activation" of a node is the dot product of the "input vector" and the node's corresponding column in the "weight matrix".
-- The "output" of the network is the result at termination of the algorithm.
-- We say that the network has "recalled the pattern as presented" when the
original input pattern matches the terminating output of the network.
