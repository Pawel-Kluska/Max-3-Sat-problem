#pragma once
#include <vector>

using namespace std;

class CVariable
{
public:
	CVariable(int v, bool n);
	~CVariable();
	int getVal();
	bool getNeg();

private:
	int var;
	bool isNegative;

};

class CClause
{
public:
	CClause();
	~CClause();
	CVariable* getVar(int i);
	void addVar(CVariable* var);
	int getSize();
	int iCompute(int* solution);
	int normalizeNumber(int n);

private:
	vector<CVariable*> clause;

};