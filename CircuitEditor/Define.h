#pragma once

//User define
#define _Type double
#define MAX_BIT_SIZE 256
#define THREADS_NUMBER 32
#define USE_THREADS true
#define CIRCUIT_LOGS true
#define CheckThreadDelay 1000

//Program define
#define _Complex Complex<_Type>
#define _Matrix Matrix<_Complex>

#define IMatrix _Matrix(2, 2, {1, 0, 0, 1})
#define XMatrix _Matrix(2, 2, {0, 1, 1, 0})
#define YMatrix _Matrix(2, 2, {0, 0, 0, 0})
#define ZMatrix _Matrix(2, 2, {1, 0, 0, -1})
#define HMatrix _Matrix(2, 2, {_Type(1/sqrt(2)), _Type(1/sqrt(2)), _Type(1/sqrt(2)), _Type(-1/sqrt(2))})

#define Sigma (_Type)0.0000000000001
#define Zero _Complex(0, 0)
#define One _Complex(1, 0)