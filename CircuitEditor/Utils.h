#pragma once

#include<stdarg.h>
#include "Define.h"

template<typename T>
class Utils
{
public:
    static T Max(T n_args, ...)
    {
        va_list ap;
        va_start(ap, n_args);
        T max = va_arg(ap, T);
        for (unsigned int i = 2; i <= n_args; i++)
        {
            unsigned int a = va_arg(ap, T);
            if (a > max && a != -1)
                max = a;
        }
        va_end(ap);
        return max;
    }

    static T RangeEquality(T arg1, T arg2)
    {
        return abs(arg1 - arg2) < Sigma;
    }
};