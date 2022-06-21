x0=[1.2; 0; 0; -1.04935751];
tic, [t,y]=ode45('apolloeq',[0,20],x0); toc
length(t), plot(y(:,1),y(:,3))

options=odeset; options.RelTol=1e-6;
tic, [t1,y1]=ode45('apolloeq',[0,20],x0,options); toc
length(t1), plot(y1(:,1),y1(:,3)),

min(diff(t1))

plot(t1(1:end-1),diff(t1))
