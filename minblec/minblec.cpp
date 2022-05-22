// minblec.cpp
// Solve constrained optimization using provided numerical differentiation
// Optimier: BLEIC
//

#include "optimization.h"
#include "test_func.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>

using namespace alglib;

void minblec(const int N, const double bndl, const double bndh, testFunc func, real_1d_array & X);

int main()
{
    // write to csv
    std::ofstream fout("minblec.csv");
    // float format
    fout << std::scientific;
    fout.precision(std::numeric_limits<double>::digits10);
    // column names
    fout << "func,d,min\n";

    const int d[]{ 10,20 };
    for (auto &funcStruct : funcCalls)
    {
        for (auto &n : d)
        {
            std::cout << funcStruct.name << '\n';
            real_1d_array X;
            minblec(n, funcStruct.lower, funcStruct.upper, funcStruct.func, X);
            double ret;
            funcStruct.func(X, ret, NULL);
            std::cout << "min: " << std::fixed << ret << '\n';
            std::cout << std::endl;
            fout << funcStruct.name << ',' << n << ',' << ret << '\n';
        }
    }
    // flush & close
    fout << std::endl;
    fout.close();
}

void minblec(const int N, const double bndl, const double bndh, testFunc func, real_1d_array & X)
{
    std::cout << "Problem dimension: " << N << '\n';

    // Problem boundaries
    std::cout << "Boundaries: [" << bndl << ',' << bndh << "]\n";
    // boundary array will be the same size as problem dimension
    real_1d_array _bndl;
    _bndl.setlength(N);
    std::fill_n(_bndl.getcontent(), N, bndl);
    real_1d_array _bndh;
    _bndh.setlength(N);
    std::fill_n(_bndh.getcontent(), N, bndh);

    // Instantiate solution array
    X.setlength(N);
    // Initialize values
    std::fill_n(X.getcontent(), N, 1.5);
    std::cout << "Starting values: " << X.tostring(4) << '\n';

    // Dimension
    real_1d_array s;
    s.setlength(N);
    std::fill_n(s.getcontent(), N, 1.0);

    // Init optimizer
    minbcstate state;    // Optimizer structure
    minbccreatef(X, 1.0e-6, state); // Create optimizer
    minbcsetbc(state, _bndl, _bndh);  // Set boundary constraints
    minbcsetcond(state, 0, 0, 0.000001, 0); // Set stopping conditions

    // stuff??
    minbcoptguardsmoothness(state);

    // Optimize
    minbcreport rep;
    minbcoptimize(state, func);
    minbcresults(state, X, rep);

    std::cout << "Solution: " << X.tostring(4) << '\n';

    optguardreport ogrep;
    minbcoptguardresults(state, ogrep);
    std::cout << "Encountered discontinuity: " << (ogrep.nonc0suspected ? "true" : "false") << '\n';
    std::cout << "Encountered gradient discontinuity: " << (ogrep.nonc1suspected ? "true" : "false") << '\n';
}

