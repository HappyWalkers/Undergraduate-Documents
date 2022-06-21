f=[-3,2,-5]; xm=[0;0;0]; xM=[1;1;1]; intlist=[1;1;1];
A=[1 2 -1; 1 4 1; 1 1 0; 0 4 1]; B=[2;4;5;6]; ctype=-1*ones(4,1);
[res,b]=ipslv_mex(f,A,B,intlist,xM,xm,ctype)