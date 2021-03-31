#include "Genome.h"

//
// CTOR
//
Genome::Genome(void)
{
	m_Fitness = 0;
	m_Weights.clear();
}
//
// CTOR
//
Genome::Genome(std::vector<double> _weights, double _fitness)
{
	m_Fitness = _fitness;
	m_Weights = _weights;
}
//
// Method:			operator<	[ Override ]
// Description:		Greater than operator for Genomes
//
bool 
Genome::operator<(const Genome& rhs)
{
	return this->m_Fitness < rhs.m_Fitness;
}
//
// Method:			GetFitness
// Description:		Returns the fitness of this Genome
// Returns:			Double representing this Genome's fitness
//
double 
Genome::GetFitness(void)
{
	return m_Fitness;
}
//
// Method:			GetWeights
// Description:		Returns the weights of this Genome
// Returns:			std::vector<double> representing total number of weights in the net
//
std::vector<double>
Genome::GetWeights(void)
{
	return m_Weights;
}