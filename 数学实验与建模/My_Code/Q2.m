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

d2=0.1;
dmin=17;%第二层厚度范围
dmax=19;
D_enough=dmin:d2:dmax;%第二层厚度搜索域
D_select=100*ones(250,1);%满足条件的第二层厚度值
for m=1:length(D_enough)%对第二层厚度进行搜索，取符合条件得最小值
    d_enough=dmin+(m-1)*d2;
    %% 方程3，热扩散方程
    T_sum=3600;%总时间
    d=[0.6;d_enough;3.6;5.5]*10^-3;%厚度
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
    T_out=65;%外界温度
    T_end=48.08;%稳态时的温度
    T(:,1)=T_in+Tk;%0s时整件衣服都是体温
    
    h1=117.4000;
    h4=8.3653;
    
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
    
    %% 找出符合条件的最小第二层厚度（温度不超过47?C，且超过44?C的时间不超过5分钟）
    times=0;
    flag=1;
    for b=1:T_sum+1
        if T(N+1,b)>44+Tk
            times=times+1;
        end
    end
    
    if max(T(N+1,:))>47+Tk || times>300
        flag=0;
    end
    
    if flag==1
        D_select(m)=d_enough;
    end
end
d_get=min(D_select);
disp(d_get);