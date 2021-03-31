#ifndef __GENOME_H__
#define __GENOME_H__

#include <vector>

class Genome
{
public:
	//
	// CTOR
	//
	Genome(void);
	//
	// CTOR
	//
	Genome(std::vector<double> _weights, double _fitness);
	//
	// Method:			operator<	[ Override ]
	// Description:		Greater than operator for Genomes
	//
	bool operator<(const Genome& rhs);
	//
	// Method:			GetFitness
	// Description:		Returns the fitness of this Genome
	// Returns:			double representing this Genome's fitness
	//
	double GetFitness(void);
	//
	// Method:			GetWeights
	// Description:		Returns the weights of this Genome
	// Returns:			std::vector<double> representing total number of weights in the net
	//
	std::vector<double> GetWeights(void);

private:
	//
	// Property:			m_Fitness
	// Description:		Fitness value for the Genome
	//
	double m_Fitness;
	//
	// Property:			m_Weights
	// Description:		Weights for this Genome
	//
	std::vector<double> m_Weights;
};

#endif //__GENOME_H__
