clear;
close all;
clc;
%% 构造系数矩阵
%相关参数
rou=[300;862;74.2;1.18];%密度, 从第一层到第四层，第一层与外界接触，第四层是空气层
c=[1377;2100;1726;1005];%比热
k=[0.082;0.37;0.045;0.028];%热传导率
afa=k./(rou.*c);%热扩散率

dt=1;%时间步长1s
h=0.05*10^-3;%空间步长，转换单位 米
r=dt/h^2;

%% 方程3，热扩散方程
T_sum=5400;%总时间
d=[0.6;6;3.6;5]*10^-3;%厚度
N1=round(d(1)/h);%各层h个数
N2=round(d(2)/h);
N3=round(d(3)/h);
N4=round(d(4)/h);
N=N1+N2+N3+N4;
A=zeros(1,N);%行向量
B=zeros(1,N+1);
C=zeros(1,N);
for i=1:N1+N2+N3+N4%系数A，B，C
    if i<=N1
        a=afa(1);
    elseif i<=N1+N2
        a=afa(2);
    elseif i<=N1+N2+N3
        a=afa(3);
    elseif i<=N1+N2+N3+N4
        a=afa(4);
    end
    A(i)=-r*a;
    B(i)=2+2*r*a;
    C(i)=-r*a;
end


XI=diag(B)+diag(A,1)+diag(C,-1);%系数矩阵XI XI*T=D
T=zeros(N+1,T_sum+1);%待求矩阵T,行标表示空间，列标表示时间
D=zeros(N+1,1);%方程右边D

%% 三个交界处，热传导方程
XI(N1+1,N1+1)=k(1)+k(2);%将所有方程统一到一个系数矩阵里去，形式上对应，
XI(N1+1,N1)=-k(1);
XI(N1+1,N1+2)=-k(2);
D(N1+1)=0;

XI(N1+N2+1,N1+N2+1)=k(2)+k(3);
XI(N1+N2+1,N1+N2)=-k(2);
XI(N1+N2+1,N1+N2+2)=-k(3);
D(N1+N2+1)=0;

XI(N1+N2+N3+1,N1+N2+N3+1)=k(3)+k(4);
XI(N1+N2+N3+1,N1+N2+N3)=-k(3);
XI(N1+N2+N3+1,N1+N2+N3+2)=-k(4);
D(N1+N2+N3+1)=0;

%% 两个边界条件，热对流方程，对h1赋值搜索符合附件2的值
%参数
Tk=273.15;%单位转换
T_in=37;%体温
T_out=75;%外界温度
T_end=48.08;%稳态时的温度
T(:,1)=T_in+Tk;%0s时整件衣服都是体温

h_min=110;%由资料可得，先进行大致搜索，再缩小步长精细搜索
h_max=120;
dh=0.1;
H1=h_min:dh:h_max;
delta=zeros(1,length(H1));%预分配内存
T_give=xlsread('C:\Users\anhuishuangqiao\Desktop\2018-A-Chinese\CUMCM-2018-Problem-A-Chinese-Appendix.xlsx','附件2','A3:B5403');

for l=1:length(H1)%对h1赋值，进行搜索，取最符合所给数据的T
    h1=h_min+(l-1)*dh;
    h4=get_h4_second(k,d,h1,T_out,T_in,T_end,Tk);
    
    XI(1,1)=h1+k(1)/h;
    XI(1,2)=-k(1)/h;
    D(1)=h1*(T_out+Tk);
    
    XI(N+1,N+1)=h4+k(4)/h;
    XI(N+1,N)=-k(4)/h;
    D(N+1)=h4*(T_in+Tk);
    
    %% 计算方程组，每次用Tn更新D，再用D算出Tn+1
    for n=1:dt:T_sum%外层循环时间，内层循环空间
        for j=1:N1+N2+N3+N4
            if j<=N1 && j>1
                a=afa(1);
            elseif j<=N1+N2 && j>N1+1
                a=afa(2);
            elseif j<=N1+N2+N3 && j>N1+N2+1
                a=afa(3);
            elseif j<=N1+N2+N3+N4 && j>N1+N2+N3+1
                a=afa(4);
            else
                continue;
            end
            D(j)=r*a*T(j+1,n)+(2-2*r*a)*T(j,n)+r*a*T(j-1,n);
        end
        T(:,n+1)=XI\D;
    end
    delta(l)=sqrt( sum( ( T_give(:,2)+Tk-T(N+1,:)'  ).^2 )/length(T_give(:,1)));
end
%% 计算方均根误差，绘制图像，寻找最优拟合项
plot(H1,delta);
xlabel('h1/(W/(m^2*C)');
ylabel('T/°C');
[~,position]=min(delta);
disp(H1(position));
%% 生成温度分布的excel文件
T_xls=zeros(T_sum+1,5);
T_xls(:,1)=T(1,:)';
T_xls(:,2)=T(N1+1,:)';%输出模型各交界处温度
T_xls(:,3)=T(N1+N2+1,:)';
T_xls(:,4)=T(N1+N2+N3+1,:)';
T_xls(:,5)=T(N1+N2+N3+N4+1,:)';
T_xls=T_xls-Tk;
xlswrite('C:\Users\anhuishuangqiao\Desktop\My_Code\Problem1.xlsx',T_xls);
%% 画图
%%
figure(1);
plot(T_give(:,1) , T_give(:,2)-(T(end , : )-Tk)')  ;
xlabel('t/s');
ylabel('delta_T℃/');
legend('拟合函数与原数据相差');

figure(2);
plot(1000 * ( 0 : h : sum(d)) ,T(:,end)-Tk);
xlabel('x /mm') ;
ylabel('T℃/');
legend('结尾时刻温度随深度分布');

figure(3);
plot(T_give(:,1) ,T(end,:)-Tk,'.',T_give(:,1) ,T_give(:,2),'r');
xlabel('t/s');
ylabel('T/℃');
title('皮肤外侧温度随时间分布');
legend('模型所得温度','附件所给温度曲线');

figure( 4 ) ;
plot(0:dt:T_sum,T_xls(:,1)',0:dt:T_sum,T_xls(:,2)',0:dt:T_sum,T_xls(:,3)',0:dt:T_sum,T_xls(:,4)',0:dt:T_sum,T_xls(:,5)')
legend( ' 层I与环境交界面 ' , ' 层I与层II交界面 ' , ' 层II与层III交界面'  ,' 层III与层IV交界面 ' , ' 层IV与皮肤交界面' ) ;
xlabel('t/s') ;
ylabel( 'T℃/') ;

figure(5) ;
mesh(0:dt:T_sum,1000*(0:h:sum(d)),(T-Tk));
ylabel('x/mm');
xlabel('t/s');
zlabel('T℃/');