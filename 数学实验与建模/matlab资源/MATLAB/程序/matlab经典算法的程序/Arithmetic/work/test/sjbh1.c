/*
 * MATLAB Compiler: 3.0
 * Date: Fri Sep 03 08:56:51 2004
 * Arguments: "-B" "macro_default" "-O" "all" "-O" "fold_scalar_mxarrays:on"
 * "-O" "fold_non_scalar_mxarrays:on" "-O" "optimize_integer_for_loops:on" "-O"
 * "array_indexing:on" "-O" "optimize_conditionals:on" "-x" "-W" "mex" "-L" "C"
 * "-t" "-T" "link:mexlibrary" "libmatlbmx.mlib" "sjbh1" 
 */
#include "sjbh1.h"
#include "axis.h"
#include "grid.h"
#include "legend.h"
#include "libmatlbm.h"
static mxArray * _mxarray0_;
static mxArray * _mxarray1_;
static mxArray * _mxarray2_;

static double _array4_[4] = { -1.0, 10.0, -2.0, 2.0 };
static mxArray * _mxarray3_;

static mxChar _array6_[6] = { 's', 'i', 'n', '(', 'x', ')' };
static mxArray * _mxarray5_;
static mxArray * _mxarray7_;

static mxChar _array9_[3] = { 'o', 'f', 'f' };
static mxArray * _mxarray8_;

static mxChar _array11_[22] = { 0xbdab, 'y', '=', 's', 'i', 'n', '(', 'x', ')',
                                0xb5c4, 0xbae1, 0xd7f8, 0xb1ea, 0xcad5, 0xcbf5,
                                0xd6c1, 0xd4ad, 0xc0b4, 0xb5c4, '1', '/', '2' };
static mxArray * _mxarray10_;

static mxChar _array13_[5] = { 'C', 'o', 'l', 'o', 'r' };
static mxArray * _mxarray12_;

static double _array15_[3] = { 1.0, 1.0, 0.0 };
static mxArray * _mxarray14_;

static mxChar _array17_[6] = { 'M', 'a', 'r', 'k', 'e', 'r' };
static mxArray * _mxarray16_;

static mxChar _array19_[1] = { '.' };
static mxArray * _mxarray18_;

static mxChar _array21_[10] = { 'M', 'a', 'r', 'k', 'e',
                                'r', 'S', 'i', 'z', 'e' };
static mxArray * _mxarray20_;
static mxArray * _mxarray22_;

static mxChar _array24_[9] = { 'E', 'r', 'a', 's', 'e', 'M', 'o', 'd', 'e' };
static mxArray * _mxarray23_;

static mxChar _array26_[3] = { 'x', 'o', 'r' };
static mxArray * _mxarray25_;

static double _array28_[21] = { 1.0, 1.05, 1.1, 1.15, 1.2, 1.25, 1.3,
                                1.35, 1.4, 1.45, 1.5, 1.55, 1.6, 1.65,
                                1.7, 1.75, 1.8, 1.85, 1.9, 1.95, 2.0 };
static mxArray * _mxarray27_;
static mxArray * _mxarray29_;
static mxArray * _mxarray30_;
static mxArray * _mxarray31_;

static mxChar _array33_[5] = { 'x', 'd', 'a', 't', 'a' };
static mxArray * _mxarray32_;

static mxChar _array35_[5] = { 'y', 'd', 'a', 't', 'a' };
static mxArray * _mxarray34_;
static mxArray * _mxarray36_;
static mxArray * _mxarray37_;

static mxChar _array39_[7] = { 's', 'i', 'n', '(', '2', 'x', ')' };
static mxArray * _mxarray38_;

static mxChar _array41_[18] = { 0xbdab, 'y', '=', 's', 'i', 'n', '(',
                                '2', 'x', ')', 0xcff2, 0xd7f3,
                                0xc6bd, 0xd2c6, 'p', 'i', '/', '6' };
static mxArray * _mxarray40_;

static double _array43_[3] = { 1.0, 0.0, 1.0 };
static mxArray * _mxarray42_;

static mxChar _array45_[3] = { 'X', 'o', 'r' };
static mxArray * _mxarray44_;
static mxArray * _mxarray46_;
static mxArray * _mxarray47_;
static mxArray * _mxarray48_;

static mxChar _array50_[12] = { 's', 'i', 'n', '(', '2', 'x',
                                '+', 'p', 'i', '/', '3', ')' };
static mxArray * _mxarray49_;
static mxArray * _mxarray51_;
static mxArray * _mxarray52_;

