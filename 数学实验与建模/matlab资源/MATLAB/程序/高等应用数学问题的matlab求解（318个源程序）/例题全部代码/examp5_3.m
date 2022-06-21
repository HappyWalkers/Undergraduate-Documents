syms x t;
G=(-17*x^5-7*x^4+2*x^3+x^2-x+1)/(x^6+11*x^5+48*x^4+106*x^3+125*x^2+75*x+17);
f=ilaplace(G,x,t)

vpa(f,16)