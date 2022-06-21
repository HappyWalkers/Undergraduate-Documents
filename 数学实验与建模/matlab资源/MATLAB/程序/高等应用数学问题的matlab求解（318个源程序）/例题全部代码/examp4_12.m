syms x a1 a2 a3 a4 a5; A=vander([a1 a2 a3 a4 a5]);
collect(poly(A),x)
