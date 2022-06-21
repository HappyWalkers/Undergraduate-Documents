syms n x
s1=symsum(2/((2*n+1)*(2*x+1)^(2*n+1)),n,0,inf);
simple(s1)  % 对结果进行化简，MATLAB 6.5 及以前版本因本身 bug 化简很麻烦