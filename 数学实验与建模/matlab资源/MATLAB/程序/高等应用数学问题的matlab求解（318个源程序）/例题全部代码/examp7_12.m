x0=[1.2; 0; 0; -1.04935751];
tic, [t1,y1]=rk_4('apolloeq',[0,20,0.01],x0); toc
plot(y1(:,1),y1(:,3))     % ???Ƴ??켣????

tic, [t2,y2]=rk_4('apolloeq',[0,20,0.001],x0); toc
plot(y2(:,1),y2(:,3))     % ???Ƴ??켣????
