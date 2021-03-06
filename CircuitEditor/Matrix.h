#pragma once

#include<bitset>
#include<iostream>
#include<thread>

#include"Define.h"

template<typename T>
class Matrix
{
public:
	//Constructor
	Matrix<T>(unsigned int rows, unsigned int cols)
	{
		_rows = rows;
		_cols = cols;

		_matrix = (T*)malloc((size_t)_rows * (size_t)_cols * sizeof(T));

		for (rows = 0; rows < _rows; rows++)
			for (cols = 0; cols < _cols; cols++)
				_set(rows, cols, {});
	}

	//Constructor
	Matrix<T>(unsigned int rows, unsigned int cols, std::initializer_list<T> args)
	{
		_rows = rows;
		_cols = cols;
		
		_matrix = (T*)malloc((size_t)_rows * (size_t)_cols * sizeof(T));

		for (rows = 0; rows < _rows; rows++)
			for (cols = 0; cols < _cols; cols++)
				_set(rows, cols, *(args.begin() + (_cols * rows + cols)));
	}

	//Constructor
	Matrix<T>(unsigned int rows, unsigned int cols, T* args)
	{
		_rows = rows;
		_cols = cols;
		
		_matrix = (T*)malloc((size_t)_rows * (size_t)_cols * sizeof(T));

		for (rows = 0; rows < _rows; rows++)
			for (cols = 0; cols < _cols; cols++)
				_set(rows, cols, *(args + (_cols * rows + cols)));
	}

	~Matrix<T>()
	{
		free(_matrix);
	}

	inline unsigned int GetRows()
	{
		return _rows;
	}

	inline unsigned int GetCols()
	{
		return _cols;
	}

	inline Matrix<T>* operator+(const Matrix<T>& matrix)
	{
		Matrix<T>* res = new Matrix<T>(_rows, _cols);

		for (unsigned int r = 0; r < _rows; r++)
			for (unsigned int c = 0; c < _cols; c++)
				res->_matrix[r][c] = _matrix[r][c] + matrix._matrix[r][c];

		return res;
	}

	inline Matrix<T>* operator*(const T& scalar)
	{
		Matrix<T>* res = new Matrix<T>(_rows, _cols);

		for (unsigned int r = 0; r < _rows; r++)
			for (unsigned int c = 0; c < _cols; c++)
				res->_set(r, c, Get(r, c) * scalar);

		return res;
	}

	//Matrix Kronecker product given size of matrix
	inline static Matrix<T>* KroneckerProduct(unsigned int size)
	{
		if (size == 0)
			return new Matrix<T>(1, 1, { 1 });

		Matrix<T>* result = new Matrix<T>(2, 2, { 1, 0, 0, 1 });
		for (; size > 0; size--)
			result = result->KroneckerProduct(new Matrix<T>(2, 2, { 1, 0, 0, 1 }));

		return result;
	}

	//Thread of dot product
	inline static void DotProductThread(Matrix<T>& res, const int threadNumber, Matrix<T>& _this, Matrix<T>& matrix)
	{
		unsigned int nElements = res._cols * res._rows;
		unsigned int nOperations = nElements / THREADS_NUMBER;
		unsigned int restOperations = nElements % THREADS_NUMBER;
		unsigned int startOp, endOp;

		if (threadNumber == 0) {
			startOp = nOperations * threadNumber;
			endOp = (nOperations * (threadNumber + 1)) + restOperations;
		}
		else {
			startOp = nOperations * threadNumber + restOperations;
			endOp = (nOperations * (threadNumber + 1)) + restOperations;
		}

		for (unsigned int op = startOp; op < endOp; ++op)
		{
			unsigned int row = op % res._cols;
			unsigned int col = op / res._rows;
			res._set(row, col, 0);
			for (unsigned int r = 0; r < res._rows; ++r)
				res._set(row, col, res.Get(row, col) + _this.Get(row, r) * matrix.Get(r, col));
		}
	}

	//Matrix dot product
	inline Matrix<T>* DotProduct(Matrix<T>* matrix)
	{
#if USE_THREADS
		Matrix<T>* res = new Matrix<T>(_rows, _cols);

		std::thread threads[THREADS_NUMBER];
		for (unsigned int i = 0; i < THREADS_NUMBER; ++i)
			threads[i] = std::thread(DotProductThread, std::ref(*res), i, std::ref(*this), std::ref(*matrix));

		for (unsigned int i = 0; i < THREADS_NUMBER; ++i)
			threads[i].join();

		return res;
#else
		Matrix<T>* res = new Matrix<T>(_rows, _cols);

		for (unsigned int i = 0; i < _rows; i++)
			for (unsigned int j = 0; j < _cols; j++)
			{
				res->_set(i, j, {}); //res->_matrix[i][j] = 0;
				for (unsigned int k = 0; k < _rows; k++)
					//res->_matrix[i][j] += _matrix[i][k] * matrix->_matrix[k][j];
					res->_set(i, j, res->Get(i, j) + Get(i, k) * matrix->Get(k, j));
			}

		return res;
#endif
	}

