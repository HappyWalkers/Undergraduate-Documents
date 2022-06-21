A=[[-2 1 0; 0 -2 1; 0 0 -2], zeros(3,2); zeros(2,3) [-5 1; 0 -5]];
j=sqrt(-1);
A1=(expm(A*j)-expm(-A*j))/(2*j),
