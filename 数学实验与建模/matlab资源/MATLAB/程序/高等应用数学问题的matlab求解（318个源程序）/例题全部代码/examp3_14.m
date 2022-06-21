syms x t; f=(-2*x^2+1)/(2*x^2-3*x+1)^2;
I=simple(int(f,x,cos(t),exp(-2*t))), latex(I)