	//Thread of Matrix Kronecker product
	inline static void KroneckerProductThread(Matrix<T>& res, const int threadNumber, Matrix<T>& _this, Matrix<T>& matrix)
	{
		for (unsigned int r = 0; r < _this._rows; r++)
			for (unsigned int c = 0; c < _this._cols; c++)
				if ((r * res._cols + c) % THREADS_NUMBER == threadNumber)
					res._insertMatrix(r * matrix._rows, c * matrix._cols, matrix.operator*(_this.Get(r, c)));
	}

	//Matrix Kronecker product
	inline Matrix<T>* KroneckerProduct(Matrix<T>* matrix)
	{
#if USE_THREADS
		Matrix<T>* res = new Matrix<T>(_rows * matrix->_rows, _cols * matrix->_cols);

		std::thread threads[THREADS_NUMBER];
		for (unsigned int i = 0; i < THREADS_NUMBER; ++i)
			threads[i] = std::thread(KroneckerProductThread, std::ref(*res), i, std::ref(*this), std::ref(*matrix));

		for (unsigned int i = 0; i < THREADS_NUMBER; ++i)
			threads[i].join();

		return res;
#else
		Matrix<T>* res = new Matrix<T>(_rows * matrix->_rows, _cols * matrix->_cols);

		for (unsigned int r = 0; r < _rows; r++)
			for (unsigned int c = 0; c < _cols; c++)
				res->_insertMatrix(r * matrix->_rows, c * matrix->_cols, matrix->operator*(Get(r, c))); // _matrix[r][c]));

		return res;
#endif
	}

	inline void Print(std::string str = "")
	{
		std::cout << str << std::endl;
		for (unsigned int r = 0; r < _rows; r++)
		{
			for (unsigned int c = 0; c < _cols; c++)
				std::cout << Get(r, c) << "\t\t";
			std::cout << std::endl;
		}
		std::cout << "----------" << std::endl;
	}

	inline T Det()
	{
		return Det(this);
	}

	inline T Trace()
	{
		T trace = {};
		for (unsigned int r = 0; r < _rows; r++)
			trace += Get(r, r);

		return trace;
	}

	inline T* M()
	{
		return _matrix;
	}

	inline T Max(unsigned int& rPos, unsigned int& cPos)
	{
		T max = Zero;
		for (unsigned int r = 0; r < _rows; r++)
			for (unsigned int c = 0; c < _cols; c++)
				if (Get(r, c) > max)
				{
					rPos = r;
					cPos = c;
					max = Get(r, c);
				}

		return max;
	}

	inline T Get(unsigned int r, unsigned int c)
	{
		return _matrix[r * _rows + c];
	}

	inline T Det(Matrix<T>* matrix)
	{
		T det = {};
		unsigned int n = matrix->_rows;

		if (n == 2)
			return matrix->Get(0, 0) * matrix->Get(1, 1) - matrix->Get(1, 0) * matrix->Get(0, 1);
		else
		{
			Matrix<T>* submatrix = new Matrix<T>(matrix->_rows - 1, matrix->_cols - 1);
			for (unsigned int x = 0; x < n; x++)
			{
				if (matrix->Get(0, x) != Zero)
				{
					unsigned int subi = 0;
					for (unsigned int i = 1; i < n; i++)
					{
						unsigned int subj = 0;
						for (unsigned int j = 0; j < n; j++)
						{
							if (j == x)
								continue;
							submatrix->_set(subi, subj, matrix->Get(i, j));
							subj++;
						}
						subi++;
					}

					if (pow(-1, x) == -1)
						det -= (matrix->Get(0, x) * Det(submatrix));
					else
						det += (matrix->Get(0, x) * Det(submatrix));
				}
			}

			submatrix->~Matrix();
		}

		return det;
	}

private:
	T* _matrix;
	unsigned int _rows;
	unsigned int _cols;

	inline void _insertMatrix(unsigned int rPos, unsigned int cPos, Matrix<T>* matrix)
	{
		unsigned int maxR = matrix->_rows;
		unsigned int maxC = matrix->_cols;
		for (unsigned int r = 0; r < maxR; r++)
			for (unsigned int c = 0; c < maxC; c++)
				_set(rPos + r, cPos + c, matrix->Get(r, c));
	}

	inline void _set(unsigned int r, unsigned int c, T el)
	{
		_matrix[r * _rows + c] = el;
	}
};

template<typename T>
Matrix<T>* CalculateCXMatrix(unsigned int size, unsigned int check, unsigned int target)
{
	unsigned int qreg = (unsigned int)pow(2, size);
	T* args = new T[(size_t)pow(qreg, 2)];

	for (unsigned int i = 0; i < qreg; i++)
	{
		std::string s = std::bitset< MAX_BIT_SIZE >(i).to_string().substr(MAX_BIT_SIZE - size, size);
		if (s[check] == '1')
		{
			if (s[target] == '0')
				s[target] = '1';
			else if (s[target] == '1')
				s[target] = '0';
		}

		unsigned int l = (unsigned int)s.length();
		unsigned long long value = 0;
		unsigned long long exp = 1;
		for (unsigned int a = l; a != 0; a--)
		{
			if (s[a - 1] == '1')
				value += exp;
			exp *= 2;
		}
		args[value + i * qreg] = 1;
	}

	Matrix<T>* result = new Matrix<T>(qreg, qreg, args);
	return result;
}