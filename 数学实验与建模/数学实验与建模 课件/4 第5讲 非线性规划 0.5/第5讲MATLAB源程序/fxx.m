clear 
close
clc

x0=[3;2.5];
VLB=[0 0];
VUB=[5 10];

option = optimset('Algorithm','active-set'); % ʹ��active-set�㷨 
[x,fval,exitflag,output]=fmincon('fun',x0,[],[],[],[],VLB,VUB,'mycon2', option)
