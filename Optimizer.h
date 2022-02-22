#pragma once

#include "Problem.h"
#include "CIndividual.h"
#include "Const.h"

#include <random>
#include <ctime>
#include <vector>
#include <iostream>



using namespace std;

class COptimizer
{
public:
	COptimizer(CProblem *pcProblem);

	~COptimizer();

	void vInitialize(int population, double probabilityOfCross, double probabilityOfMut);
	void vInitialize();
	void vRunIteration();
	
	CIndividual  *pcGetBestFound();

private:

	int* COptimizer::piGetTabWhichGene();
	CIndividual* pcChooseParent();

	CProblem *pc_problem;
	static mt19937 c_rand_engine;
	CIndividual  *pc_best_found;

	double probOfMut;
	double probOfCross;

	vector<CIndividual *> v_population;
};//class COptimizer

