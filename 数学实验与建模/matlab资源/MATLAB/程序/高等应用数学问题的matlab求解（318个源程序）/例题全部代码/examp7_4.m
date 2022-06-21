syms t; u=exp(-5*t)*cos(2*t+1)+5;    % 定义输入函数
uu=laplace(5*diff(u,2)+4*diff(u)+2*u);   % 对等号右侧整个式子进行变换
uu=collect(simple(uu)); latex(uu)    % 化简

syms s; G=uu/(s^4+10*s^3+35*s^2+50*s+24);
Y=residue(G,s); y=ilaplace(Y); latex(simple(y))

syms t; u=exp(-5*t)*cos(2*t+1)+5;    % 定义输入函数
uu=laplace(5*diff(u,2)+4*diff(u)+2*u)   % 求出并显示等号右侧式子

y1=dsolve(['D4y+10*D3y+35*D2y+50*Dy+24*y=',...
    '87*exp(-5*t)*cos(2*t+1)+92*exp(-5*t)*sin(2*t+1)+10'],...
    'y(0)=0','Dy(0)=0','D2y(0)=0','D3y(0)=0');
simple(y-y1)   % 验证两种方法的结果完全一致

ezplot(y,[0,10]);  axis([0,10,0,0.6])  % 手工调整坐标系范围
