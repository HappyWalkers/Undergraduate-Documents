x=[0.1:0.01:0.18];
y=[42 41.5 45 45.5 45 47.5 49 55 50];
rstool(x',y','linear',0.05)%多项式回归分析
%model可为linear（线性）purequadratic（纯二次）interaction（交叉）quadratic（完全二次）

%'linear' ：表示仅仅包括常数项和一次项。 
%'purequadratic'：表示包括常数项、一次项和二次项。 
%'interaction'：表示包括常数项、一次项和交叉项。 
%'quadratic'表示包括交叉项和二次项




%导入数据data
x1=data(:,1);
x2=data(:,2);
x3=data(:,3);
x4=data(:,4);
y=data(:,end);
stepwise([x1,x2,x3,x4],y)%逐步分析，顺便看数据的正确性



x=[0.1:0.01:0.18];
y=[42 41.5 45 45.5 45 47.5 49 55 50];
plot（x，y）
a=polyfit(x,y,1);
c=polyval(a,x);
%下面是检验
[b,bint,r,rint,stats]=regress(c',[ones(size(x))',x'])
rcoplot(r,rint)%看数据的正确性