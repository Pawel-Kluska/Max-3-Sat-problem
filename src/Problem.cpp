#include "Problem.h"



using namespace std;

CProblem::CProblem() {

}

CProblem::~CProblem() {

	for (int i = 0; i < allClauses.size(); i++)
	{
		delete allClauses[i];
	}

}

bool CProblem::bLoad(std::string sSourcePath) {
	

	fstream stream;
	stream.open(sSourcePath);
	
	if (stream.good())
	{
		vector<string>* lines = new vector<string>;
		(*lines).push_back("");
		(*lines).push_back("");

		sFile = sSourcePath;

		do
		{
			getline(stream, (*lines)[0]);
			getline(stream, (*lines)[1]);

			if ((*lines)[0] != "" && (*lines)[1] != "")
				allClauses.push_back(pcExtractNumbers(lines));
			
		} while ((*lines)[0] != "" && (*lines)[1] != "");

		delete lines;
		vGetNumberVariables();

		return true;
	}
	
	return false;
}

CClause* CProblem::pcExtractNumbers(vector<string>* line)
{
	CClause* clause = new CClause();
	string number = "";

	for (int j = 0; j < line->size(); j++)
	{

		for (int i = 0; i < (*line)[j].length(); i++)
		{

			if ((*line)[j][i] == '-')
			{
				i++;
				while (isdigit((*line)[j][i]))
				{
					number += (*line)[j][i];
					i++;
				}
				clause->addVar(new CVariable(stoi(number), true));
				number = "";
			}


			if (isdigit((*line)[j][i]))
			{
				while (isdigit((*line)[j][i]))
				{
					number += (*line)[j][i];
					i++;
				}
				clause->addVar(new CVariable(stoi(number), false));
				number = "";
			}
		}
	}

	return clause;
}


void CProblem::vGetNumberVariables()
{
	int n = allClauses[0]->getVar(0)->getVal();

	for (int i = 0; i < allClauses.size(); i++)
	{
		for (int j = 0; j < allClauses[i]->getSize(); j++)
		{
			if (allClauses[i]->getVar(j)->getVal() > n)
				n = allClauses[i]->getVar(j)->getVal();
		}
	}

	nrOfVars = n+1;
}

int CProblem::iCompute(CIndividual *pdGenotype)
{

	int* solution = pdGenotype->piGetSolution();
	int quality = 0;
	int qualityOfOneSet = 0;

	for (int i = 0; i < allClauses.size(); i++)
	{
		qualityOfOneSet = allClauses[i]->iCompute(solution);

		if (qualityOfOneSet > 0)
			quality++;

		qualityOfOneSet = 0;
	}

	return(quality);
}

void CProblem::vShowSets()
{
	for (int i = 0; i < allClauses.size(); i++)
	{
		for (int j = 0; j < allClauses[i]->getSize(); j++)
		{
			if (allClauses[i]->getVar(j)->getNeg() == true)
				cout << "-" << allClauses[i]->getVar(j)->getVal() << " ";
			else
				cout << allClauses[i]->getVar(j)->getVal()<<" ";
		}
		cout << endl;
	}
}

int CProblem::iGetNrVars()
{
	return nrOfVars;
}