#pragma once

#include<iostream>

unsigned int gateStep = 0;
unsigned int maxReg = 0;

class CircuitDraw
{
public:
	static void DrawGate1Q(unsigned int reg, std::string name = "")
	{
		if (reg > maxReg)
			maxReg = reg;

		Utils::GotoXY(gateStep * (_width + _spaceBetweenWidth), reg * (_height + _spaceBetweenHeight));

		std::cout << "+";
		for (unsigned int i = 0; i < _width - 2; i++)
			std::cout << "-";
		std::cout << "+\n";

		for (unsigned int i = 0; i < _height - 2; i++)
		{
			Utils::GotoXY(gateStep * (_width + _spaceBetweenWidth), reg * (_height + _spaceBetweenHeight) + 1 + i);
			std::cout << "|";
			for (unsigned int j = 0; j < _width - 2; j++)
				std::cout << " ";
			std::cout << "|\n";
		}

		Utils::GotoXY(gateStep * (_width + _spaceBetweenWidth), reg * (_height + _spaceBetweenHeight) + _height - 1);
		std::cout << "+";
		for (unsigned int i = 0; i < _width - 2; i++)
			std::cout << "-";
		std::cout << "+\n";

		Utils::GotoXY(gateStep * (_width + _spaceBetweenWidth) + _width / 2 - name.length() / 2, reg * (_height + _spaceBetweenHeight) + _height / 2);
		std::cout << name;

		gateStep++;

		//At the end always go to the last line
		Utils::GotoXY(gateStep * (_width + _spaceBetweenWidth), 0);
	}

	static void DrawGate2Q(unsigned int reg1, unsigned int reg2, std::string name = "")
	{
		DrawGate1Q(reg1, name);
		gateStep--;
		DrawConnection(reg1, reg2);
		DrawCheck(reg2, reg1 < reg2);
	}

	static void DrawGate3Q(unsigned int reg1, unsigned int reg2, unsigned int reg3, std::string name = "")
	{
		DrawGate1Q(reg1, name);
		gateStep--;
		DrawConnection(reg1, reg2);
		DrawCheck(reg2, reg1 < reg2);
		gateStep--;
		DrawConnection(reg2, reg3);
		DrawCheck(reg3, reg2 < reg3);
	}

	static void DrawGateNQ(unsigned int reg[], std::string name = "")
	{
		unsigned int nQ = sizeof(reg) / sizeof(reg[0]);
		DrawGate1Q(reg[0], name);
		for (unsigned int i = 0; i < nQ - 1; i++)
		{
			gateStep--;
			DrawCheck(reg[i + 1], reg[i] < reg[i + 1]);
			DrawConnection(reg[i], reg[i + 1]);
		}

		DrawCheck(reg[nQ - 1], reg[nQ - 2] < reg[nQ - 1]);
	}

	//The initial position of the cursor
	static void StartPosition()
	{

	}

	//Return to the beginning of the terminal
	static void GoToWritingPosition()
	{

	}

private:
	static const unsigned int _width = 7;
	static const unsigned int _height = 3;
	static const unsigned int _spaceBetweenWidth = 1;
	static const unsigned int _spaceBetweenHeight = 1;

	static void DrawCheck(unsigned int reg, bool upper)
	{
		Utils::GotoXY(gateStep * (_width + _spaceBetweenWidth) + _width / 2, reg * (_height + _spaceBetweenHeight) + _height / 2 + (upper ? -1 : 1));
		std::cout << "|";
		Utils::GotoXY(gateStep * (_width + _spaceBetweenWidth) + _width / 2, reg * (_height + _spaceBetweenHeight) + _height / 2);
		std::cout << "x";
		gateStep++;

		//At the end always go to the last line
		Utils::GotoXY(gateStep * (_width + _spaceBetweenWidth), 0);
	}

	static void DrawConnection(unsigned int reg1, unsigned int reg2)
	{
		unsigned int minReg = min(reg1, reg2);
		unsigned int maxReg = max(reg1, reg2);

		for (unsigned int i = minReg; i < maxReg - 1; i++)
		{
			for (unsigned int h = 0; h < _height + _spaceBetweenHeight; h++)
			{
				Utils::GotoXY(gateStep * (_width + _spaceBetweenWidth) + _width / 2, i * (_height + _spaceBetweenHeight) + _height + h);
				std::cout << "|";
			}
		}

		for (unsigned int h = 0; h < _spaceBetweenHeight; h++)
		{
			Utils::GotoXY(gateStep * (_width + _spaceBetweenWidth) + _width / 2, (maxReg - 1) * (_height + _spaceBetweenHeight) + _height + h);
			std::cout << "|";
		}
	}
};