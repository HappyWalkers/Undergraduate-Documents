/*
 * MATLAB Compiler: 3.0
 * Date: Fri Sep 03 08:56:51 2004
 * Arguments: "-B" "macro_default" "-O" "all" "-O" "fold_scalar_mxarrays:on"
 * "-O" "fold_non_scalar_mxarrays:on" "-O" "optimize_integer_for_loops:on" "-O"
 * "array_indexing:on" "-O" "optimize_conditionals:on" "-x" "-W" "mex" "-L" "C"
 * "-t" "-T" "link:mexlibrary" "libmatlbmx.mlib" "sjbh1" 
 */

#ifndef MLF_V2
#define MLF_V2 1
#endif

#ifndef __sjbh1_h
#define __sjbh1_h 1

#ifdef __cplusplus
extern "C" {
#endif

#include "libmatlb.h"

extern void InitializeModule_sjbh1(void);
extern void TerminateModule_sjbh1(void);
extern _mexLocalFunctionTable _local_function_table_sjbh1;

extern void mlfSjbh1(mxArray * m);
extern void mlxSjbh1(int nlhs, mxArray * plhs[], int nrhs, mxArray * prhs[]);

#ifdef __cplusplus
}
#endif

#endif
