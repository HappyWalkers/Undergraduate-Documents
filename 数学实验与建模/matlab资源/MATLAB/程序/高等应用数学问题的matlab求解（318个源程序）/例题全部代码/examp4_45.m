A=[[-2 1 0; 0 -2 1; 0 0 -2], zeros(3,2); zeros(2,3) [-5 1; 0 -5]];
expm(A)   % ��ֵ�����

logm(ans)   % ��ֵ�������

norm(ans-A)

syms t; expm(A*t)

format short; expm3(A)  % ��ʾ���Ƚ��ͣ������Ű