syms t; A=sym([-21,19,-20; 19,-21,20; 40,-40,-40]);
y0=[1; 0; -1]; y=expm(A*t)*y0

opt=odeset; opt.RelTol=1e-6;
tic,[t,y]=ode45('c7xstf1',[0,1],[1;0;-1],opt); toc

x1=exp(-2*t); x2=exp(-40*t).*cos(40*t); x3=exp(-40*t).*sin(40*t);
y1=[0.5*x1+0.5*x2+0.5*x3, 0.5*x1-0.5*x2-0.5*x3, -x2+x3];
plot(t,y,t,y1,':')

tic,[t2,y2]=rk_4('c7xstf1',[0,1,0.01],[1;0;-1]); toc
plot(t,y1,t2,y2,':')