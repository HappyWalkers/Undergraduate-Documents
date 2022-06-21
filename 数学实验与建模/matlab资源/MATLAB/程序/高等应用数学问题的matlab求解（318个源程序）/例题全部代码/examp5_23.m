syms x; A=x^4+7*x^3+13*x^2+19*x+20;
B=x^7+16*x^6+103*x^5+346*x^4+655*x^3+700*x^2+393*x+90;
d=gcd(A,B)

simple(A/d)

simple(B/d)

