fh=inline('sqrt(1-x.^2/2)','x');  % 内积分上限
fl=inline('-sqrt(1-x.^2/2)','x'); % 内积分下限
f=inline('exp(-x.^2/2).*sin(x.^2+y)','y','x');  % 交换顺序的被积函数
y=quad2dggen(f,fl,fh,-1/2,1,eps),

syms x y   % 现在考虑解析解方法
i1=int(exp(-x^2/2)*sin(x^2+y),y,-sqrt(1-x^2/2),sqrt(1-x^2/2));
int(i1,x,-1/2,1) % 求取解析解时得出错误信息
vpa(ans)

vpa(ans,70)   % 不存在解析解，但可以求高精度数值解

fh=inline('sqrt(1-y.^2)','y');  % 内积分上限
fl=inline('-sqrt(1-y.^2)','y'); % 内积分下限
f=inline('exp(-x.^2/2).*sin(x.^2+y)','x','y');  % 交换顺序的被积函数
I=quad2dggen(f,fl,fh,-1,1,eps),
