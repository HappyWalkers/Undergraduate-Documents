//
// MATLAB Compiler: 3.0
// Date: Thu Sep 02 20:52:11 2004
// Arguments: "-B" "macro_default" "-O" "all" "-O" "fold_scalar_mxarrays:on"
// "-O" "fold_non_scalar_mxarrays:on" "-O" "optimize_integer_for_loops:on" "-O"
// "array_indexing:on" "-O" "optimize_conditionals:on" "-p" "-W" "main" "-L"
// "Cpp" "-t" "-T" "link:exe" "-h" "libmmfile.mlib" "test_exe.m" 
//
#include "test_exe.hpp"
#include "libmatlbm.hpp"
static mwArray _mxarray0_ = mclInitializeDouble(18800.0);
static mwArray _mxarray1_ = mclInitializeDouble(100.0);

static mxChar _array3_[4] = { 'o', 'u', 't', '=' };
static mwArray _mxarray2_ = mclInitializeString(4, _array3_);

void InitializeModule_test_exe() {
}

void TerminateModule_test_exe() {
}

static mwArray Mtest_exe(int nargout_);

_mexLocalFunctionTable _local_function_table_test_exe
  = { 0, (mexFunctionTableEntry *)NULL };

//
// The function "test_exe" contains the normal interface for the "test_exe"
// M-function from file "d:\matlab6p5p1\work\test\test_exe.m" (lines 1-4). This
// function processes any input arguments and passes them to the implementation
// version of the function, appearing above.
//
mwArray test_exe() {
    int nargout = 1;
    mwArray out = mwArray::UNDEFINED;
    out = Mtest_exe(nargout);
    return out;
}

//
// The function "mlxTest_exe" contains the feval interface for the "test_exe"
// M-function from file "d:\matlab6p5p1\work\test\test_exe.m" (lines 1-4). The
// feval function calls the implementation version of test_exe through this
// function. This function processes any input arguments and passes them to the
// implementation version of the function, appearing above.
//
void mlxTest_exe(int nlhs, mxArray * plhs[], int nrhs, mxArray * prhs[]) {
    MW_BEGIN_MLX();
    {
        mwArray mplhs[1];
        mclCppUndefineArrays(1, mplhs);
        if (nlhs > 1) {
            error(
              mwVarargin(
                mwArray(
                  "Run-time Error: File: test_exe Line: 1 Column: "
                  "1 The function \"test_exe\" was called with mor"
                  "e than the declared number of outputs (1).")));
        }
        if (nrhs > 0) {
            error(
              mwVarargin(
                mwArray(
                  "Run-time Error: File: test_exe Line: 1 Column: "
                  "1 The function \"test_exe\" was called with mor"
                  "e than the declared number of inputs (0).")));
        }
        mplhs[0] = Mtest_exe(nlhs);
        plhs[0] = mplhs[0].FreezeData();
    }
    MW_END_MLX();
}

//
// The function "Mtest_exe" is the implementation version of the "test_exe"
// M-function from file "d:\matlab6p5p1\work\test\test_exe.m" (lines 1-4). It
// contains the actual compiled code for that M-function. It is a static
// function and must only be called from one of the interface functions,
// appearing below.
//
//
// function [out]=test_exe()
//
static mwArray Mtest_exe(int nargout_) {
    mwLocalFunctionTable save_local_function_table_
      = &_local_function_table_test_exe;
    mwArray out = mwArray::UNDEFINED;
    mwArray ans = mwArray::UNDEFINED;
    //
    // out=100*188*sqrt(100);
    //
    out = _mxarray0_ * sqrt(_mxarray1_);
    //
    // disp('out=');
    //
    disp(_mxarray2_);
    //
    // disp(out);
    //
    disp(mwVv(out, "out"));
    mwValidateOutput(out, 1, nargout_, "out", "test_exe");
    return out;
}
