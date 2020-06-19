#pragma once

#include <string>
#include <chrono>

#include"Qbit.h"
#include"Topology.h"
#include"Frame.h"
#include"CircuitDraw.h"

struct Circuit
{
public:
	unsigned int circuitSize;
	Qbit* q;
	Topology* t;

	Circuit(unsigned int n)
	{
		circuitSize = n;
		q = new Qbit[n];
		t = new Topology();
	}
};

Circuit* InitQuantumRegister(unsigned int reg)
{
	if (CIRCUIT_LOGS)
		std::cout << "Creating circuit of " << reg << " quantum registers...";
	
	Circuit* c = new Circuit(reg);
	
	if (CIRCUIT_LOGS)
		std::cout << "Done" << std::endl;

	return c;
}

std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
void StartLog()
{
	if (CIRCUIT_LOGS)
	{
		std::cout << "CircuitEditor started" << std::endl;
		std::cout << "Default datatype: " << sizeof(_Type) << std::endl;
		std::cout << "MAX_BIT_SIZE: " << std::to_string(MAX_BIT_SIZE) << std::endl;
		std::cout << "THREADS_NUMBER: " << std::to_string(THREADS_NUMBER) << std::endl;
		std::cout << "USE_THREADS: " << (USE_THREADS ? "true" : "false") << std::endl;
		std::cout << "CIRCUIT_LOGS: " << (CIRCUIT_LOGS ? "true" : "false") << std::endl;
		std::cout << "MonitoringThreadDelay: " << MonitoringThreadDelay << std::endl;
		std::cout << "----------" << std::endl;
	}
}

void EndLog()
{
	if (CIRCUIT_LOGS)
	{
		long long mills = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
		std::cout << "The circuit has been created in " << mills << "ms" << std::endl;
	}
}

void I(Circuit* c, unsigned int a)
{
	if (CIRCUIT_LOGS)
		std::cout << "I in register " << a << "...";

	(c->q + a)->I();
	c->t->AddStep("I", a);
	CircuitDraw::DrawGate1Q(a, "I");

	if (CIRCUIT_LOGS)
		std::cout << "Done" << std::endl;
}

void X(Circuit* c, unsigned int a)
{
	if (CIRCUIT_LOGS)
		std::cout << "X in register " << a << "...";

	(c->q + a)->X();
	c->t->AddStep("X", a);
	CircuitDraw::DrawGate1Q(a, "X");

	if (CIRCUIT_LOGS)
		std::cout << "Done" << std::endl;
}

void Y(Circuit* c, unsigned int a)
{
	if (CIRCUIT_LOGS)
		std::cout << "Y in register " << a << "...";

	(c->q + a)->Y();
	c->t->AddStep("Y", a);
	CircuitDraw::DrawGate1Q(a, "Y");

	if (CIRCUIT_LOGS)
		std::cout << "Done" << std::endl;
}

void Z(Circuit* c, unsigned int a)
{
	if (CIRCUIT_LOGS)
		std::cout << "Z in register " << a << "...";

	(c->q + a)->Z();
	c->t->AddStep("Z", a);
	CircuitDraw::DrawGate1Q(a, "Z");

	if (CIRCUIT_LOGS)
		std::cout << "Done" << std::endl;
}

void H(Circuit* c, unsigned int a)
{
	if (CIRCUIT_LOGS)
		std::cout << "H in register " << a << "...";

	(c->q + a)->H();
	c->t->AddStep("H", a);
	CircuitDraw::DrawGate1Q(a, "H");

	if (CIRCUIT_LOGS)
		std::cout << "Done" << std::endl;
}

void R(Circuit* c, unsigned int a, _Complex angle)
{
	if (CIRCUIT_LOGS)
		std::cout << "R in register " << a << "...";

	(c->q + a)->R(angle);
	c->t->AddStep("R", a);
	CircuitDraw::DrawGate1Q(a, "R");

	if (CIRCUIT_LOGS)
		std::cout << "Done" << std::endl;
}

void CX(Circuit* c, unsigned int a, unsigned int b)
{
	if (CIRCUIT_LOGS)
		std::cout << "CX between " << a << " and " << b << "...";

	(c->q + a)->CX(*(c->q + b));
	c->t->AddStep("CX", a, b);
	CircuitDraw::DrawGate2Q(a, b, "CX");

	if (CIRCUIT_LOGS)
		std::cout << "Done" << std::endl;
}

void CY_(Circuit* c, unsigned int a, unsigned int b)
{
	if (CIRCUIT_LOGS)
		std::cout << "CY between " << a << " and " << b << "...";

	(c->q + a)->CY(*(c->q + b));
	c->t->AddStep("CY", a, b);
	CircuitDraw::DrawGate2Q(a, b, "CY");

	if (CIRCUIT_LOGS)
		std::cout << "Done" << std::endl;
}

void CZ(Circuit* c, unsigned int a, unsigned int b)
{
	if (CIRCUIT_LOGS)
		std::cout << "CZ between " << a << " and " << b << "...";

	(c->q + a)->CZ(*(c->q + b));
	c->t->AddStep("CZ", a, b);
	CircuitDraw::DrawGate2Q(a, b, "CZ");

	if (CIRCUIT_LOGS)
		std::cout << "Done" << std::endl;
}

void Toffoli(Circuit* c, unsigned int a, unsigned int b, unsigned int c_)
{
	if (CIRCUIT_LOGS)
		std::cout << "Toffoli between " << a << ", " << b << " and " << c << "...";

	(c->q + a)->Toffoli(*(c->q + b), *(c->q + c_));
	c->t->AddStep("Toffoli", b, c_);
	CircuitDraw::DrawGate3Q(a, b, c_, "Toff");

	if (CIRCUIT_LOGS)
		std::cout << "Done" << std::endl;
}

void Swap(Circuit* c, unsigned int a, unsigned int b)
{
	if (CIRCUIT_LOGS)
		std::cout << "Swap between " << a << " and " << b << "...";

	(c->q + a)->Swap(*(c->q + b));
	c->t->AddStep("SWAP", a, b);
	CircuitDraw::DrawGate2Q(a, b, "SWAP");

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
	//std::cout << "Determinant is: " << systemMatrix->Det() << std::endl;
	//std::cout << "Trace is: " << systemMatrix->Trace() << std::endl;
	std::cout << "Rows: " << systemMatrix->GetRows() << std::endl;
	std::cout << "Cols: " << systemMatrix->GetCols() << std::endl;
	std::cout << "Size (rows*cols): " << systemMatrix->GetRows() * systemMatrix->GetCols() << std::endl;

	if (print)
		systemMatrix->Print();

	if (draw)
		Frame::CreateFromMatrix<_Complex>(systemMatrix, "frame.bmp", true);
}