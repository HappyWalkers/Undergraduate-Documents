H=hilb(20); rank(H)

H=sym(hilb(20)); rank(H)  % �ɼ�ԭ����Ϊ���������

A=[16 2 3 13; 5 11 10 8; 9 7 6 12; 4 14 15 1];
[norm(A), norm(A,2), norm(A,1), norm(A,Inf), norm(A,'fro')]