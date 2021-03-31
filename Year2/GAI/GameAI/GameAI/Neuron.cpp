#include "Neuron.h"

//
// CTOR
//
Neuron::Neuron(int _inputs)
{
	m_Inputs = _inputs;

	for (unsigned int i = 0; i < _inputs + 1; ++i)
	{
		m_Weights.push_back((rand() / RAND_MAX + 1.0f) - (rand() / RAND_MAX + 1.0f));
	}
}

//
// Method:			GetNumberOfInputs
// Description:		Returns the total number of inputs for this Neuron
// Returns:			int representing total number of inputs for this Neuron
//
int 
Neuron::GetNumberOfInputs(void)
{
	return m_Inputs;
}

//
// Method:			GetWeights
// Description:		Returns the list of Weights for this Neuron's Inputs
// Returns:			std::vector<Neuron> representing the list of Weights for this Neuron's Inputs
//
std::vector<double> 
Neuron::GetWeights(void)
{
	return m_Weights;
}