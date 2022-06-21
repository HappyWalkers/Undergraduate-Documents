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

#include "libmatlb.h"
#include "mwservices.h"
#include "sjbh1.h"
#include "axis.h"
#include "grid.h"
#include "legend.h"

extern _mex_information _mex_info;

static mexFunctionTableEntry function_table[1]
  = { { "sjbh1", mlxSjbh1, 1, 0, &_local_function_table_sjbh1 } };

static _mexInitTermTableEntry init_term_table[1]
  = { { InitializeModule_sjbh1, TerminateModule_sjbh1 } };

/*
 * The function "Mlegend" is the MATLAB callback version of the "legend"
 * function from file "d:\matlab6p5p1\toolbox\matlab\graph2d\legend.m". It
 * performs a callback to MATLAB to run the "legend" function, and passes any
 * resulting output arguments back to its calling function.
 */
static mxArray * Mlegend(mxArray * * labelhandles,
                         mxArray * * outH,
                         mxArray * * outM,
                         int nargout_,
                         mxArray * varargin) {
    mxArray * leghandle = NULL;
    mclFevalCallMATLAB(
      mclNVarargout(nargout_, 0, &leghandle, labelhandles, outH, outM, NULL),
      "legend",
      mlfIndexRef(varargin, "{?}", mlfCreateColonIndex()), NULL);
    return leghandle;
}

/*
 * The function "Mgrid" is the MATLAB callback version of the "grid" function
 * from file "d:\matlab6p5p1\toolbox\matlab\graph2d\grid.m". It performs a
 * callback to MATLAB to run the "grid" function, and passes any resulting
 * output arguments back to its calling function.
 */
static void Mgrid(mxArray * arg1, mxArray * arg2) {
    mclFevalCallMATLAB(mclAnsVarargout(), "grid", arg1, arg2, NULL);
}

/*
 * The function "Maxis" is the MATLAB callback version of the "axis" function
 * from file "d:\matlab6p5p1\toolbox\matlab\graph2d\axis.m". It performs a
 * callback to MATLAB to run the "axis" function, and passes any resulting
 * output arguments back to its calling function.
 */
static mxArray * Maxis(mxArray * * ans2,
                       mxArray * * ans3,
                       int nargout_,
                       mxArray * varargin) {
    mxArray * ans1 = NULL;
    mclFevalCallMATLAB(
      mclNVarargout(nargout_, 0, &ans1, ans2, ans3, NULL),
      "axis",
      mlfIndexRef(varargin, "{?}", mlfCreateColonIndex()), NULL);
    return ans1;
}

/*
 * The function "mexLibrary" is a Compiler-generated mex wrapper, suitable for
 * building a MEX-function. It initializes any persistent variables as well as
 * a function table for use by the feval function. It then calls the function
 * "mlxSjbh1". Finally, it clears the feval table and exits.
 */
mex_information mexLibrary(void) {
    mclMexLibraryInit();
    return &_mex_info;
}

_mex_information _mex_info
  = { 1, 1, function_table, 0, NULL, 0, NULL, 1, init_term_table };

/*
 * The function "mlfNLegend" contains the nargout interface for the "legend"
 * M-function from file "d:\matlab6p5p1\toolbox\matlab\graph2d\legend.m" (lines
 * 0-0). This interface is only produced if the M-function uses the special
 * variable "nargout". The nargout interface allows the number of requested
 * outputs to be specified via the nargout argument, as opposed to the normal
 * interface which dynamically calculates the number of outputs based on the
 * number of non-NULL inputs it receives. This function processes any input
 * arguments and passes them to the implementation version of the function,
 * appearing above.
 */
