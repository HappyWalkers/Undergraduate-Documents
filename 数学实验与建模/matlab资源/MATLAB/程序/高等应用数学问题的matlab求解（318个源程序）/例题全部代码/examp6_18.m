f=[-2,-4,-6,-8]; H=diag([2,2,2,2]);
OPT=optimset; OPT.LargeScale='off'; % 不使用大规模问题算法
A=[1,1,1,1; 3,3,2,1]; B=[5;10]; Aeq=[]; Beq=[]; LB=zeros(4,1);
[x,f_opt]=quadprog(H,f,A,B,Aeq,Beq,LB,[],[],OPT)
