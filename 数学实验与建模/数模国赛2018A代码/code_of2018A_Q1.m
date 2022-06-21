% Matlab
% Q1 .m
clear ;
close all ;
clc ;
pho = [300;862;74.2;1.18] ;%密度rou 列向量
c = [1377;2100;1726;1005] ;%比热容c 列向量
lamda = [0.082;0.37;0.045;0.028] ;%热传导率k 列向量
a=lamda./( pho .* c ) ;%热扩散率a_fa 列向量
d = [0.6;6;3.6;5]*10 ^ -3 ;%各层厚度Q1 列向量
TT=273.15;%单位转换
T_in=37;%体温
T_out=75;%环境温度Q1
T_s=48.08;%稳定温度
xmin =0;
xmax=sum( d ) ;%d为各层厚度
N=5400;%总时间90min=90*60=5400s
h=0.05*10^-3;%空间步长 Crank-Nicholson  x = xmin + ih
k=1;%时间步长t = nk       ooooooooooo1s aaa
r=k/h ^ 2 ;% r = k/2h^2 数字
I=round ( ( xmax-xmin ) /h ) ;%空间间隔数Ni = round(di/ h )
%% 构造线性方程组的系数矩阵
A=zeros ( 1 , I ) ;
B=zeros ( 1 , I +1) ;
C=zeros ( 1 , I ) ;
N1=round ( d ( 1 ) /h ) ;%空间间隔数Ni = round(di/ h )
N2=round ( d ( 2 ) /h ) ;
N3=round ( d ( 3 ) /h ) ;
N4=round ( d ( 4 ) /h ) ;
for i =1:N1
    A( i )=-a ( 1 ) * r ;
    B( i )=2+2*r *a ( 1 ) ;
    C( i )=-r *a ( 1 ) ;
end
for i=N1+1:N1+N2
    A( i )=-a ( 2 ) * r ;
    B( i )=2+2*r *a ( 2 ) ;
    C( i )=-r *a ( 2 ) ;
end
for i=N1+N2+1:N1+N2+N3
    A( i )=-a ( 3 ) * r ;
    B( i )=2+2*r *a ( 3 ) ;
    C( i )=-r *a ( 3 ) ;
end
for i=N1+N2+N3+1:N1+N2+N3+N4
    A( i )=-a ( 4 ) * r ;
    B( i )=2+2*r *a ( 4 ) ;
    C( i )=-r *a ( 4 ) ;
