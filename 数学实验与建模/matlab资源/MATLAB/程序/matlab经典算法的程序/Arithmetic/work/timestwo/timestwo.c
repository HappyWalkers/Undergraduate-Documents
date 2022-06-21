#include "mex.h"
void timestwo(double y[],double x[])
{
	y[0]=2.0*x[0];
}
void mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[])
{
	double *x,*y;
	int mrows,ncols;
	mrows=mxGetM(prhs[0]);
	ncols=mxGetN(prhs[0]);
	plhs[0]=mxCreateDoubleMatrix(mrows,ncols,mxREAL);
	x=mxGetPr(prhs[0]);
	y=mxGetPr(plhs[0]);
	timestwo(y,x);
}