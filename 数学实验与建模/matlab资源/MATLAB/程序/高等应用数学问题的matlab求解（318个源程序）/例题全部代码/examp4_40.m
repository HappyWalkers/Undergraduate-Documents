A=[8,1,6; 3,5,7; 4,9,2]; B=[16,4,1; 9,3,1; 4,2,1];
C=-[1,2,3; 4,5,6; 7,8,0];  X=lyap(A,B,C)

norm(A*X+X*B+C)

x=lyap(sym(A),B,C)

norm(double(A*x+x*B+C))
