function c1ex5
f=-[2 1 4 3 1]'; A=[0 2 1 4 2; 3 4 5 -1 -1]; B=[54; 62]; 
xm=[0,0,3.32,0.678,2.57]; Ae=[]; Be=[];
[x,f_opt,key,c]=linprog(f,A,B,Ae,Be,xm);  %���һ�����Թ滮����
ctype=[-1; -1];  xM=inf*ones(5,1); intlist=ones(5,1);
x=ipslv_mex(f,A,B,intlist,xM,xm,ctype)  % ��������滮��Ҫ��װ�����滮������