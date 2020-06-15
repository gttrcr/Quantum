#pragma once

#include"Qbit.h"
#include"Topology.h"

struct Circuit
{
public:
	Qbit* q;
	Topology* t;

	Circuit(unsigned int n)
	{
		q = new Qbit[n];
		t = new Topology();
	}
};

void I(Circuit* c, unsigned int a)
{
	if (CIRCUIT_LOGS)
		std::cout << "I in register " << a << "...";

	(c->q + a)->I();
	c->t->AddStep("I", a);

	if (CIRCUIT_LOGS)
		std::cout << "Done" << std::endl;
}

void X(Circuit* c, unsigned int a)
{
	if (CIRCUIT_LOGS)
		std::cout << "X in register " << a << "...";

	(c->q + a)->X();
	c->t->AddStep("X", a);

	if (CIRCUIT_LOGS)
		std::cout << "Done" << std::endl;
}

void Y(Circuit* c, unsigned int a)
{
	if (CIRCUIT_LOGS)
		std::cout << "Y in register " << a << "...";

	(c->q + a)->Y();
	c->t->AddStep("Y", a);

	if (CIRCUIT_LOGS)
		std::cout << "Done" << std::endl;
}

void Z(Circuit* c, unsigned int a)
{
	if (CIRCUIT_LOGS)
		std::cout << "Z in register " << a << "...";

	(c->q + a)->Z();
	c->t->AddStep("Z", a);

	if (CIRCUIT_LOGS)
		std::cout << "Done" << std::endl;
}

void H(Circuit* c, unsigned int a)
{
	if (CIRCUIT_LOGS)
		std::cout << "H in register " << a << "...";

	(c->q + a)->H();
	c->t->AddStep("H", a);

	if (CIRCUIT_LOGS)
		std::cout << "Done" << std::endl;
}

void R(Circuit* c, unsigned int a, _Complex angle)
{
	if (CIRCUIT_LOGS)
		std::cout << "R in register " << a << "...";

	(c->q + a)->R(angle);
	c->t->AddStep("R", a);

	if (CIRCUIT_LOGS)
		std::cout << "Done" << std::endl;
}

void CX(Circuit* c, unsigned int a, unsigned int b)
{
	if (CIRCUIT_LOGS)
		std::cout << "CX between " << a << " and " << b << "...";

	(c->q + a)->CX(*(c->q + b));
	c->t->AddStep("CX", a, b);

	if (CIRCUIT_LOGS)
		std::cout << "Done" << std::endl;
}

void CY(Circuit* c, unsigned int a, unsigned int b)
{
	if (CIRCUIT_LOGS)
		std::cout << "CY between " << a << " and " << b << "...";

	(c->q + a)->CY(*(c->q + b));
	c->t->AddStep("CY", a, b);

	if (CIRCUIT_LOGS)
		std::cout << "Done" << std::endl;
}

void CZ(Circuit* c, unsigned int a, unsigned int b)
{
	if (CIRCUIT_LOGS)
		std::cout << "CZ between " << a << " and " << b << "...";

	(c->q + a)->CZ(*(c->q + b));
	c->t->AddStep("CZ", a, b);

	if (CIRCUIT_LOGS)
		std::cout << "Done" << std::endl;
}

void Swap(Circuit* c, unsigned int a, unsigned int b)
{
	if (CIRCUIT_LOGS)
		std::cout << "Swap between " << a << " and " << b << "...";

	(c->q + a)->Swap(*(c->q + b));
	c->t->AddStep("SWAP", a, b);

	if (CIRCUIT_LOGS)
		std::cout << "Done" << std::endl;
}

void Optimize(Circuit* c)
{
	if (CIRCUIT_LOGS)
		std::cout << "Start optimization...";

	c->t->Optimize();

	if (CIRCUIT_LOGS)
		std::cout << "Done" << std::endl;
}

void Info(Circuit* c, bool print = false, bool draw = false)
{
	std::cout << "Determinant is: " << systemMatrix->Det() << std::endl;
	std::cout << "Trace is: " << systemMatrix->Trace() << std::endl;

	if (print)
		systemMatrix->Print();

	if (draw)
		Frame::CreateFromMatrix<_Complex>(systemMatrix, "frame.bmp", true);
}