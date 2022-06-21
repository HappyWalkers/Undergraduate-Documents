function huisexitong()
%原始发电量数据
X0=[306.35,311.2,324.9,343.4,361.61,390.76,421.36,458.75,494.9,522.78,547.22,588.7,647.18,712.34,778.32,835.31,888.1,923.16,939.48];
KK=300;   %KK大于30，越大越没有问题
x0=sin(sqrt(X0)/KK);   %得到变换后的值，作为原始的数据

n=length(x0);
for k=1:n   
    x1(k)=sum(x0(1:k));              %计算x1
end
z(1)=0;
for k=1:n-1
    z(k+1)=(x1(k)+2*Newton(1:n,x1,k+2/4)+4*(Newton(1:n,x1,k+1/4)+Newton(1:n,x1,k+3/4))+x1(k+1))/12;        %计算z1
end

Y=(x0(2:end))';
B=[-1*(z(2:end))' ones(n-1,1)];
au=(inv(B'*B))*(B')*Y;              %得到a和u
a=au(1);
u=au(2);


%x01表示预测值
for m=1:n
    for k=0:n-1
        x01(k+1)=(x1(m)-u/a)*exp(-a*(k-m+1))+u/a;            %按预测公式计算预测值
    end
    x02=huanyuan(x01);           %预测出来的值需要前后两项想减，得到预测值
    derta(m)=100*sum(abs((x02(1:n)-x0)./x0))/n;
end
figure
plot(derta)
title('各m下的平均误差曲线')
xlabel('m')
ylabel('平均误差 %')
[Y m_min]=min(derta);    %找到平均误差最小时对应的m

dd=3;    %需要预测的年数
m=m_min;    %此处m取平均误差最小的m，也可以在此修改m
for k=0:n-1+dd
    x01(k+1)=(x1(m)-u/a)*exp(-a*(k-m+1))+u/a;            %按预测公式计算预测值
end
x02=huanyuan(x01);           %预测出来的值需要前后两项相减，得到预测值

yucezhi=(asin(x02)*KK).^2;


X0all=[306.35,311.2,324.9,343.4,361.61,390.76,421.36,458.75,494.9,522.78,547.22,588.7,647.18,712.34,778.32,835.31,888.1,923.16,939.48,988.6,1073.62,1164.29];
num=1;
for i=1980:2001
    year{num}=num2str(i);
    num=num+1;
end

figure
axes('XTickLabel',year,'XTick',1:22)
axis([1 22 200 1400])
hold on
h(1)=plot(yucezhi,'*-');
h(2)=plot(X0all,'ro-');
legend(h,{'预测值','原始值'},'Location','NorthWest')
title('原始发电量和预测发电量')
xlabel('年份');
ylabel('发电量')
end

function XD=huanyuan(X)
%灰色系统：还原算子，输入原序列(仅包含一行)，输出始点零化生成序列（仅包含一行）
n=length(X);
XD(1)=X(1);
for k=2:n
    XD(k)=X(k)-X(k-1);
end
end

function yi=Newton(x,y,xi)
%Newton插值方法，给定一系列插值的点(x,y)，得到在x=xi处的，牛顿插值多项的值yi
n=length(x);
m=length(y);
A=zeros(n);    %定义差商表
A(:,1)=y;      %差商表第一列为y
for j=2:n               %j为列标
    for i=1:(n-j+1)     %i为行标
        A(i,j)=(A(i+1,j-1)-A(i,j-1))/(x(i+j-1)-x(i));   %计算差商表
    end
end
%根据差商表,求对应的牛顿插值多项式在x=xi处的值yi
N(1)=A(1,1);
for j=2:n
    T=1;
    for i=1:j-1
        T=T*(xi-x(i));
    end
    N(j)=A(1,j)*T;
end
yi=sum(N);   %将x=xi带入牛顿插值多项式，得到的yi的值
end







