#pragma once

#include"Complex.h"
#include"Matrix.h"
#include"Define.h"

static _Matrix* systemMatrix;
static unsigned int _qregSize;

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
			_qregSize = 1;
		}
		else
		{
			systemMatrix = systemMatrix->KroneckerProduct(&IMatrix);
			_qregSize++;
		}

		_alpha = new _Complex(1, 0);
		_beta = new _Complex(0, 0);
		_positionInRegister = _qregSize - 1;
	}

	void I()
	{
		_Matrix* stepMatrix = _Matrix::KroneckerProduct(_positionInRegister);
		stepMatrix = stepMatrix->KroneckerProduct(&IMatrix);
		stepMatrix = stepMatrix->KroneckerProduct(_Matrix::KroneckerProduct((_qregSize - _positionInRegister - 1)));
		systemMatrix = systemMatrix->DotProduct(stepMatrix);
	}

	void X()
	{
		_Matrix* stepMatrix = _Matrix::KroneckerProduct(_positionInRegister);
		stepMatrix = stepMatrix->KroneckerProduct(&XMatrix);
		stepMatrix = stepMatrix->KroneckerProduct(_Matrix::KroneckerProduct((_qregSize - _positionInRegister - 1)));
		systemMatrix = systemMatrix->DotProduct(stepMatrix);
	}

	void Y()
	{

	}

	void Z()
	{
		_Matrix* stepMatrix = _Matrix::KroneckerProduct(_positionInRegister);
		stepMatrix = stepMatrix->KroneckerProduct(&ZMatrix);
		stepMatrix = stepMatrix->KroneckerProduct(_Matrix::KroneckerProduct((_qregSize - _positionInRegister - 1)));
		systemMatrix = systemMatrix->DotProduct(stepMatrix);
	}

	void H()
	{
		_Matrix* stepMatrix = _Matrix::KroneckerProduct(_positionInRegister);
		stepMatrix = stepMatrix->KroneckerProduct(&HMatrix);
		stepMatrix = stepMatrix->KroneckerProduct(_Matrix::KroneckerProduct((_qregSize - _positionInRegister - 1)));
		systemMatrix = systemMatrix->DotProduct(stepMatrix);
	}

	void R(_Complex ang)
	{

	}

	void CX(Qbit q)
	{
		_Matrix* stepMatrix = CalculateCXMatrix<_Complex>(_qregSize, q._positionInRegister, _positionInRegister);
		systemMatrix = systemMatrix->DotProduct(stepMatrix);
	}

	void CY(Qbit q)
	{

	}

	void CZ(Qbit q)
	{

	}

	void Swap(Qbit q)
	{
		CX(q);
		q.CX(*this);
		CX(q);
	}

	void Measure()
	{

	}
};