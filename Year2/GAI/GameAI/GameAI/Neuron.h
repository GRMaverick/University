#ifndef __NEURON_H__
#define __NEURON_H__

#include <vector>

class Neuron
{
public:
	//
	// CTOR
	//
	Neuron(int _inputs);	
	//
	// Method:			GetNumberOfInputs
	// Description:		Returns the total number of inputs for this Neuron
	// Returns:			int representing total number of inputs for this Neuron
	//
	int GetNumberOfInputs(void);
	//
	// Method:			GetWeights
	// Description:		Returns the list of Weights for this Neuron's Inputs
	// Returns:			std::vector<Neuron> representing the list of Weights for this Neuron's Inputs
	//
	std::vector<double> GetWeights(void);
private:
	//
	// Property:		m_Inputs
	// Description:	Number of inputs to this neuron
	//
	int m_Inputs;
	//
	// Property:		m_Weights
	// Description:	List of weights for each input
	//
	std::vector<double> m_Weights;
};

#endif // __NEURON_H__