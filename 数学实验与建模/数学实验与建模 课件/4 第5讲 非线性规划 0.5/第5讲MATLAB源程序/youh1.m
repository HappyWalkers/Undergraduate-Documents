H=[1 -1; -1 2]; 
c=[-2 ;-6];
A=[1 1; -1 2];  
b=[2;2];
Aeq=[];
beq=[];    
VLB=[0;0];VUB=[];
[x,z]=quadprog(H,c,A,b,Aeq,beq,VLB,VUB)
