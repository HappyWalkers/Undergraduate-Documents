/*
 * MATLAB Compiler: 3.0
 * Date: Fri Sep 03 08:56:52 2004
 * Arguments: "-B" "macro_default" "-O" "all" "-O" "fold_scalar_mxarrays:on"
 * "-O" "fold_non_scalar_mxarrays:on" "-O" "optimize_integer_for_loops:on" "-O"
 * "array_indexing:on" "-O" "optimize_conditionals:on" "-x" "-W" "mex" "-L" "C"
 * "-t" "-T" "link:mexlibrary" "libmatlbmx.mlib" "sjbh1" 
 */

#ifndef MLF_V2
#define MLF_V2 1
#endif

#ifndef __legend_h
#define __legend_h 1

#ifdef __cplusplus
extern "C" {
#endif

#include "libmatlb.h"

extern void InitializeModule_legend(void);
extern void TerminateModule_legend(void);
extern _mexLocalFunctionTable _local_function_table_legend;

extern mxArray * mlfNLegend(int nargout,
                            mxArray * * labelhandles,
                            mxArray * * outH,
                            mxArray * * outM,
                            ...);
extern mxArray * mlfLegend(mxArray * * labelhandles,
                           mxArray * * outH,
                           mxArray * * outM,
                           ...);
extern void mlfVLegend(mxArray * synthetic_varargin_argument, ...);
extern void mlxLegend(int nlhs, mxArray * plhs[], int nrhs, mxArray * prhs[]);

#ifdef __cplusplus
}
#endif

#endif
