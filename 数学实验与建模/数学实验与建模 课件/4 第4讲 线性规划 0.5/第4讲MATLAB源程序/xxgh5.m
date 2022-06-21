a=0;
while(1.1-a)>1
c=[-0.05 -0.27 -0.19 -0.185 -0.185];
Aeq=[1 1.01 1.02 1.045 1.065];
beq=[1];
A=[0 0.025 0 0 0;0 0 0.015 0 0;0 0 0 0.055 0;0 0 0 0 0.026];
b=[a;a;a;a];
vlb=[0,0,0,0,0];
vub=[];
[x,val]=linprog(c,A,b,Aeq,beq,vlb,vub);
a
x=x'
Q=-val
plot(a,Q,'.')
axis([0 0.1 0 0.5])
hold on
a=a+0.001;
end 
xlabel('a'),ylabel('Q')