mxArray * mlfNLegend(int nargout,
                     mxArray * * labelhandles,
                     mxArray * * outH,
                     mxArray * * outM,
                     ...) {
    mxArray * varargin = NULL;
    mxArray * leghandle = NULL;
    mxArray * labelhandles__ = NULL;
    mxArray * outH__ = NULL;
    mxArray * outM__ = NULL;
    mlfVarargin(&varargin, outM, 0);
    mlfEnterNewContext(3, -1, labelhandles, outH, outM, varargin);
    leghandle = Mlegend(&labelhandles__, &outH__, &outM__, nargout, varargin);
    mlfRestorePreviousContext(3, 0, labelhandles, outH, outM);
    mxDestroyArray(varargin);
    if (labelhandles != NULL) {
        mclCopyOutputArg(labelhandles, labelhandles__);
    } else {
        mxDestroyArray(labelhandles__);
    }
    if (outH != NULL) {
        mclCopyOutputArg(outH, outH__);
    } else {
        mxDestroyArray(outH__);
    }
    if (outM != NULL) {
        mclCopyOutputArg(outM, outM__);
    } else {
        mxDestroyArray(outM__);
    }
    return mlfReturnValue(leghandle);
}

/*
 * The function "mlfLegend" contains the normal interface for the "legend"
 * M-function from file "d:\matlab6p5p1\toolbox\matlab\graph2d\legend.m" (lines
 * 0-0). This function processes any input arguments and passes them to the
 * implementation version of the function, appearing above.
 */
mxArray * mlfLegend(mxArray * * labelhandles,
                    mxArray * * outH,
                    mxArray * * outM,
                    ...) {
    mxArray * varargin = NULL;
    int nargout = 1;
    mxArray * leghandle = NULL;
    mxArray * labelhandles__ = NULL;
    mxArray * outH__ = NULL;
    mxArray * outM__ = NULL;
    mlfVarargin(&varargin, outM, 0);
    mlfEnterNewContext(3, -1, labelhandles, outH, outM, varargin);
    if (labelhandles != NULL) {
        ++nargout;
    }
    if (outH != NULL) {
        ++nargout;
    }
    if (outM != NULL) {
        ++nargout;
    }
    leghandle = Mlegend(&labelhandles__, &outH__, &outM__, nargout, varargin);
    mlfRestorePreviousContext(3, 0, labelhandles, outH, outM);
    mxDestroyArray(varargin);
    if (labelhandles != NULL) {
        mclCopyOutputArg(labelhandles, labelhandles__);
    } else {
        mxDestroyArray(labelhandles__);
    }
    if (outH != NULL) {
        mclCopyOutputArg(outH, outH__);
    } else {
        mxDestroyArray(outH__);
    }
    if (outM != NULL) {
        mclCopyOutputArg(outM, outM__);
    } else {
        mxDestroyArray(outM__);
    }
    return mlfReturnValue(leghandle);
}

/*
 * The function "mlfVLegend" contains the void interface for the "legend"
 * M-function from file "d:\matlab6p5p1\toolbox\matlab\graph2d\legend.m" (lines
 * 0-0). The void interface is only produced if the M-function uses the special
 * variable "nargout", and has at least one output. The void interface function
 * specifies zero output arguments to the implementation version of the
 * function, and in the event that the implementation version still returns an
 * output (which, in MATLAB, would be assigned to the "ans" variable), it
 * deallocates the output. This function processes any input arguments and
 * passes them to the implementation version of the function, appearing above.
 */
void mlfVLegend(mxArray * synthetic_varargin_argument, ...) {
    mxArray * varargin = NULL;
    mxArray * leghandle = NULL;
    mxArray * labelhandles = NULL;
    mxArray * outH = NULL;
    mxArray * outM = NULL;
    mlfVarargin(&varargin, synthetic_varargin_argument, 1);
    mlfEnterNewContext(0, -1, varargin);
    leghandle
      = Mlegend(&labelhandles, &outH, &outM, 0, synthetic_varargin_argument);
    mlfRestorePreviousContext(0, 0);
    mxDestroyArray(varargin);
    mxDestroyArray(leghandle);
    mxDestroyArray(labelhandles);
    mxDestroyArray(outH);
}

/*
 * The function "mlxLegend" contains the feval interface for the "legend"
 * M-function from file "d:\matlab6p5p1\toolbox\matlab\graph2d\legend.m" (lines
 * 0-0). The feval function calls the implementation version of legend through
 * this function. This function processes any input arguments and passes them
 * to the implementation version of the function, appearing above.
 */
