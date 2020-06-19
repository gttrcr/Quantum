#pragma once

#include"QbitWrapper.h"

class QAlgh
{
public:
	static void Reverse(Circuit* c)
	{
		for (unsigned int i = 0; i < c->circuitSize / 2; i++)
		{
			CX(c, i, c->circuitSize - i - 1);
			CX(c, c->circuitSize - i - 1, i);
			CX(c, i, c->circuitSize - i - 1);
		}
	}
};