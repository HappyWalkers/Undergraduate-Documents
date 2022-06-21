x0=[0;0.6;0.4;0;250;0;250];
A=[0,0,0,0,0,1,1;0,0,0,1,0,1,0;0,0,0,0,1,0,1];
b=[250;300;500];
Aeq=[1,1,1,0,0,0,0];beq=[1];
VLB=[0 0 0 0 0 0 0];VUB=[1,1,1,inf,inf,inf,inf];
[x,fval,exitflag,output]=fmincon('fun5',x0,A,b,Aeq,beq,VLB,VUB,'mycon5')
