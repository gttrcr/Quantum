#pragma once

#include<thread>
#include<mutex>
#include<sstream>

#include"Complex.h"
#include"Matrix.h"
#include"Define.h"

static _Matrix* systemMatrix;
static unsigned int qregSize;
std::mutex systemMatrixUnitaryCheckMutex;

class Qbit
{
private:
	_Complex* _alpha;
	_Complex* _beta;
	unsigned int _positionInRegister;
	std::thread* _checkThread;
	bool _runThread;

	void checkThread()
	{
		while (_runThread)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(CheckThreadDelay));

			systemMatrixUnitaryCheckMutex.lock();

			_Type modDet = _Complex(systemMatrix->Det()).Mod();
			if (!Utils<_Type>::RangeEquality(modDet, 1.0))
			{
				std::ostringstream strs;
				strs << modDet;
				std::string text = "Determinant of systemMatrix is " + strs.str() + " which is not 1";
				throw new std::exception(text.c_str());
			}

			systemMatrixUnitaryCheckMutex.unlock();
		}
	}

public:
	Qbit()
	{
		if (systemMatrix == nullptr)
		{
			systemMatrix = new IMatrix;
			qregSize = 1;
			_checkThread = new std::thread(&Qbit::checkThread, this);
		}
		else
		{
			systemMatrix = systemMatrix->KroneckerProduct(&IMatrix);
			qregSize++;
		}

		_alpha = new _Complex(1, 0);
		_beta = new _Complex(0, 0);
		_positionInRegister = qregSize - 1;
		_runThread = true;
	}

	void I()
	{
		systemMatrixUnitaryCheckMutex.lock();
		
		_Matrix* stepMatrix = _Matrix::KroneckerProduct(_positionInRegister);
		stepMatrix = stepMatrix->KroneckerProduct(&IMatrix);
		stepMatrix = stepMatrix->KroneckerProduct(_Matrix::KroneckerProduct((qregSize - _positionInRegister - 1)));
		systemMatrix = systemMatrix->DotProduct(stepMatrix);

		systemMatrixUnitaryCheckMutex.unlock();
	}

	void X()
	{
		systemMatrixUnitaryCheckMutex.lock();
		
		_Matrix* stepMatrix = _Matrix::KroneckerProduct(_positionInRegister);
		stepMatrix = stepMatrix->KroneckerProduct(&XMatrix);
		stepMatrix = stepMatrix->KroneckerProduct(_Matrix::KroneckerProduct((qregSize - _positionInRegister - 1)));
		systemMatrix = systemMatrix->DotProduct(stepMatrix);

		systemMatrixUnitaryCheckMutex.unlock();
	}

	void Y()
	{
		systemMatrixUnitaryCheckMutex.lock();

		_Matrix* stepMatrix = _Matrix::KroneckerProduct(_positionInRegister);
		stepMatrix = stepMatrix->KroneckerProduct(&YMatrix);
		stepMatrix = stepMatrix->KroneckerProduct(_Matrix::KroneckerProduct((qregSize - _positionInRegister - 1)));
		systemMatrix = systemMatrix->DotProduct(stepMatrix);

		systemMatrixUnitaryCheckMutex.unlock();
	}

	void Z()
	{
		systemMatrixUnitaryCheckMutex.lock();
		
		_Matrix* stepMatrix = _Matrix::KroneckerProduct(_positionInRegister);
		stepMatrix = stepMatrix->KroneckerProduct(&ZMatrix);
		stepMatrix = stepMatrix->KroneckerProduct(_Matrix::KroneckerProduct((qregSize - _positionInRegister - 1)));
		systemMatrix = systemMatrix->DotProduct(stepMatrix);
		
		systemMatrixUnitaryCheckMutex.unlock();
	}

	void H()
	{
		systemMatrixUnitaryCheckMutex.lock();
		
		_Matrix* stepMatrix = _Matrix::KroneckerProduct(_positionInRegister);
		stepMatrix = stepMatrix->KroneckerProduct(&HMatrix);
		stepMatrix = stepMatrix->KroneckerProduct(_Matrix::KroneckerProduct((qregSize - _positionInRegister - 1)));
		systemMatrix = systemMatrix->DotProduct(stepMatrix);

		systemMatrixUnitaryCheckMutex.unlock();
	}

	void R(_Complex ang)
	{
		systemMatrixUnitaryCheckMutex.lock();

		//todo

		systemMatrixUnitaryCheckMutex.unlock();
	}

	void CX(Qbit q)
	{
		systemMatrixUnitaryCheckMutex.lock();
		
		_Matrix* stepMatrix = CalculateCXMatrix<_Complex>(qregSize, q._positionInRegister, _positionInRegister);
		systemMatrix = systemMatrix->DotProduct(stepMatrix);

		systemMatrixUnitaryCheckMutex.unlock();
	}

	void CY(Qbit q)
	{
		systemMatrixUnitaryCheckMutex.lock();

		//

		systemMatrixUnitaryCheckMutex.unlock();
	}

	void CZ(Qbit q)
	{
		systemMatrixUnitaryCheckMutex.lock();

		//

		systemMatrixUnitaryCheckMutex.unlock();
	}

	void Swap(Qbit q)
	{
		CX(q);
		q.CX(*this);
		CX(q);
	}

	void Measure()
	{
		systemMatrixUnitaryCheckMutex.lock();

		//

		systemMatrixUnitaryCheckMutex.unlock();
	}
};