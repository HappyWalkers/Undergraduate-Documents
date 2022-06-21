A=[6,1,4,2,1; 3,0,1,4,2; -3,-2,-5,8,4]; rank(A)

iA = pinv(A) % 非满秩矩阵的广义逆

norm(iA*A*iA-iA)   % 测试关系式 A^+ A A^+=A^+

norm(A*iA*A-A) % 测试关系式 A A^+ A=A

norm(iA*A-A'*iA')  % 测试 A^+*A 的对称性

norm(A*iA-iA'*A')  % 测试 A*A^+ 的对称性