end%all the same
T=zeros ( I +1,N+1) ;%create the T, I空间间隔数，N总时长5400s
T ( : , 1 ) =(T_in+TT) * ones ( I +1 ,1) ;%一开始（T的第一列其实是T=0s时)整件衣服都是体温37，纵坐标代表时间，横坐标代表X，位置
T_xt=xlsread('C:\Users\anhuishuangqiao\Desktop\2018-A-Chinese\CUMCM-2018-Problem-A-Chinese-Appendix.xlsx','附件2','A3:B5403');
%T_xt，在求出模型的T之后，与附件给出的T_xt比较，求误差，选取误差最小的地方为h1
%% 寻找的最优拟合解h1
h_min=110;
h_max=120;
delta_h = 0.1 ;
H1=h_min : delta_h : h_max ;
delta=zeros ( 1 , length (H1) ) ;
for j =1: length (H1)
    h1=h_min+( j -1)* delta_h ;%赋值
    % h1 =121.41;
    k1=lamda ( 1 ) ; k2=lamda ( 2 ) ; k3=lamda ( 3 ) ; k4=lamda ( 4 ) ;%热传导率k:变量名lamda
    x1=d ( 1 ) ; x2=d ( 1 )+d ( 2 ) ; x3=d ( 1 )+d ( 2 )+d ( 3 ) ; x4=d ( 1 )+d ( 2 )+d ( 3 )+d ( 4 ) ;
    t1=T_out+TT; t2=T_in+TT; t3=T_s+TT;%外界，人体，稳态
    h5=-((h1* k2 * k3 * k4 * t1 )...%将h4用h1和其他参数表示，这里的t3其实是T4，也就是外界温度
        /( k1 * k2 * k3 * k4 -h1* k1 * k2 * k3 * x3 - h1* k1 * k2 * k4 * x2...
        - h1* k1 * k3 * k4 * x1 + h1* k1 * k2 * k3 * x4 + h1* k1 * k2 * k4 * x3...
        + h1* k1 * k3 * k4 * x2 + h1* k2 * k3 * k4 * x1 )...
        - ( h1* k2 * k3 * k4 * t3 )...
        /( k1 * k2 * k3 * k4 -h1* k1 * k2 * k3 * x3- h1* k1 * k2 * k4 * x2...
        - h1* k1 * k3 * k4 * x1 + h1* k1 * k2 * k3 * x4 + h1* k1 * k2 * k4 * x3...
        + h1* k1 * k3 * k4 * x2 + h1* k2 * k3 * k4 * x1 ) )...
        /( t2 / k1-t3 / k1 ) ;
    % h5 =8.36;
    AA=diag (B)+diag (A, 1 )+diag (C,-1) ;%AA为方程组的系数矩阵。。%A.B.C都是行向量,B比A，C长一个，生成类似于对角阵的矩阵AA
    
    AA( 1 , 1 )=lamda ( 1 ) /h+h1 ;%T1，T4分别为外界温度和人体温度%第7页边界条件%人体4层，外界1层热对流
    AA( 1 , 2 )=-lamda ( 1 ) /h ;
    AA( I +1, I )=-lamda ( 4 ) /h ;%空间间隔数I
    AA( I +1, I +1)=lamda ( 4 ) /h+h5 ;
    
    AA(N1+1,N1)=-lamda ( 1 ) ;%层与层之间热传导方程，交界处
    AA(N1+1,N1+1)=lamda ( 1 )+lamda ( 2 ) ;%列数代表和 T几 相乘，而且B为对角线上的元素，其行标与列标相同
    AA(N1+1,N1+2)=-lamda ( 2 ) ;
    AA(N1+N2+1,N1+N2)=-lamda ( 2 ) ;
    AA(N1+N2+1,N1+N2+1)=lamda ( 2 )+lamda ( 3 ) ;
    AA(N1+N2+1,N1+N2+2)=-lamda ( 3 ) ;
    AA(N1+N2+N3+1,N1+N2+N3)=-lamda ( 3 ) ;
    AA(N1+N2+N3+1,N1+N2+N3+1)=lamda ( 3 )+lamda ( 4 ) ;
    AA(N1+N2+N3+1,N1+N2+N3+2)=-lamda ( 4 ) ;
    
    for n=1:k :N   %k时间步长，每一秒热量进行传导，每一层（随着i的变化）的温度都在更新
        D=zeros ( I +1 ,1) ;%D为方程组的右边矩阵%create
        D( 1 )=h1 *( T_out+TT) ;%外界%边界条件%第7页边界条件%人体4层，外界1层热对流
        D( I +1)=h5 *( T_in+TT) ;%人体
        for i = 2 : 1 :N1%层内热扩散，由于T(:.n+1)表示的是第n秒，故横坐标I要比原来少一个，以求对应上相应的n+1
            D( i )=r *a ( 1 ) *T( i -1,n ) +(2-2* r *a ( 1 ) ) *T( i , n )+r *a ( 1 ) *T( i +1,n ) ;
        end
        for i=N1+ 1 : 1 :N1+N2
            D( i )=r *a ( 2 ) *T( i -1,n ) +(2-2* r *a ( 2 ) ) *T( i , n )+r *a ( 2 ) *T( i +1,n ) ;
        end
        for i=N1+N2+ 1 : 1 :N1+N2+N3
            D( i )=r *a ( 3 ) *T( i -1,n ) +(2-2* r *a ( 3 ) ) *T( i , n )+r *a ( 3 ) *T( i +1,n ) ;
        end
        for i=N1+N2+N3+ 1 : 1 :N1+N2+N3+N4
            D( i )=r *a ( 4 ) *T( i -1,n ) +(2-2* r *a ( 4 ) ) *T( i , n )+r *a ( 4 ) *T( i +1,n ) ;
        end
        D(N1+1)=0;%层间热传导，方程右边皆为0
        D(N1+N2+1)=0;
        D(N1+N2+N3+1)=0;
        T ( : , n+1)=AA\D;%解方程，由第n列的T更新D，由新的D算出第n+1列的T
    end
     figure( 1 ) ;
     mesh(0:k:N,1000*(0:h:sum(d)),(T-TT));
     ylabel('x/mm');
     xlabel('t/s');
     zlabel('T℃/');
    delta(j)=sqrt(sum((T_xt(:,2)-T(end,:)'+TT).^2)/length(T_xt(:,1))) ;
    %方均根误差
end
%% 绘制方均根误差图像，寻找最优拟合项
figure ( 2 ) ;
plot (H1 , delta ) ;
xlabel ( ' h1 /(W（/m℃）^2*) ' ) ;
ylabel ( 'T℃/ ') ;
[ ~ ,position] = min(delta) ;
h1_p=H1(position ) ;%给出最小的h1
disp ( h1_p ) ;
%%
figure(2);
 plot(T_xt(:,1) , T_xt(:,2)-(T(end , : )-TT)')  ;
 xlabel('t/s');
 ylabel('delta_T/℃');
 legend('拟合函数与原数据相差');
 
 figure(3);
 plot(1000 * ( 0 : h : sum(d)) ,T(:,end)-TT);
 xlabel('x/mm') ;
 ylabel('T/℃');
 legend('结尾时刻温度随深度分布');
 
 figure(5);
 plot(T_xt(:,1) ,T(end,:)-TT,'.',T_xt(:,1) ,T_xt(:,2),'r');
 xlabel('t/s');
 ylabel('T/℃');
 title('皮肤外侧温度随时间分布');
 legend('模型所得温度','附件所给温度曲线');
%% 输出problem1 . 文件x l s x
T_problem1=zeros(N+1 ,4) ;
T_problem1 ( : , 1 )=T( 1 , : )';
T_problem1 ( : , 2 )=T(N1+1 ,:)';
T_problem1 ( : , 3 )=T(N1+N2+1 ,:)';
T_problem1 ( : , 4 )=T(N1+N2+N3+1 ,:)';
T_problem1=T_problem1-TT;
%x l s w r i t e ( ’C: \ Users \wangc\ Desktop \CUMCM正赛\2018\ code \ problem1 . x l s x ’ , T_problem1 ) ;
figure( 4 ) ;
plot(0:k:N,T_problem1(:,1)',0:k:N,T_problem1(:,2)',0:k:N,T_problem1(:,3)',0:k:N,T_problem1(:,4)',0:k:N,T_xt(:,2)')
legend( ' 层I与环境交界面 ' , ' 层I与层II交界面 ' , ' 层II与层III交界面'  ,' 层III与层IV交界面 ' , ' 层IV与皮肤交界面' ) ;
xlabel('t/s') ;
ylabel( 'T℃/') ;