f=[-3,2,-5]; A=[1 2 -1; 1 4 1; 1 1 0; 0 4 1]; B=[2;4;5;6];
x=bintprog(f,A,B,[],[])'

[x1,x2,x3]=meshgrid([0,1]);
i=find((x1+2*x2-x3<=2) & (x1+4*x2+x3<=4) & (x1+x2<=3) & (4*x1+x3<=6));
f=-3*x1(i)+2*x2(i)-5*x3(i); [fmin,ii]=sort(f);
index=i(ii(1)); x=[x1(index),x2(index),x3(index)]

x=[x1(i(ii)),x2(i(ii)),x3(i(ii))]; [x fmin]  % 还可以列出所有的可行解