void mlxLegend(int nlhs, mxArray * plhs[], int nrhs, mxArray * prhs[]) {
    mxArray * mprhs[1];
    mxArray * mplhs[4];
    int i;
    if (nlhs > 4) {
        mlfError(
          mxCreateString(
            "Run-time Error: File: legend Line: 1 Column: "
            "1 The function \"legend\" was called with mor"
            "e than the declared number of outputs (4)."),
          NULL);
    }
    for (i = 0; i < 4; ++i) {
        mplhs[i] = NULL;
    }
    mlfEnterNewContext(0, 0);
    mprhs[0] = NULL;
    mlfAssign(&mprhs[0], mclCreateVararginCell(nrhs, prhs));
    mplhs[0] = Mlegend(&mplhs[1], &mplhs[2], &mplhs[3], nlhs, mprhs[0]);
    mlfRestorePreviousContext(0, 0);
    plhs[0] = mplhs[0];
    for (i = 1; i < 4 && i < nlhs; ++i) {
        plhs[i] = mplhs[i];
    }
    for (; i < 4; ++i) {
        mxDestroyArray(mplhs[i]);
    }
    mxDestroyArray(mprhs[0]);
}

/*
 * The function "mlfGrid" contains the normal interface for the "grid"
 * M-function from file "d:\matlab6p5p1\toolbox\matlab\graph2d\grid.m" (lines
 * 0-0). This function processes any input arguments and passes them to the
 * implementation version of the function, appearing above.
 */
void mlfGrid(mxArray * arg1, mxArray * arg2) {
    mlfEnterNewContext(0, 2, arg1, arg2);
    Mgrid(arg1, arg2);
    mlfRestorePreviousContext(0, 2, arg1, arg2);
}

/*
 * The function "mlxGrid" contains the feval interface for the "grid"
 * M-function from file "d:\matlab6p5p1\toolbox\matlab\graph2d\grid.m" (lines
 * 0-0). The feval function calls the implementation version of grid through
 * this function. This function processes any input arguments and passes them
 * to the implementation version of the function, appearing above.
 */
void mlxGrid(int nlhs, mxArray * plhs[], int nrhs, mxArray * prhs[]) {
    mxArray * mprhs[2];
    int i;
    if (nlhs > 0) {
        mlfError(
          mxCreateString(
            "Run-time Error: File: grid Line: 1 Column: 1 The function \"grid\""
            " was called with more than the declared number of outputs (0)."),
          NULL);
    }
    if (nrhs > 2) {
        mlfError(
          mxCreateString(
            "Run-time Error: File: grid Line: 1 Column: 1 The function \"grid"
            "\" was called with more than the declared number of inputs (2)."),
          NULL);
    }
    for (i = 0; i < 2 && i < nrhs; ++i) {
        mprhs[i] = prhs[i];
    }
    for (; i < 2; ++i) {
        mprhs[i] = NULL;
    }
    mlfEnterNewContext(0, 2, mprhs[0], mprhs[1]);
    Mgrid(mprhs[0], mprhs[1]);
    mlfRestorePreviousContext(0, 2, mprhs[0], mprhs[1]);
}

/*
 * The function "mlfNAxis" contains the nargout interface for the "axis"
 * M-function from file "d:\matlab6p5p1\toolbox\matlab\graph2d\axis.m" (lines
 * 0-0). This interface is only produced if the M-function uses the special
 * variable "nargout". The nargout interface allows the number of requested
 * outputs to be specified via the nargout argument, as opposed to the normal
 * interface which dynamically calculates the number of outputs based on the
 * number of non-NULL inputs it receives. This function processes any input
 * arguments and passes them to the implementation version of the function,
 * appearing above.
 */
mxArray * mlfNAxis(int nargout, mxArray * * ans2, mxArray * * ans3, ...) {
    mxArray * varargin = NULL;
    mxArray * ans1 = NULL;
    mxArray * ans2__ = NULL;
    mxArray * ans3__ = NULL;
    mlfVarargin(&varargin, ans3, 0);
    mlfEnterNewContext(2, -1, ans2, ans3, varargin);
    ans1 = Maxis(&ans2__, &ans3__, nargout, varargin);
    mlfRestorePreviousContext(2, 0, ans2, ans3);
    mxDestroyArray(varargin);
    if (ans2 != NULL) {
        mclCopyOutputArg(ans2, ans2__);
    } else {
        mxDestroyArray(ans2__);
    }
    if (ans3 != NULL) {
        mclCopyOutputArg(ans3, ans3__);
    } else {
        mxDestroyArray(ans3__);
    }
    return mlfReturnValue(ans1);
}

