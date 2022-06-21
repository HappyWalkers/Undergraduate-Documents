t_final=100; x0=[0;0;1e-10];
b1=8/3; r1=10; s1=28;  % 并不要求变量名必须是 beta 等
[t,x]=ode45('lorenz1',[0,t_final],x0,[],b1,r1,s1);
plot(t,x),
figure; plot3(x(:,1),x(:,2),x(:,3)); axis([10 42 -20 20 -20 25]);

t_final=100; x0=[0;0;1e-10];
b2=2; r2=5; s2=20;
[t2,x2]=ode45('lorenz1',[0,t_final],x0,[],b2,r2,s2);
plot(t2,x2),
figure; plot3(x2(:,1),x2(:,2),x2(:,3)); axis([0 72 -20 22 -35 40]);

f2=inline(['[-beta*x(1)+x(2)*x(3); -rho*x(2)+rho*x(3);',...
    '-x(1)*x(2)+sigma*x(2)-x(3)]'],'t','x','flag','beta','rho','sigma');

t_final=100; x0=[0;0;1e-10];
b2=2; r2=5; s2=20;
[t2,x2]=ode45(f2,[0,t_final],x0,[],b2,r2,s2);
plot(t2,x2),
figure; plot3(x2(:,1),x2(:,2),x2(:,3)); axis([0 72 -20 22 -35 40]);

