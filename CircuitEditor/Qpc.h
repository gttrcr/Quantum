#pragma once

class Qpc
{
public:
	Qpc()
	{
		systemMatrix = new IMatrix;
		_qregSize = 0;
	}

	void AddQbit(Qbit* q)
	{
		systemMatrix = systemMatrix->KroneckerProduct(&IMatrix);
		_qregSize++;

		if (qArray == nullptr)
		{
			qArray = new Qbit;
			qArray = q;
		}
		else
			*(qArray + _qregSize) = *q;
	}

	bool Compare(Qpc * qpc)
	{
		if (systemMatrix == qpc->systemMatrix)
			return true;
		return false;
	}

private:
	_Matrix* systemMatrix;
	unsigned int _qregSize;
	Qbit* qArray;
};