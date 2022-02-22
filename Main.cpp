#include "Problem.h"
#include "Optimizer.h"
#include "Timer.h"
#include "CIndividual.h"
#include <random>
#include <exception>
#include <iostream>


using namespace TimeCounters;

using namespace std;

#define dMAX_TIME 20 * 60


void vRunExperiment(CProblem *pcProblem)
{
	try
	{
		CTimeCounter c_time_counter;

		double d_time_passed;

		COptimizer c_optimizer(pcProblem);

		c_time_counter.vSetStartNow();


		c_optimizer.vInitialize();

		c_time_counter.bGetTimePassed(&d_time_passed);

		while (d_time_passed <= dMAX_TIME)
		{
			c_optimizer.vRunIteration();
			cout<<c_optimizer.pcGetBestFound()->iGetFitness()<<endl;


			c_time_counter.bGetTimePassed(&d_time_passed);
		}

	}
	catch (exception &c_exception)
	{
		cout << c_exception.what() << endl;
	}
}


void main(int iArgCount, char **ppcArgValues)
{
	CProblem c_problem;
	string file = "C:/Users/DELL-PRECISION 3510/Desktop/max3sat/50/m3s_50_0.txt";
	
	//int i = 0;
	//while (i <= 10000)
	//{
	//	c_optimizer.vRunIteration();
	//	i++;
	//}

	//cout<<endl<<c_optimizer.pcGetBestFound()->getFitness();

	
	
	if (c_problem.bLoad(file) == true)
	{
		vRunExperiment(&c_problem);
	}
	


}