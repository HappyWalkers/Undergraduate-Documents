syms x; I1=int(exp(-x^2/2),x,0,1.5)

vpa(I1,70)

I2=int(exp(-x^2/2),x,0,inf)