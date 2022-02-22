#include "Clause.h"

using namespace std;

CClause::CClause()
{
	
}

CClause::~CClause()
{
	for (int i = 0; i < clause.size(); i++)
	{
		delete clause[i];
	}
}

int CClause::iCompute(int* solution)
{
	int qualityOfOneSet = 0;
	CVariable* currVariable;
	for (int i = 0; i < clause.size() && qualityOfOneSet == 0; i++)
	{
		currVariable = clause[i];
		if (currVariable->getNeg() == true)
			qualityOfOneSet += normalizeNumber(solution[currVariable->getVal()]);
		else qualityOfOneSet += solution[currVariable->getVal()];
	}
	return qualityOfOneSet;
}

int CClause::normalizeNumber(int n)
{
	if (n = 0) return 1;
	if (n = 1) return 0;
	else return 0;
}

CVariable* CClause::getVar(int i)
{
	return clause[i];
}

void CClause::addVar(CVariable* var)
{
	clause.push_back(var);
}

int CClause::getSize()
{
	return clause.size();
}


CVariable::CVariable(int v, bool n)
{
	var = v;
	isNegative = n;
}

CVariable::~CVariable()
{

}

int CVariable::getVal()
{
	return var;
}

bool CVariable::getNeg()
{
	return isNegative;
}


