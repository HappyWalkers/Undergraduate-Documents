[t,y]=nlbound('c7fun4','c7fun3',[0,pi/2],[-1,1],1e-8);
plot(t,y); set(gca,'xlim',[0,pi/2]);

y0=tan(t-pi/4); norm(y(:,1)-y0)

norm(y(end,1)-1)
