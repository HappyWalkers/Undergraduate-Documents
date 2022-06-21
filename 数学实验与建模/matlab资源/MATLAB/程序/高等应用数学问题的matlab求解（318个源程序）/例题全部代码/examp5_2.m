syms x w; f=x^2*exp(-2*x)*sin(x+pi);
F=laplace(f,x,w)

ilaplace(F)