#ifndef __NEURON_NETWORK_H__
#define __NEURON_NETWORK_H__

#include <vector>
#include "NeuronLayer.h"

class NeuralNetwork
{
public:
	//
	// CTOR
	//
	NeuralNetwork(void);
	//
	// DTOR
	//
	~NeuralNetwork(void);
	//
	// Method:			InitialiseNetwork
	// Description:		Initialise the network
	//
	void InitialiseNetwork();
	//
	// Method:			UpdateNetwork()
	// Description:		Updates the network
	// Parameters:
	//		(OUT)			_inputs - Contains a reference to the inputs list
	// Returns:			vector<double> representing outputs of the ANN
	//
	std::vector<double> UpdateNetwork(std::vector<double>& _inputs);
	//
	// Method:			GetNumberOfWeights
	// Description:		Returns the total number of weights in the net
	// Returns:			int representing total number of weights in the net
	//
	int GetNumberOfWeights(void);
	//
	// Method:			SetWeights
	// Description:		Sets the Weights with updated weights
	// Parameters:
	//		(IN)				_weights - updated weights
	//
	void SetWeights(std::vector<double>& _weights);
	//
	// Method:			GetWeights
	// Description:		Returns the current weights
	// Returns:			vector<double> which is current list of weights
	//
	std::vector<double> GetWeights(void);
	//
	// Method:			Sigmoid
	// Description:		Sigmoidal response curve
	// Parameters:
	//		(IN)				_activation - activation level to calculate result
	//		(IN)				_response - configuration parameter
	//
	double Sigmoid(double _activation, double _response);

private:
	//
	// Property:		m_NumberInputs	
	// Description:	Number of Network Inputs
	//
	int m_NumberInputs;
	//
	// Property:		m_NumberOutputs	
	// Description:	Number of Network Outputs
	//
	int m_NumberOutputs;
	//
	// Property:		m_NumberHiddenLayers	
	// Description:	Number of Network Hidden Layers
	//
	int m_NumberHiddenLayers;
	//
	// Property:		m_NumberNeuronsPerLayer	
	// Description:	Number of Neurons per Hidden Layers
	//
	int m_NumberNeuronsPerLayer;
	//
	// Property:		m_Layers	
	// Description:	The hidden layers
	//
	std::vector<NeuronLayer> m_Layers;
};

#endif // __NEURON_NETWORK_H__