A=[5,9,8,3; 0,3,2,4; 2,3,5,9; 3,4,5,8];
Q=orth(A)

norm(Q'*Q-eye(4))

norm(Q*Q'-eye(4))