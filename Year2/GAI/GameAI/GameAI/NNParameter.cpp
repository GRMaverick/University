#include "NNParameters.h"

double NNParameters::Bias = 0;														// Bias weight value
double NNParameters::ActivationResponse = 0;								// Tweeking the Sigmoid Function
double NNParameters::CrossoverRate = 0;
double NNParameters::MutationRate = 0;
double NNParameters::MaxPerturbation = 0;
int		NNParameters::NumberOfInputs = 0;
int		NNParameters::NumberOfOutput = 0;
int		NNParameters::NumberOfHiddenLayers = 0;
int		NNParameters::NumberOfNeuronsPerLayer = 0;				// Maximum mutation amount per weight
int		NNParameters::NumberOfElite = 0;									// Elitism
int		NNParameters::NumberOfEliteCopies = 0;							//     " 

NNParameters::NNParameters(void)
{
	if (!LoadConfig("NeuralNetwork.config"))
	{
		std::cout << "Cannot find NeuralNetwork.config" << std::endl;
	}
}

bool 
NNParameters::LoadConfig(char* _filename)
{
	char ParamDescription[40];
	std::ifstream file(_filename);

	if (!file)
		return false;

	file >> ParamDescription;
	file >> NumberOfInputs;
	file >> ParamDescription;
	file >> NumberOfHiddenLayers;
	file >> ParamDescription;
	file >> NumberOfNeuronsPerLayer;
	file >> ParamDescription;
	file >> NumberOfOutput;
	file >> ParamDescription;
	file >> ActivationResponse;
	file >> ParamDescription;
	file >> Bias;

	return true;
}