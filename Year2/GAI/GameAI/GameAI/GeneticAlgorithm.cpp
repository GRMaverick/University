#include "GeneticAlgorithm.h"
#include "NNParameters.h"
#include <algorithm>

//
// CTOR
//
GeneticAlgorithm::GeneticAlgorithm(int _populationSize, double _mutationRate, double _crossoverRate, int _numWeights)
{
	m_PopulationSize = _populationSize;
	m_MutationRate = _mutationRate;
	m_CrossoverRate = _crossoverRate;
	m_ChromosoneLength = _numWeights;
	m_TotalFitness = 0;
	m_GenerationCount = 0;
	m_FittestGenome = 0;
	m_BestFitness = 0;
	m_WorstFitness = 9999999;
	m_AverageFitness = 0;

	for (unsigned int i = 0; i < m_PopulationSize; ++i)
	{
		m_Population.push_back(Genome());
		for (unsigned int j = 0; j < m_ChromosoneLength; ++j)
		{
			m_Population[i].GetWeights().push_back((rand() / RAND_MAX + 1.0f) - (rand() / RAND_MAX + 1.0f));
		}
	}
}
//
// DTOR
//
GeneticAlgorithm::~GeneticAlgorithm(void)
{

}
//
// Method:			Epoch
// Description:		Runs the Genetic Algorithm for one generation
// Parameters:
//		(IN)				_oldPopulation - Population undergoing the Genetic Algorithm
// Returns:			std::vector<Genome>, representing the new population set
//
std::vector<Genome> 
GeneticAlgorithm::Epoch(std::vector<Genome>& _oldPopulation)
{
	m_Population = _oldPopulation;

	this->Reset();

	std::sort(m_Population.begin(), m_Population.end());

	CalculateBestWorstAverageTotal();

	std::vector<Genome> newPopulation;

	if (!(NNParameters::NumberOfEliteCopies * NNParameters::NumberOfElite % 2))
	{
		this->GrabNBest(NNParameters::NumberOfElite, NNParameters::NumberOfEliteCopies, newPopulation);
	}

	while (newPopulation.size() < m_PopulationSize)
	{
		Genome mother = this->GetChromosomeRoulette();
		Genome father = this->GetChromosomeRoulette();

		std::vector<double> offspring1;
		std::vector<double> offspring2;

		this->Crossover(mother.GetWeights(), father.GetWeights(), offspring1, offspring2);
		this->Mutate(offspring1);
		this->Mutate(offspring2);

		newPopulation.push_back(Genome(offspring1, 0));
		newPopulation.push_back(Genome(offspring2, 0));
	}
	m_Population = newPopulation;
	return m_Population;
}
//
// Method:			BestFitness
// Description:		Returns the best fitness
// Returns:			double, representing the best fitness value
//
double 
GeneticAlgorithm::BestFitness(void) const
{
	return m_BestFitness;
}
//
// Method:			AverageFitness
// Description:		Returns the average fitness
// Returns:			double, representing the average fitness value
//
double 
GeneticAlgorithm::AverageFitness(void) const
{
	return m_TotalFitness / m_PopulationSize;
}
//
// Method:			GetChromosomes
// Description:		Returns the chromosomes
// Returns:			std::vector<Genome>, representing the chromosome set
//
std::vector<Genome>
GeneticAlgorithm::GetChromosomes(void) const
{
	return m_Population;
}
//
// Method:			Reset
// Description:		Reset the Genetic Algorithm
//
void 
GeneticAlgorithm::Reset(void)
{
	m_TotalFitness = 0;
	m_BestFitness = 0;
	m_WorstFitness = 0;
	m_AverageFitness = 0;
}
//
// Method:			Mutate
// Description:		Mutates the offspring
//
void 
GeneticAlgorithm::Mutate(std::vector<double>& _chromo)
{
	for (unsigned int i = 0; i < _chromo.size(); ++i)
	{
		if ((rand() / RAND_MAX + 1.0f) < m_MutationRate)
		{
			_chromo[i] += ((rand() / RAND_MAX + 1.0f) - (rand() / RAND_MAX + 1.0f)) * NNParameters::MaxPerturbation;
		}
	}
}
//
// Method:			Crossover
// Description:		Generates the offspring and crosses the genes from parents to offspring
// Parameters:
//		(OUT)				_mother, mother of the offspring
//		(OUT)				_father, father of the offspring
//		(OUT)				_offspring1, first offspring
//		(OUT)				_offspring2, second offspring
//
void 
GeneticAlgorithm::Crossover(const std::vector<double>& _mother, const std::vector<double>& _father, std::vector<double>& _offspring1, std::vector<double>& _offspring2)
{
	if (((rand() / RAND_MAX + 1.0f) > m_CrossoverRate) || (_mother == _father))
	{
		_offspring1 = _mother;
		_offspring2 = _father;

		return;
	}

	int crossoverPoint = (rand() % (m_ChromosoneLength-1 - 0 + 1) + 0);

	for (unsigned int i = 0; i < crossoverPoint; ++i)
	{
		_offspring1.push_back(_mother[i]);
		_offspring2.push_back(_father[i]);
	}
	for (unsigned int i = crossoverPoint; i < _mother.size(); ++i)
	{
		_offspring1.push_back(_father[i]);
		_offspring2.push_back(_mother[i]);
	}
}
//
// Method:			CalculateBestWorstAverageTotal
// Description:		Calculates the best, worst, average and total fitnesses
//
void 
GeneticAlgorithm::CalculateBestWorstAverageTotal(void)
{
	m_TotalFitness = 0;

	double highestSoFar = 0;
	double lowestSoFar = 9999999;

	for (unsigned int i = 0; i < m_PopulationSize; ++i)
	{
		if (m_Population[i].GetFitness() > highestSoFar)
		{
			highestSoFar = m_Population[i].GetFitness();

			m_FittestGenome = i;
			m_BestFitness = highestSoFar;
		}

		if (m_Population[i].GetFitness() < lowestSoFar)
		{
			lowestSoFar = m_Population[i].GetFitness();
			m_WorstFitness = lowestSoFar;
		}

		m_TotalFitness += m_Population[i].GetFitness();
	}

	m_AverageFitness += m_TotalFitness / m_PopulationSize;
}
//
// Method:			GrabNBest
// Description:		Grabs the N best populace
// Parameters:
//		(IN)				_nBest, number of best
//		(IN)				_numCopies, number of copies
//		(OUT)			_population, current population
//
void 
GeneticAlgorithm::GrabNBest(int _nBest, const int _numCopies, std::vector<Genome>& _population)
{
	while (_nBest--)
	{
		for (unsigned int i = 0; i < _numCopies; ++i)
		{
			_population.push_back(m_Population[(m_PopulationSize - 1) - _nBest]);
		}
	}
}
//
// Method:			GetChromosomeRoulette
// Description:		Gets chromosomes from Roulette selection
// Returns:			Genome, Selected Genome
//
Genome 
GeneticAlgorithm::GetChromosomeRoulette(void)
{
	Genome selected;
	double slice = (double)((rand() / RAND_MAX + 1.0f) * m_TotalFitness);

	double currentFitness = 0;

	for (unsigned int i = 0; i < m_PopulationSize; ++i)
	{
		currentFitness += m_Population[i].GetFitness();

		if (currentFitness >= slice)
		{
			selected = m_Population[i];
			break;
		}
	}
	return selected;
}