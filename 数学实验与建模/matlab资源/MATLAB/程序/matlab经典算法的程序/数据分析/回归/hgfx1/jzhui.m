x1=[5.5 2.5 8 3 3 2.9 8 9 4 6.5 5.5 5 6 5 3.5 8 6 4 7.5 7]';
x2=[31 55 67 50 38 71 30 56 42 73 60 44 50 39 55 70 40 50 62 59]';
x3=[10 8 12 7 8 12 12 5 8 5 11 12 6 10 10 6 11 11 9 9]';
x4=[8 6 9 16 15 17 8 10 4 16 7 12 6 4 4 14 6 8 13 11]';
y=[79.3 200.1 163.1 200.1 146.0 177.7 30.9 291.9 160 339.4 159.6 86.3 237.5 107.2 155 201.4 100.2 135.8 223.3 195]';
X=[ones(size(x1)),x1,x2,x3,x4];
[b,bint,r,rint,stats]=regress(y,X)
Q=r'*r
sigma=Q/18
rcoplot(r,rint)pause
X1=[x1,x2,x3,x4];
stepwise(X1,y,[1,2,3])
%X2=[ones(size(x1)),x2,x3];
%X3=[ones(size(x1)),x1,x2,x3];
%X4=[ones(size(x1)),x2,x3,x4];
%[b1,b1int,r1,r1int,stats1]=regress(y,X2)
%[b2,b2int,r2,r2int,stats2]=regress(y,X3);
%[b3,b3int,r3,r3int,stats3]=regress(y,X4);

<i