static mxChar _array54_[13] = { '2', 's', 'i', 'n', '(', '2', 'x',
                                '+', 'p', 'i', '/', '3', ')' };
static mxArray * _mxarray53_;

void InitializeModule_sjbh1(void) {
    _mxarray0_ = mclInitializeDouble(-1.0);
    _mxarray1_ = mclInitializeDouble(.01);
    _mxarray2_ = mclInitializeDouble(10.0);
    _mxarray3_ = mclInitializeDoubleVector(1, 4, _array4_);
    _mxarray5_ = mclInitializeString(6, _array6_);
    _mxarray7_ = mclInitializeDouble(2.0);
    _mxarray8_ = mclInitializeString(3, _array9_);
    _mxarray10_ = mclInitializeString(22, _array11_);
    _mxarray12_ = mclInitializeString(5, _array13_);
    _mxarray14_ = mclInitializeDoubleVector(1, 3, _array15_);
    _mxarray16_ = mclInitializeString(6, _array17_);
    _mxarray18_ = mclInitializeString(1, _array19_);
    _mxarray20_ = mclInitializeString(10, _array21_);
    _mxarray22_ = mclInitializeDouble(4.0);
    _mxarray23_ = mclInitializeString(9, _array24_);
    _mxarray25_ = mclInitializeString(3, _array26_);
    _mxarray27_ = mclInitializeDoubleVector(1, 21, _array28_);
    _mxarray29_ = mclInitializeDouble(1101.0);
    _mxarray30_ = mclInitializeDouble(21.0);
    _mxarray31_ = mclInitializeDoubleVector(0, 0, (double *)NULL);
    _mxarray32_ = mclInitializeString(5, _array33_);
    _mxarray34_ = mclInitializeString(5, _array35_);
    _mxarray36_ = mclInitializeDouble(.0005);
    _mxarray37_ = mclInitializeDouble(1.0);
    _mxarray38_ = mclInitializeString(7, _array39_);
    _mxarray40_ = mclInitializeString(18, _array41_);
    _mxarray42_ = mclInitializeDoubleVector(1, 3, _array43_);
    _mxarray44_ = mclInitializeString(3, _array45_);
    _mxarray46_ = mclInitializeDouble(20.0);
    _mxarray47_ = mclInitializeDouble(3.141592653589793);
    _mxarray48_ = mclInitializeDouble(60.0);
    _mxarray49_ = mclInitializeString(12, _array50_);
    _mxarray51_ = mclInitializeDouble(5.0);
    _mxarray52_ = mclInitializeDouble(1.0471975511965976);
    _mxarray53_ = mclInitializeString(13, _array54_);
}

void TerminateModule_sjbh1(void) {
    mxDestroyArray(_mxarray53_);
    mxDestroyArray(_mxarray52_);
    mxDestroyArray(_mxarray51_);
    mxDestroyArray(_mxarray49_);
    mxDestroyArray(_mxarray48_);
    mxDestroyArray(_mxarray47_);
    mxDestroyArray(_mxarray46_);
    mxDestroyArray(_mxarray44_);
    mxDestroyArray(_mxarray42_);
    mxDestroyArray(_mxarray40_);
    mxDestroyArray(_mxarray38_);
    mxDestroyArray(_mxarray37_);
    mxDestroyArray(_mxarray36_);
    mxDestroyArray(_mxarray34_);
    mxDestroyArray(_mxarray32_);
    mxDestroyArray(_mxarray31_);
    mxDestroyArray(_mxarray30_);
    mxDestroyArray(_mxarray29_);
    mxDestroyArray(_mxarray27_);
    mxDestroyArray(_mxarray25_);
    mxDestroyArray(_mxarray23_);
    mxDestroyArray(_mxarray22_);
    mxDestroyArray(_mxarray20_);
    mxDestroyArray(_mxarray18_);
    mxDestroyArray(_mxarray16_);
    mxDestroyArray(_mxarray14_);
    mxDestroyArray(_mxarray12_);
    mxDestroyArray(_mxarray10_);
    mxDestroyArray(_mxarray8_);
    mxDestroyArray(_mxarray7_);
    mxDestroyArray(_mxarray5_);
    mxDestroyArray(_mxarray3_);
    mxDestroyArray(_mxarray2_);
    mxDestroyArray(_mxarray1_);
    mxDestroyArray(_mxarray0_);
}

static void Msjbh1(mxArray * m);

_mexLocalFunctionTable _local_function_table_sjbh1
  = { 0, (mexFunctionTableEntry *)NULL };

