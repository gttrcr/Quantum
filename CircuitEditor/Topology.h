#pragma once

#include<vector>
#include"Utils.h"

struct Step
{
public:
	std::string _gateName;
	unsigned int _a;
	unsigned int _b;
	unsigned int _c;
	unsigned int _d;
	unsigned int _e;
	unsigned int _f;

	Step(std::string gateName, unsigned int a = -1, unsigned int b = -1, unsigned int c = -1, unsigned int d = -1, unsigned int e = -1, unsigned int f = -1)
	{
		_gateName = gateName;
		_a = a;
		_b = b;
		_c = c;
		_d = d;
		_e = e;
		_f = f;
	}
};

class Topology
{
private:
	std::vector<Step>* _circuit;

public:
	Topology()
	{
		_circuit = new std::vector<Step>();
	}

	void AddStep(std::string gateName, unsigned int a = -1, unsigned int b = -1, unsigned int c = -1, unsigned int d = -1, unsigned int e = -1, unsigned int f = -1)
	{
		Step step(gateName, a, b, c, d, e, f);
		_circuit->push_back(step);
	}

	void Optimize()
	{
		unsigned int realNumberOfReg = 0;
		for (unsigned int nStep = 0; nStep < _circuit->size(); nStep++)
		{
			Step step = (*_circuit)[nStep];
			realNumberOfReg = Utils::Max<unsigned int>(7, step._a, step._b, step._c, step._d, step._e, step._f, realNumberOfReg);
		}

		//Add optimizer

		for (unsigned int nStep = 1; nStep < _circuit->size(); nStep++)
		{
			for (unsigned int reg = 0; reg < realNumberOfReg; reg++)
			{

			}
		}
	}
};