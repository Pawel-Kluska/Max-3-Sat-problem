#include "CIndividual.h"




mt19937 CIndividual::c_rand_engine(time(nullptr));

CIndividual::CIndividual(int var)
{

	pi_genotype = new int[var];
	i_nr_of_vars = var;

	for (int i = 0; i < i_nr_of_vars; i++)
	{
		pi_genotype[i] = c_rand_engine() % 2;
	}

}


CIndividual::CIndividual(CIndividual& pcOther)
{
	pi_genotype = new int[pcOther.i_nr_of_vars];

	for (int i = 0; i < pcOther.i_nr_of_vars; i++)
	{
		pi_genotype[i] = pcOther.pi_genotype[i];
	}

	i_nr_of_vars = pcOther.i_nr_of_vars;
	i_fitness = pcOther.i_fitness;
}

CIndividual::~CIndividual()
{
	delete[] pi_genotype;
}

vector<CIndividual*>* CIndividual::Crossover(CIndividual* pcOther, double probability)
{
	vector<CIndividual*>* v_children = new vector<CIndividual*>;

	v_children->push_back(new CIndividual(*this));
	v_children->push_back(new CIndividual(*pcOther));

	if (((double)c_rand_engine() / (double)RAN_MAX) < probability)
	{
		for (int ii = 0; ii < i_nr_of_vars; ii++)
		{
			if ((c_rand_engine() % 2) == 1)
			{
				(*v_children)[0]->pi_genotype[ii] = pcOther->pi_genotype[ii];
				(*v_children)[1]->pi_genotype[ii] = pi_genotype[ii];
			}
		}
	}

	return v_children;
}

void CIndividual::vMutation(double p)
{
	for (int i = 0; i < i_nr_of_vars; i++)
	{
		
		if (((double)c_rand_engine() / (double) RAN_MAX) < p)
		{
			if (pi_genotype[i] == 1)
				pi_genotype[i] = 0;
			else
				pi_genotype[i] = 1;
		}
	}
}


int CIndividual::iGetFitness()
{
	return i_fitness;
}

void CIndividual::vSetFitness(int f)
{
	i_fitness = f;
}

int* CIndividual::piGetSolution()
{
	return pi_genotype;
}

void CIndividual::vSetSolution(int* pi_other)
{
	if (pi_genotype == nullptr) delete pi_genotype;
	pi_genotype = pi_other;
}


void CIndividual::toString()
{
	for (int i = 0; i < i_nr_of_vars; i++)
	{
		cout << "var " << i << "= " << pi_genotype[i] << endl;
	}
	cout << endl;
}