/*
 * The function "mlfSjbh1" contains the normal interface for the "sjbh1"
 * M-function from file "d:\matlab6p5p1\work\test\sjbh1.m" (lines 1-67). This
 * function processes any input arguments and passes them to the implementation
 * version of the function, appearing above.
 */
void mlfSjbh1(mxArray * m) {
    mlfEnterNewContext(0, 1, m);
    Msjbh1(m);
    mlfRestorePreviousContext(0, 1, m);
}

/*
 * The function "mlxSjbh1" contains the feval interface for the "sjbh1"
 * M-function from file "d:\matlab6p5p1\work\test\sjbh1.m" (lines 1-67). The
 * feval function calls the implementation version of sjbh1 through this
 * function. This function processes any input arguments and passes them to the
 * implementation version of the function, appearing above.
 */
void mlxSjbh1(int nlhs, mxArray * plhs[], int nrhs, mxArray * prhs[]) {
    mxArray * mprhs[1];
    int i;
    if (nlhs > 0) {
        mlfError(
          mxCreateString(
            "Run-time Error: File: sjbh1 Line: 2 Column: 1 The function \"sjbh1"
            "\" was called with more than the declared number of outputs (0)."),
          NULL);
    }
    if (nrhs > 1) {
        mlfError(
          mxCreateString(
            "Run-time Error: File: sjbh1 Line: 2 Column: 1 The function \"sjbh1"
            "\" was called with more than the declared number of inputs (1)."),
          NULL);
    }
    for (i = 0; i < 1 && i < nrhs; ++i) {
        mprhs[i] = prhs[i];
    }
    for (; i < 1; ++i) {
        mprhs[i] = NULL;
    }
    mlfEnterNewContext(0, 1, mprhs[0]);
    Msjbh1(mprhs[0]);
    mlfRestorePreviousContext(0, 1, mprhs[0]);
}

/*
 * The function "Msjbh1" is the implementation version of the "sjbh1"
 * M-function from file "d:\matlab6p5p1\work\test\sjbh1.m" (lines 1-67). It
 * contains the actual compiled code for that M-function. It is a static
 * function and must only be called from one of the interface functions,
 * appearing below.
 */
/*
 * %sjbh.m
 * function sjbh1(m)
 */
