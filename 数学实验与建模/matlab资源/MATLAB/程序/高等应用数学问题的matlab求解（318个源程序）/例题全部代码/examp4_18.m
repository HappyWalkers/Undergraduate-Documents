A=[16 2 3 13; 5 11 10 8; 9 7 6 12; 4 14 15 1];
B=pinv(A)

A*B

norm(A*B*A-A)

norm(B*A*B-B)

[norm(A*B-(A*B)'), norm(B*A-(B*A)')]

pinv(B)