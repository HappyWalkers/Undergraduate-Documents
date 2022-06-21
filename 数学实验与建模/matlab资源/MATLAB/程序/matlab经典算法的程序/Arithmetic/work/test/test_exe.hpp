//
// MATLAB Compiler: 3.0
// Date: Thu Sep 02 20:52:11 2004
// Arguments: "-B" "macro_default" "-O" "all" "-O" "fold_scalar_mxarrays:on"
// "-O" "fold_non_scalar_mxarrays:on" "-O" "optimize_integer_for_loops:on" "-O"
// "array_indexing:on" "-O" "optimize_conditionals:on" "-p" "-W" "main" "-L"
// "Cpp" "-t" "-T" "link:exe" "-h" "libmmfile.mlib" "test_exe.m" 
//
#ifndef __test_exe_hpp
#define __test_exe_hpp 1

#include "libmatlb.hpp"

extern void InitializeModule_test_exe();
extern void TerminateModule_test_exe();
extern _mexLocalFunctionTable _local_function_table_test_exe;

extern mwArray test_exe();
#ifdef __cplusplus
extern "C"
#endif
void mlxTest_exe(int nlhs, mxArray * plhs[], int nrhs, mxArray * prhs[]);

#endif
