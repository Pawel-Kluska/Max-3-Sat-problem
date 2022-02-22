#include "Optimizer.h"


using namespace std;

mt19937 COptimizer::c_rand_engine(time(nullptr));

COptimizer::COptimizer(CProblem *pcProblem) 
{
	pc_problem = pcProblem;
}

COptimizer::~COptimizer() 
{
	delete pc_best_found;

	for (int i = 0; i < v_population.size(); i++)
	{
		delete v_population[i];
	}

}

void COptimizer::vInitialize()
{
	vInitialize(POPULATION, PR_OF_CROS, PR_OF_MUT);
}

void COptimizer::vInitialize(int population, double probabilityOfCross, double probabilityOfMut)
{
	CIndividual* solution;
	pc_best_found = new CIndividual(pc_problem->iGetNrVars());
	probOfCross = probabilityOfCross;
	probOfMut = probabilityOfMut;
	
	for (int i = 0; i < population; i++)
	{
		solution = new CIndividual(pc_problem->iGetNrVars());
		solution->vSetFitness(pc_problem->iCompute(solution));

		if (solution->iGetFitness() > pc_best_found->iGetFitness())
			delete pc_best_found;
			pc_best_found = new CIndividual(*solution);

		v_population.push_back(solution);

	}

}

void COptimizer::vRunIteration()
{
	vector<CIndividual*> newPopulation;
	CIndividual* parent1;
	CIndividual* parent2;
	CIndividual* child1;
	CIndividual* child2;
	vector<CIndividual*>* children;


	while (newPopulation.size() < v_population.size())
	{
		parent1 = pcChooseParent();
		parent2 = pcChooseParent();

		
		children = parent1->Crossover(parent2, probOfCross);
		child1 = (*children)[0];
		child2 = (*children)[1];

		child1->vMutation(probOfMut);
		child2->vMutation(probOfMut);

		child1->vSetFitness(pc_problem->iCompute(child1));
		child2->vSetFitness(pc_problem->iCompute(child2));

		if (child1->iGetFitness() > pc_best_found->iGetFitness())
		{
			delete pc_best_found;
			pc_best_found = new CIndividual(*child1);
		}

		if (child2->iGetFitness() > pc_best_found->iGetFitness())
		{
			delete pc_best_found;
			pc_best_found = new CIndividual(*child2);
		}

		newPopulation.push_back(child1);
		newPopulation.push_back(child2);

		delete children;
	}
 

	for (int i = 0; i < v_population.size(); i++)
	{
		delete v_population[i];
	}


	v_population = newPopulation;

}

CIndividual* COptimizer::pcGetBestFound() 
{ 
	return pc_best_found; 
}

CIndividual* COptimizer::pcChooseParent()
{
	CIndividual* parent1 = v_population[ c_rand_engine() % v_population.size() ];
	CIndividual* parent2 = v_population[ c_rand_engine() % v_population.size() ];

	if (parent1->iGetFitness() > parent2->iGetFitness()) return parent1;
	else return parent2;
}

