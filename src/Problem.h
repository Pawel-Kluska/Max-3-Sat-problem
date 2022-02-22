#pragma once

#include "CIndividual.h"
#include "Clause.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>


using namespace std;



class CProblem
{
public:
	CProblem();
	
	~CProblem();

	bool bLoad(std::string sSourcePath);

	int iCompute(CIndividual *pdGenotype);

	void vShowSets();

	int iGetNrVars();

private:
	string sFile;
	vector<CClause*> allClauses;
	int nrOfVars;

	void vGetNumberVariables();
	CClause* pcExtractNumbers(vector<string>* line);

};



