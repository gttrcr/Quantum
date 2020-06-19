#pragma once

#include<stdarg.h>
#ifdef _WIN32
#include<Windows.h>
#include<Psapi.h>
#else
#include<unistd.h>
#include<term.h>
#endif

#include "Define.h"

namespace Utils
{
    template<typename T>
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

    template<typename T>
    static T RangeEquality(T arg1, T arg2)
    {
        return abs(arg1 - arg2) < Sigma;
    }

    static void GotoXY(unsigned int x, unsigned int y)
    {
#ifdef  _WIN32
        COORD p = { x, y };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
#else
        int err;
        if (!cur_term)
            if (setupterm(NULL, STDOUT_FILENO, &err) == ERR)
                return;
        putp(tparm(tigetstr("cup"), y, x, 0, 0, 0, 0, 0, 0, 0));
#endif
    }

    static void SetConsoleBuffer()
    {
#ifdef _WIN32
        COORD p = { 10000, 1000 };
        SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), p);
#else

#endif
    }

    static unsigned int VirtualMemoryUsedByProcess()
    {
#ifdef _WIN32
        PROCESS_MEMORY_COUNTERS_EX pmc;
        GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
        SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;
        return (unsigned int)virtualMemUsedByMe;
#else
        FILE* file = fopen("/proc/self/status", "r");
        int result = -1;
        char line[128];

        while (fgets(line, 128, file) != NULL)
        {
            if (strncmp(line, "VmSize:", 7) == 0)
            {
                int i = strlen(line);
                const char* p = line;
                while (*p < '0' || *p > '9') p++;
                line[i - 3] = '\0';
                i = atoi(p);
                result = i;
                break;
            }
        }
        fclose(file);
        return 1000 * result;
#endif
    }

    static void ConsoleTitle(std::string str)
    {
#ifdef _WIN32
        std::wstring stemp = std::wstring(str.begin(), str.end());
        LPCWSTR sw = stemp.c_str();
        SetConsoleTitle(sw);
#else
        std::cout << "\033]0;" << str << "\007";
#endif
    }
};