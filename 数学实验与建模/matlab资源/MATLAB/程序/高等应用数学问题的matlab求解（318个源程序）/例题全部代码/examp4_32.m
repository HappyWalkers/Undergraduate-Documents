A=[1,3,5,7; 2,4,6,8]; [L,A1,M]=svd(A)

A2=L*A1*M'   % ��ԭ A ��

norm(A-A2)