static void Msjbh1(mxArray * m) {
    mexLocalFunctionTable save_local_function_table_
      = mclSetCurrentLocalFunctionTable(&_local_function_table_sjbh1);
    mxArray * y4 = NULL;
    mxArray * w3 = NULL;
    mxArray * y3 = NULL;
    mxArray * w1 = NULL;
    mxArray * i = NULL;
    mxArray * y2 = NULL;
    mxArray * w = NULL;
    mxArray * h = NULL;
    mxArray * ans = NULL;
    mxArray * y1 = NULL;
    mxArray * x = NULL;
    mclCopyArray(&m);
    /*
     * x=-1:0.01:10;
     */
    mlfAssign(&x, mlfColon(_mxarray0_, _mxarray1_, _mxarray2_));
    /*
     * y1=sin(x);
     */
    mlfAssign(&y1, mlfSin(mclVv(x, "x")));
    /*
     * plot(x,y1)
     */
    mclPrintAns(&ans, mlfNPlot(0, mclVv(x, "x"), mclVv(y1, "y1"), NULL));
    /*
     * axis([-1 10 -2 2])
     */
    mclPrintAns(&ans, mlfNAxis(0, NULL, NULL, _mxarray3_, NULL));
    /*
     * grid
     */
    mlfGrid(NULL, NULL);
    /*
     * legend('sin(x)')
     */
    mclPrintAns(&ans, mlfNLegend(0, NULL, NULL, NULL, _mxarray5_, NULL));
    /*
     * pause(2)
     */
    mlfPause(_mxarray7_);
    /*
     * legend off
     */
    mclPrintAns(&ans, mlfNLegend(0, NULL, NULL, NULL, _mxarray8_, NULL));
    /*
     * legend('将y=sin(x)的横坐标收缩至原来的1/2')
     */
    mclPrintAns(&ans, mlfNLegend(0, NULL, NULL, NULL, _mxarray10_, NULL));
    /*
     * %hold on
     * %theax=axis;
     * pause
     */
    mlfPause(NULL);
    /*
     * %y=sinx->y=sin(wx)
     * h=line('Color',[1 1 0],'Marker','.','MarkerSize',4,'EraseMode','xor');
     */
    mlfAssign(
      &h,
      mlfNLine(
        1,
        _mxarray12_,
        _mxarray14_,
        _mxarray16_,
        _mxarray18_,
        _mxarray20_,
        _mxarray22_,
        _mxarray23_,
        _mxarray25_,
        NULL));
    /*
     * w=1:0.05:2;
     */
    mlfAssign(&w, _mxarray27_);
    /*
     * y2=zeros(1101,21);
     */
    mlfAssign(&y2, mlfZeros(_mxarray29_, _mxarray30_, NULL));
    /*
     * for i=1:21
     */
    {
        int v_ = mclForIntStart(1);
        int e_ = 21;
        if (v_ > e_) {
            mlfAssign(&i, _mxarray31_);
        } else {
            /*
             * y2(:,i)=sin(w(i)*x');
             * set(h,'xdata',x,'ydata',y2(:,i));
             * drawnow;
             * pause(0.0005)
             * i=i+1;
             * %axis=theax;
             * end
             */
            for (; ; ) {
                mlfAssign(&i, mlfScalar(v_));
                mclArrayAssign2(
                  &y2,
                  mlfSin(
                    mlf_times_transpose(
                      mclArrayRef1(mclVv(w, "w"), mclVv(i, "i")),
                      mclVv(x, "x"),
                      _mxarray7_)),
                  mlfCreateColonIndex(),
                  mclVv(i, "i"));
                mclAssignAns(
                  &ans,
                  mlfNSet(
                    0,
                    mclVv(h, "h"),
                    _mxarray32_,
                    mclVv(x, "x"),
                    _mxarray34_,
                    mclArrayRef2(
                      mclVv(y2, "y2"), mlfCreateColonIndex(), mclVv(i, "i")),
                    NULL));
                mlfDrawnow(NULL);
                mlfPause(_mxarray36_);
                mlfAssign(&i, mclPlus(mclVv(i, "i"), _mxarray37_));
                if (v_ == e_) {
                    break;
                }
                ++v_;
            }
        }
    }
    /*
     * legend off
     */
    mclPrintAns(&ans, mlfNLegend(0, NULL, NULL, NULL, _mxarray8_, NULL));
    /*
     * legend('sin(2x)')
     */
    mclPrintAns(&ans, mlfNLegend(0, NULL, NULL, NULL, _mxarray38_, NULL));
    /*
     * pause(2)
     */
    mlfPause(_mxarray7_);
    /*
     * legend('将y=sin(2x)向左平移pi/6')
     */
    mclPrintAns(&ans, mlfNLegend(0, NULL, NULL, NULL, _mxarray40_, NULL));
    /*
     * %hold on
     * pause
     */
    mlfPause(NULL);
    /*
     * %y=sin(wx)->y=sin(wx+pi/3)
     * h=line('Color',[1 0 1],'Marker','.','MarkerSize',4,'EraseMode','Xor');
     */
    mlfAssign(
      &h,
      mlfNLine(
        1,
        _mxarray12_,
        _mxarray42_,
        _mxarray16_,
        _mxarray18_,
        _mxarray20_,
        _mxarray22_,
        _mxarray23_,
        _mxarray44_,
        NULL));
    /*
     * w1=2;
     */
    mlfAssign(&w1, _mxarray7_);
    /*
     * y3=zeros(1101,20);
     */
    mlfAssign(&y3, mlfZeros(_mxarray29_, _mxarray46_, NULL));
    /*
     * for i=1:20
     */
    {
        int v_ = mclForIntStart(1);
        int e_ = 20;
        if (v_ > e_) {
            mlfAssign(&i, _mxarray31_);
        } else {
            /*
             * y3(:,i)=sin(w1*x'+i*pi/60);
             * set(h,'xdata',x,'ydata',y3(:,i));
             * drawnow;
             * pause(0.0005)
             * i=i+1;
             * %axis=theax;
             * end
             */
            for (; ; ) {
                mlfAssign(&i, mlfScalar(v_));
                mclArrayAssign2(
                  &y3,
                  mlfSin(
                    mclPlus(
                      mlf_times_transpose(
                        mclVv(w1, "w1"), mclVv(x, "x"), _mxarray7_),
                      mclMrdivide(
                        mclMtimes(mclVv(i, "i"), _mxarray47_), _mxarray48_))),
                  mlfCreateColonIndex(),
                  mclVv(i, "i"));
                mclAssignAns(
                  &ans,
                  mlfNSet(
                    0,
                    mclVv(h, "h"),
                    _mxarray32_,
                    mclVv(x, "x"),
                    _mxarray34_,
                    mclArrayRef2(
                      mclVv(y3, "y3"), mlfCreateColonIndex(), mclVv(i, "i")),
                    NULL));
                mlfDrawnow(NULL);
                mlfPause(_mxarray36_);
                mlfAssign(&i, mclPlus(mclVv(i, "i"), _mxarray37_));
                if (v_ == e_) {
                    break;
                }
                ++v_;
            }
        }
    }
    /*
     * legend off
     */
    mclPrintAns(&ans, mlfNLegend(0, NULL, NULL, NULL, _mxarray8_, NULL));
    /*
     * legend('sin(2x+pi/3)')
     */
    mclPrintAns(&ans, mlfNLegend(0, NULL, NULL, NULL, _mxarray49_, NULL));
    /*
     * pause(2)
     */
    mlfPause(_mxarray7_);
    /*
     * legend('将y=sin(2x)向左平移pi/6')
     */
    mclPrintAns(&ans, mlfNLegend(0, NULL, NULL, NULL, _mxarray40_, NULL));
    /*
     * %y=sin(wx+pi/3)->y=2sin(wx+pi/3)
     * pause
     */
    mlfPause(NULL);
    /*
     * %y=sin(wx)->y=sin(wx+pi/3)
     * h=line('Color',[1 0 1],'Marker','.','MarkerSize',5,'EraseMode','Xor');
     */
    mlfAssign(
      &h,
      mlfNLine(
        1,
        _mxarray12_,
        _mxarray42_,
        _mxarray16_,
        _mxarray18_,
        _mxarray20_,
        _mxarray51_,
        _mxarray23_,
        _mxarray44_,
        NULL));
    /*
     * w3=1:0.05:2;
     */
    mlfAssign(&w3, _mxarray27_);
    /*
     * y4=zeros(1101,21);
     */
    mlfAssign(&y4, mlfZeros(_mxarray29_, _mxarray30_, NULL));
    /*
     * for i=1:21
     */
    {
        int v_ = mclForIntStart(1);
        int e_ = 21;
        if (v_ > e_) {
            mlfAssign(&i, _mxarray31_);
        } else {
            /*
             * y4(:,i)=w3(i)*sin(w1*x'+pi/3);
             * set(h,'xdata',x,'ydata',y4(:,i));
             * drawnow;
             * %pause(0.0005)
             * i=i+1;
             * %axis=theax;
             * end
             */
            for (; ; ) {
                mlfAssign(&i, mlfScalar(v_));
                mclArrayAssign2(
                  &y4,
                  mclMtimes(
                    mclArrayRef1(mclVv(w3, "w3"), mclVv(i, "i")),
                    mlfSin(
                      mclPlus(
                        mlf_times_transpose(
                          mclVv(w1, "w1"), mclVv(x, "x"), _mxarray7_),
                        _mxarray52_))),
                  mlfCreateColonIndex(),
                  mclVv(i, "i"));
                mclAssignAns(
                  &ans,
                  mlfNSet(
                    0,
                    mclVv(h, "h"),
                    _mxarray32_,
                    mclVv(x, "x"),
                    _mxarray34_,
                    mclArrayRef2(
                      mclVv(y4, "y4"), mlfCreateColonIndex(), mclVv(i, "i")),
                    NULL));
                mlfDrawnow(NULL);
                mlfAssign(&i, mclPlus(mclVv(i, "i"), _mxarray37_));
                if (v_ == e_) {
                    break;
                }
                ++v_;
            }
        }
    }
    /*
     * legend off
     */
    mclPrintAns(&ans, mlfNLegend(0, NULL, NULL, NULL, _mxarray8_, NULL));
    /*
     * legend('2sin(2x+pi/3)')
     */
    mclPrintAns(&ans, mlfNLegend(0, NULL, NULL, NULL, _mxarray53_, NULL));
    /*
     * legend off
     */
    mclPrintAns(&ans, mlfNLegend(0, NULL, NULL, NULL, _mxarray8_, NULL));
    mxDestroyArray(x);
    mxDestroyArray(y1);
    mxDestroyArray(ans);
    mxDestroyArray(h);
    mxDestroyArray(w);
    mxDestroyArray(y2);
    mxDestroyArray(i);
    mxDestroyArray(w1);
    mxDestroyArray(y3);
    mxDestroyArray(w3);
    mxDestroyArray(y4);
    mxDestroyArray(m);
    mclSetCurrentLocalFunctionTable(save_local_function_table_);
    /*
     * %pause(2)
     * %legend('将y=sin(2x)向左平移pi/6')
     */
}
