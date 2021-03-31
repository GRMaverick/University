#include "NeuralNetwork.h"
#include "NNParameters.h"

//
// CTOR
//
NeuralNetwork::NeuralNetwork(void)
{
	m_NumberInputs = NNParameters::NumberOfInputs;
	m_NumberOutputs = NNParameters::NumberOfOutput;
	m_NumberHiddenLayers = NNParameters::NumberOfHiddenLayers;
	m_NumberNeuronsPerLayer = NNParameters::NumberOfNeuronsPerLayer;

	this->InitialiseNetwork();
}
//
// DTOR
//
NeuralNetwork::~NeuralNetwork(void)
{
}
//
// Method:			InitialiseNetwork
// Description:		Initialise the network
//
void 
NeuralNetwork::InitialiseNetwork()
{
	if (m_NumberHiddenLayers > 0)
	{
		// Input Layer
		m_Layers.push_back(NeuronLayer(m_NumberNeuronsPerLayer, m_NumberInputs));

		// Middle Layers
		for (unsigned int i = 0; i < m_NumberHiddenLayers-1; ++i)
		{
			m_Layers.push_back(NeuronLayer(m_NumberNeuronsPerLayer, m_NumberInputs));
		}

		// Output Layer
		m_Layers.push_back(NeuronLayer(m_NumberNeuronsPerLayer, m_NumberInputs));
	}
	else
	{
		// Output Layer
		m_Layers.push_back(NeuronLayer(m_NumberNeuronsPerLayer, m_NumberInputs));
	}
}
//
// Method:			UpdateNetwork()
// Description:		Updates the network
// Parameters:
//		(OUT)			_inputs - Contains a reference to the inputs list
// Returns:			vector<double> representing outputs of the ANN
//
std::vector<double>
NeuralNetwork::UpdateNetwork(std::vector<double>& _inputs)
{
	int weight = 0;
	std::vector<double> outputs;

	if (_inputs.size() != m_NumberInputs)
		return outputs;

	// For each layer
	for (unsigned int i = 0; i < m_NumberHiddenLayers + 1; ++i)
	{
		if (i > 0)
			_inputs = outputs;

		weight = 0;
		outputs.clear();

		// Each neuron
		for (unsigned int j = 0; j < m_Layers[i].GetNumberOfNeurons(); ++j)
		{
			double netInput = 0;
			int numInputs = m_Layers[j].GetNeurons()[j].GetNumberOfInputs();

			// each weight
			for (unsigned int k = 0; k < numInputs; ++k)
			{
				// a = SIGMA (xN * wN)
				netInput += m_Layers[i].GetNeurons()[j].GetWeights()[k] * _inputs[weight++];
			}
			
			// Add bias
			netInput += m_Layers[i].GetNeurons()[j].GetWeights()[numInputs - 1] * NNParameters::Bias;

			// output = 1 / (1 + exponent(-a/p)
			outputs.push_back(Sigmoid(netInput, NNParameters::ActivationResponse));

			weight = 0;
		}
	}

	return outputs;
}
//
// Method:			GetNumberOfWeights
// Description:		Returns the total number of weights in the net
// Returns:			int representing total number of weights in the net
//
int 
NeuralNetwork::GetNumberOfWeights(void)
{
	unsigned int weights = 0;
	for (unsigned int i = 0; i < m_NumberHiddenLayers + 1; ++i)
	{
		for (unsigned int j = 0; j < m_Layers[i].GetNumberOfNeurons(); ++j)
		{
			for (unsigned int k = 0; k < m_Layers[i].GetNeurons()[j].GetNumberOfInputs(); ++k)
			{
				weights++;
			}
		}
	}
	return weights;
}
//
// Method:			SetWeights
// Description:		Sets the Weights with updated weights
// Parameters:
//		(IN)				_weights - updated weights
//
void 
NeuralNetwork::SetWeights(std::vector<double>& _weights)
{
	unsigned int index = 0;
	for (unsigned int i = 0; i < m_NumberHiddenLayers + 1; ++i)
	{
		for (unsigned int j = 0; j < m_Layers[i].GetNumberOfNeurons(); ++j)
		{
			for (unsigned int k = 0; k < m_Layers[i].GetNeurons()[j].GetNumberOfInputs(); ++k)
			{
				m_Layers[i].GetNeurons()[j].GetWeights()[k] = _weights[index++];
			}
		}
	}
}
//
// Method:			GetWeights
// Description:		Returns the current weights
// Returns:			vector<double> which is current list of weights
//
std::vector<double> 
NeuralNetwork::GetWeights(void)
{
	std::vector<double> weightsToReturn;
	for (unsigned int i = 0; i < m_NumberHiddenLayers + 1; ++i)
	{
		for (unsigned int j = 0; j < m_Layers[i].GetNumberOfNeurons(); ++j)
		{
			for (unsigned int k = 0; k < m_Layers[i].GetNeurons()[j].GetNumberOfInputs(); ++k)
			{
				weightsToReturn.push_back(m_Layers[i].GetNeurons()[j].GetWeights()[k]);
			}
		}
	}
	return weightsToReturn;
}
//
// Method:			Sigmoid
// Description:		Sigmoidal response curve
// Parameters:
//		(IN)				_activation - activation level to calculate result
//		(IN)				_response - configuration parameter
//
double 
NeuralNetwork::Sigmoid(double _activation, double _response)
{
	return (1 / (1 + exp(-_activation / _response)));
}