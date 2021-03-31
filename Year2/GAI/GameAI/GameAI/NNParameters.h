#ifndef __NN_PARAMETERS_H__
#define __NN_PARAMETERS_H__

#include <fstream>
#include <iostream>

class NNParameters
{
public:
	static double Bias;									// Bias weight value
	static double ActivationResponse;			// Tweeking the Sigmoid Function

	static int NumberOfInputs;
	static int NumberOfOutput;
	static int NumberOfHiddenLayers;
	static int NumberOfNeuronsPerLayer;

	static double CrossoverRate;
	static double MutationRate;
	static double MaxPerturbation;				// Maximum mutation amount per weight

	static int NumberOfElite;							// Elitism
	static int NumberOfEliteCopies;				//     " 

	NNParameters(void);
	bool LoadConfig(char* _filename);
};

#endif // __NN_PARAMETERS_H__