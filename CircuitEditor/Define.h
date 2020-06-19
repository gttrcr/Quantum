#pragma once

//User define
#define _Type double
#define MAX_BIT_SIZE 256
#define THREADS_NUMBER 32
#define USE_THREADS false
#define CIRCUIT_LOGS false
#define MonitoringThreadDelay 1000

//Program define
#define _Complex Complex<_Type>
#define _Matrix Matrix<_Complex>

#define IMatrix _Matrix(2, 2, {_Complex(1, 0), _Complex(0, 0), _Complex(0, 0), _Complex(1, 0)})
#define XMatrix _Matrix(2, 2, {_Complex(0, 0), _Complex(1, 0), _Complex(1, 0), _Complex(0, 0)})
#define YMatrix _Matrix(2, 2, {_Complex(0, 0), _Complex(0, -1), _Complex(0, 1), _Complex(0, 0)})
#define ZMatrix _Matrix(2, 2, {_Complex(1, 0), _Complex(0, 0), _Complex(0, 0), _Complex(-1, 0)})
#define HMatrix _Matrix(2, 2, {_Complex(_Type(1/sqrt(2)), 0), _Complex(_Type(1/sqrt(2)), 0), _Complex(_Type(1/sqrt(2)), 0), _Complex(_Type(-1/sqrt(2)), 0)})

#define Sigma (_Type)pow(10, -14)
#define Zero _Complex(0, 0)
#define One _Complex(1, 0)