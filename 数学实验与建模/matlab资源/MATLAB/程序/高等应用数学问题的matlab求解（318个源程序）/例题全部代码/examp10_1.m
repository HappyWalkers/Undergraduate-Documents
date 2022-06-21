A=[1,4,5,8,7,3]; B=[2,4,6,8,10]; C=[1,7,4,2,7,9,8];   % 集合定义
D=unique(C)  % 求解唯一运算，可见从 C 中剔除了重复的 7

E=union(A,B)   % 求出并集

F=intersect(A,B)  % 求出交集

G=setdiff(intersect(union(A,B),C),union(intersect(A,C),intersect(B,C)))

ismember(A,B)

A(ismember(A,B))

