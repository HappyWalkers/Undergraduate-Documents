t_final=100; x0=[0;0;1e-10];
[t,x]=ode45('lorenzeq',[0,t_final],x0);plot(t,x),
figure;  % 打开新图形窗口
plot3(x(:,1),x(:,2),x(:,3));
axis([10 42 -20 20 -20 25]);  % 根据实际数值手动设置坐标系

comet3(x(:,1),x(:,2),x(:,3))