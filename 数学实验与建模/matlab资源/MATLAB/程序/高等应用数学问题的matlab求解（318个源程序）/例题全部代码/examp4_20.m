A=[16 2 3 13; 5 11 10 8; 9 7 6 12; 4 14 15 1]; eig(A)

eig(sym(A))

vpa(ans,70)

[v, d] = eig(A)

[v,d]=eig(sym(A))

