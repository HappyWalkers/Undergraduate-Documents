A=[[-2 1 0; 0 -2 1; 0 0 -2], zeros(3,2); zeros(2,3) [-5 1; 0 -5]];
expm(A)   % 数值解求解

logm(ans)   % 数值解求对数

norm(ans-A)

syms t; expm(A*t)

format short; expm3(A)  % 显示精度降低，利于排版