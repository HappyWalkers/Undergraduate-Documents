A=[0 2 1 4 2; 3 4 5 -1 -1]; intlist=ones(5,1); Aeq=[]; Beq=[];
B=[54; 62]; ctype=[-1; -1];
xm=[0,0,4,1,3]'; xM=20000*ones(5,1); x0=xm;
[errmsg,f,X]=bnb20('c6miopt',x0,intlist,xm,xM,A,B,Aeq,Beq); X=X'

intlist=[1,0,0,1,1]';xm=[0,0,3.32,1,3]';
[errmsg,f,X]=bnb20('c6miopt',x0,intlist,xm,xM,A,B,Aeq,Beq); X

