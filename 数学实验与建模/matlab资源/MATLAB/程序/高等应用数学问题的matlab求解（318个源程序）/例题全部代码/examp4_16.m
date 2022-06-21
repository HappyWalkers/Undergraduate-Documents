A=[16 2 3 13; 5 11 10 8; 9 7 6 12; 4 14 15 1];
format long; B = inv(A)

norm(A*B-eye(size(A)))

A=sym(A);  inv(A)