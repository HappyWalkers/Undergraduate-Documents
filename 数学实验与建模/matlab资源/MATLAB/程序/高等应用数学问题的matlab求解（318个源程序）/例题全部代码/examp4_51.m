A=[-7,2,0,-1; 1,-4,2,1; 2,-1,-6,-1; -1,-1,0,-4];

syms x t; A1=funm(sym(A),exp(x*cos(x*t)),x)

collect(A1(1,1),exp(-6*cos(6*t)))

subs(A1,t,1)