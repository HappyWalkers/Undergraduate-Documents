h=0.05; x=0:h:pi; syms x1; y=sin(x1)/(x1^2+4*x1+3);
yy1=diff(y); f1=subs(yy1,x1,x);   % 求各阶导数的解析解与对照数据
yy2=diff(yy1); f2=subs(yy2,x1,x); yy3=diff(yy2); f3=subs(yy3,x1,x);
yy4=diff(yy3); f4=subs(yy4,x1,x);

y=sin(x)./(x.^2+4*x+3);   % 生成已知数据点
[y1,dx1]=diff_ctr(y,h,1); subplot(221),plot(x,f1,dx1,y1,':');
[y2,dx2]=diff_ctr(y,h,2); subplot(222),plot(x,f2,dx2,y2,':')
[y3,dx3]=diff_ctr(y,h,3); subplot(223),plot(x,f3,dx3,y3,':');
[y4,dx4]=diff_ctr(y,h,4); subplot(224),plot(x,f4,dx4,y4,':')

norm((y4-f4(4:60))./f4(4:60))