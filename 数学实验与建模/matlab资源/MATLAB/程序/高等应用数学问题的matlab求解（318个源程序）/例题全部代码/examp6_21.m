f=-[2 1 4 3 1]'; A=[0 2 1 4 2; 3 4 5 -1 -1]; intlist=ones(5,1);
B=[54; 62]; ctype=[-1; -1]; xm=[0,0,3.32,0.678,2.57]; xM=inf*ones(5,1);
[res,b]=ipslv_mex(f,A,B,intlist,xM,xm,ctype)  % 因为返回的 b=0，表示优化成功

[x1,x2,x3,x4,x5]=ndgrid(1:20,0:20,4:20,1:20,3:20);
i=find((2*x2+x3+4*x4+2*x5<=54) & (3*x1+4*x2+5*x3-x4-x5<=62));
f=-2*x1(i)-x2(i)-4*x3(i)-3*x4(i)-x5(i); [fmin,ii]=sort(f);
index=i(ii(1)); x=[x1(index),x2(index),x3(index),x4(index),x5(index)]

fmin(1:10)'

intlist=[1,0,0,1,1];
[res,b]=ipslv_mex(f,A,B,intlist,xM,xm,ctype)
