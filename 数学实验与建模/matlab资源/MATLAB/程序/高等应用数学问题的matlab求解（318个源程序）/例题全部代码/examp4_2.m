C=[1 2 3]; V=diag(C)

V1=diag(V)'   % 将列向量通过转置变换成行向量

C=[1 2 3]; V=diag(C,2)

V=diag([1 2 3 4])+diag([2 3 4],1)+diag([5 4 3],-1)
