x0=[-0.2; -0.7]; t_final=20;
mu=1; [t1,y1]=ode45('vdp_eq',[0,t_final],x0,[],mu);
mu=2; [t2,y2]=ode45('vdp_eq',[0,t_final],x0,[],mu);
plot(t1,y1,t2,y2,':')
figure; plot(y1(:,1),y1(:,2),y2(:,1),y2(:,2),':')

x0=[2;0]; t_final=3000;
mu=1000; [t,y]=ode45('vdp_eq',[0,t_final],x0,[],mu);
