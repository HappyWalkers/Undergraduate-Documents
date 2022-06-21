tic,[t2,y2]=ode45('c7exstf2',[0,100],[0;1]); toc

length(t2), plot(t2,y2)

format long, [min(diff(t2)), max(diff(t2))]

plot(t2(1:end-1),diff(t2))

opt=odeset; opt.RelTol=1e-6;
tic,[t1,y1]=ode15s('c7exstf2',[0,100],[0;1],opt); toc

length(t1), plot(t1,y1)