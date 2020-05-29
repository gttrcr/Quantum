#pragma once

#include<vector>

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

	void AddStep(std::string gateName, unsigned int a)
	{
		Step step(gateName, a);
		_circuit->push_back(step);
	}

	void AddStep(std::string gateName, unsigned int a, unsigned int b)
	{
		Step step(gateName, a, b);
		_circuit->push_back(step);
	}

	void AddStep(std::string gateName, unsigned int a, unsigned int b, unsigned int c)
	{
		Step step(gateName, a, b, c);
		_circuit->push_back(step);
	}

	void Optimize()
	{
		//Add optimizer
	}
};