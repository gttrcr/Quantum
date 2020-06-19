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

public:
	Qbit()
	{
		if (systemMatrix == nullptr)
		{
			systemMatrix = new IMatrix;
			qregSize = 1;
		}
		else
		{
			systemMatrix = systemMatrix->KroneckerProduct(&IMatrix);
			qregSize++;
		}

		_alpha = new _Complex(1, 0);
		_beta = new _Complex(0, 0);
		_positionInRegister = qregSize - 1;
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

		throw std::exception("Not implemented");

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

		throw std::exception("Not implemented");

		systemMatrixUnitaryCheckMutex.unlock();
	}

	void CZ(Qbit q)
	{
		systemMatrixUnitaryCheckMutex.lock();

		throw std::exception("Not implemented");

		systemMatrixUnitaryCheckMutex.unlock();
	}

	void Toffoli(Qbit q1, Qbit q2)
	{
		systemMatrixUnitaryCheckMutex.lock();

		throw std::exception("Not implemented");

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

		throw std::exception("Not implemented");

		systemMatrixUnitaryCheckMutex.unlock();
	}
};