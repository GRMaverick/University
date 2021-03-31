#include "NeuronLayer.h"

//
// CTOR
//
NeuronLayer::NeuronLayer(int _neurons, int _neuronInputs)
{
	m_NeuronCount = _neurons;

	for (unsigned int i = 0; i < m_NeuronCount; ++i)
	{
		m_Neurons.push_back(Neuron(_neuronInputs));
	}
}

//
// Method:			GetNumberOfNeurons
// Description:		Returns the total number of neurons in this layer
// Returns:			int representing total number of neuron in this layer
//
int 
NeuronLayer::GetNumberOfNeurons(void)
{
	return m_NeuronCount;
}

//
// Method:			GetNeurons
// Description:		Returns the list of Neurons in this layer
// Returns:			std::vector<Neuron> representing the list of Neurons in this layer
//
std::vector<Neuron> 
NeuronLayer::GetNeurons(void)
{
	return m_Neurons;
}