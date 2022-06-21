A=[-7,2,0,-1; 1,-4,2,1; 2,-1,-6,-1; -1,-1,0,-4];
syms t; j=sym(sqrt(-1));
A1=simple((expm(A*j*t)-expm(-A*j*t))/(2*j)),

A2=simple((expm(A*j*t)+expm(-A*j*t))/2)