syms x; f=x*(x-pi)*(x-2*pi);
[A,B,F]=fseries(f,x,12,0,2*pi); latex(F)