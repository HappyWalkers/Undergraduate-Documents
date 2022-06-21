syms x; A=x^4+7*x^3+13*x^2+19*x+20;
B=x^7+16*x^6+103*x^5+346*x^4+655*x^3+700*x^2+393*x+90;
n=sym2poly(A); d=sym2poly(B);
[r,p,k]=residue(n,d); [n1,d1]=rat(r); [n1,d1,p]

r(1)

residue1(A/B,x)