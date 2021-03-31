#ifndef __NEURON_LAYER_H__
#define __NEURON_LAYER_H__

#include <vector>
#include "Neuron.h"

class NeuronLayer
{
public:
	//
	// CTOR
	//
	NeuronLayer(int _neurons, int _neuronInputs);
	//
	// Method:			GetNumberOfNeurons
	// Description:		Returns the total number of neurons in this layer
	// Returns:			int representing total number of neuron in this layer
	//
	int GetNumberOfNeurons(void);
	//
	// Method:			GetNeurons
	// Description:		Returns the list of Neurons in this layer
	// Returns:			std::vector<Neuron> representing the list of Neurons in this layer
	//
	std::vector<Neuron> GetNeurons(void);
private:
	//
	// Property:			m_NeuronsCount
	// Description:		Number of Neurons in this layer
	//
	int m_NeuronCount;
	//
	// Property:			m_Neurons
	// Description:		List of Neurons in this layer
	//
	std::vector<Neuron> m_Neurons;
};

#endif // __NEURON_LAYER_H__