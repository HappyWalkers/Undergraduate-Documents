A=[-2,1,-3; -1,0,-2; 0,-1,-2]; B=[2,2,-2; -1 5 -2; -1 1 2];
C=[5 -4 4; 1 0 4; 1 -1 5]; X=are(A,B,C)

norm(double(A'*X+X*A-X*B*X+C))   % 验证结果可见，结果很精确