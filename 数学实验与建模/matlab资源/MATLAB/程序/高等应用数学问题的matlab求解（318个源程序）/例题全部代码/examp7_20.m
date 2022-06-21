M=[1,0,0; 0,1,0; 0,0,0]; options=odeset; options.Mass=M;
x0=[0.8; 0.1; 0.1]; [t,x]=ode15s(@c7eqdae,[0,20],x0,options); plot(t,x)

x0=[0.8; 0.1];
fDae=inline(['[-0.2*x(1)+x(2)*(1-x(1)-x(2))+0.3*x(1)*x(2);',...
    '2*x(1)*x(2)-5*x(2)*(1-x(1)-x(2))-2*x(2)*x(2)]'],'t','x');
[t1,x1]=ode45(fDae,[0,20],x0); plot(t1,x1,t1,1-sum(x1'))

x0=[0.8;0.1;2]; x0F=[1;1;0]; xd0=[1;1;1]; xd0F=[];
[x0,xd0]=decic(@c7midae,0,x0,x0F,xd0,xd0F); [x0,xd0]  % 相容初始条件

res=ode15i('c7midae',[0,20],x0,xd0); plot(res.x,res.y)