/*
 * The function "mlfAxis" contains the normal interface for the "axis"
 * M-function from file "d:\matlab6p5p1\toolbox\matlab\graph2d\axis.m" (lines
 * 0-0). This function processes any input arguments and passes them to the
 * implementation version of the function, appearing above.
 */
mxArray * mlfAxis(mxArray * * ans2, mxArray * * ans3, ...) {
    mxArray * varargin = NULL;
    int nargout = 1;
    mxArray * ans1 = NULL;
    mxArray * ans2__ = NULL;
    mxArray * ans3__ = NULL;
    mlfVarargin(&varargin, ans3, 0);
    mlfEnterNewContext(2, -1, ans2, ans3, varargin);
    if (ans2 != NULL) {
        ++nargout;
    }
    if (ans3 != NULL) {
        ++nargout;
    }
    ans1 = Maxis(&ans2__, &ans3__, nargout, varargin);
    mlfRestorePreviousContext(2, 0, ans2, ans3);
    mxDestroyArray(varargin);
    if (ans2 != NULL) {
        mclCopyOutputArg(ans2, ans2__);
    } else {
        mxDestroyArray(ans2__);
    }
    if (ans3 != NULL) {
        mclCopyOutputArg(ans3, ans3__);
    } else {
        mxDestroyArray(ans3__);
    }
    return mlfReturnValue(ans1);
}

/*
 * The function "mlfVAxis" contains the void interface for the "axis"
 * M-function from file "d:\matlab6p5p1\toolbox\matlab\graph2d\axis.m" (lines
 * 0-0). The void interface is only produced if the M-function uses the special
 * variable "nargout", and has at least one output. The void interface function
 * specifies zero output arguments to the implementation version of the
 * function, and in the event that the implementation version still returns an
 * output (which, in MATLAB, would be assigned to the "ans" variable), it
 * deallocates the output. This function processes any input arguments and
 * passes them to the implementation version of the function, appearing above.
 */
void mlfVAxis(mxArray * synthetic_varargin_argument, ...) {
    mxArray * varargin = NULL;
    mxArray * ans1 = NULL;
    mxArray * ans2 = NULL;
    mxArray * ans3 = NULL;
    mlfVarargin(&varargin, synthetic_varargin_argument, 1);
    mlfEnterNewContext(0, -1, varargin);
    ans1 = Maxis(&ans2, &ans3, 0, synthetic_varargin_argument);
    mlfRestorePreviousContext(0, 0);
    mxDestroyArray(varargin);
    mxDestroyArray(ans1);
    mxDestroyArray(ans2);
}

/*
 * The function "mlxAxis" contains the feval interface for the "axis"
 * M-function from file "d:\matlab6p5p1\toolbox\matlab\graph2d\axis.m" (lines
 * 0-0). The feval function calls the implementation version of axis through
 * this function. This function processes any input arguments and passes them
 * to the implementation version of the function, appearing above.
 */
void mlxAxis(int nlhs, mxArray * plhs[], int nrhs, mxArray * prhs[]) {
    mxArray * mprhs[1];
    mxArray * mplhs[3];
    int i;
    if (nlhs > 3) {
        mlfError(
          mxCreateString(
            "Run-time Error: File: axis Line: 1 Column: 1 The function \"axis\""
            " was called with more than the declared number of outputs (3)."),
          NULL);
    }
    for (i = 0; i < 3; ++i) {
        mplhs[i] = NULL;
    }
    mlfEnterNewContext(0, 0);
    mprhs[0] = NULL;
    mlfAssign(&mprhs[0], mclCreateVararginCell(nrhs, prhs));
    mplhs[0] = Maxis(&mplhs[1], &mplhs[2], nlhs, mprhs[0]);
    mlfRestorePreviousContext(0, 0);
    plhs[0] = mplhs[0];
    for (i = 1; i < 3 && i < nlhs; ++i) {
        plhs[i] = mplhs[i];
    }
    for (; i < 3; ++i) {
        mxDestroyArray(mplhs[i]);
    }
    mxDestroyArray(mprhs[0]);
}
