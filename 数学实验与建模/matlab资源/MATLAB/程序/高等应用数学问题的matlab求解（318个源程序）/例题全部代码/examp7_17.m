opt=odeset; opt.RelTol=1e-6;
[t,x]=ode45('c7ximp',[0,10],[0; 0],opt); plot(t,x)
