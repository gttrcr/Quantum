#pragma once

#define _Type double
#define _Complex Complex<_Type>
#define _Matrix Matrix<_Complex>

#define MAX_BIT_SIZE 256
#define THREADS_NUMBER 256
#define USE_THREADS 1

#define IMatrix _Matrix(2, 2, {1, 0, 0, 1})
#define XMatrix _Matrix(2, 2, {0, 1, 1, 0})
#define YMatrix _Matrix(2, 2, {0, 0, 0, 0})
#define ZMatrix _Matrix(2, 2, {1, 0, 0, -1})
#define HMatrix _Matrix(2, 2, {_Type(1/sqrt(2)), _Type(1/sqrt(2)), _Type(1/sqrt(2)), _Type(-1/sqrt(2))})