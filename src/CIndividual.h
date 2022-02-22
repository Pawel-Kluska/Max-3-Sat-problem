#pragma once

#include "Const.h"

#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <iostream>

using namespace std;


class CIndividual
{
public:
	CIndividual(int var);
	CIndividual(CIndividual &pcOther);
	virtual ~CIndividual();

	void vSetSolution(int* s);
	int* piGetSolution();
	vector<CIndividual*>* CIndividual::Crossover(CIndividual* pcOther, double probability);
	void vMutation(double p);
	int iGetFitness();
	void vSetFitness(int f);

	void toString();


private:
	int* pi_genotype;
	int i_nr_of_vars;
	int i_fitness;
	static mt19937 c_rand_engine;
};


