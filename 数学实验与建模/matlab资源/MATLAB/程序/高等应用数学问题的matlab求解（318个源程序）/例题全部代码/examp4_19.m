A=[6,1,4,2,1; 3,0,1,4,2; -3,-2,-5,8,4]; rank(A)

iA = pinv(A) % �����Ⱦ���Ĺ�����

norm(iA*A*iA-iA)   % ���Թ�ϵʽ A^+ A A^+=A^+

norm(A*iA*A-A) % ���Թ�ϵʽ A A^+ A=A

norm(iA*A-A'*iA')  % ���� A^+*A �ĶԳ���

norm(A*iA-iA'*A')  % ���� A*A^+ �ĶԳ���