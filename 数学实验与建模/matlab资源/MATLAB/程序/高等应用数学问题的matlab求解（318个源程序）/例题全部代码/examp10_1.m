A=[1,4,5,8,7,3]; B=[2,4,6,8,10]; C=[1,7,4,2,7,9,8];   % ���϶���
D=unique(C)  % ���Ψһ���㣬�ɼ��� C ���޳����ظ��� 7

E=union(A,B)   % �������

F=intersect(A,B)  % �������

G=setdiff(intersect(union(A,B),C),union(intersect(A,C),intersect(B,C)))

ismember(A,B)

A(ismember(A,B))

