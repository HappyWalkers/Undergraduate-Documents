A=[8,1,6; 3,5,7; 4,9,2]; Q=[16,4,1; 9,3,1; 4,2,1];
X=dlyap(A,Q)

norm(A*X*A'-X+Q)   % ??????֤