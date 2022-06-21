clear;
close all;
clc;
%% ����ϵ������
%��ز���
rou=[300;862;74.2;1.18];%�ܶ�, �ӵ�һ�㵽���Ĳ㣬��һ�������Ӵ������Ĳ��ǿ�����
c=[1377;2100;1726;1005];%����
k=[0.082;0.37;0.045;0.028];%�ȴ�����
afa=k./(rou.*c);%����ɢ��

dt=1;%ʱ�䲽��1s
h=0.05*10^-3;%�ռ䲽����ת����λ ��
r=dt/h^2;

%% ����3������ɢ����
T_sum=5400;%��ʱ��
d=[0.6;6;3.6;5]*10^-3;%���
N1=round(d(1)/h);%����h����
N2=round(d(2)/h);
N3=round(d(3)/h);
N4=round(d(4)/h);
N=N1+N2+N3+N4;
A=zeros(1,N);%������
B=zeros(1,N+1);
C=zeros(1,N);
for i=1:N1+N2+N3+N4%ϵ��A��B��C
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


XI=diag(B)+diag(A,1)+diag(C,-1);%ϵ������XI XI*T=D
T=zeros(N+1,T_sum+1);%�������T,�б��ʾ�ռ䣬�б��ʾʱ��
D=zeros(N+1,1);%�����ұ�D

%% �������紦���ȴ�������
XI(N1+1,N1+1)=k(1)+k(2);%�����з���ͳһ��һ��ϵ��������ȥ����ʽ�϶�Ӧ��
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

%% �����߽��������ȶ������̣���h1��ֵ�������ϸ���2��ֵ
%����
Tk=273.15;%��λת��
T_in=37;%����
T_out=75;%����¶�
T_end=48.08;%��̬ʱ���¶�
T(:,1)=T_in+Tk;%0sʱ�����·���������

h_min=110;%�����Ͽɵã��Ƚ��д�������������С������ϸ����
h_max=120;
dh=0.1;
H1=h_min:dh:h_max;
delta=zeros(1,length(H1));%Ԥ�����ڴ�
T_give=xlsread('C:\Users\anhuishuangqiao\Desktop\2018-A-Chinese\CUMCM-2018-Problem-A-Chinese-Appendix.xlsx','����2','A3:B5403');

for l=1:length(H1)%��h1��ֵ������������ȡ������������ݵ�T
    h1=h_min+(l-1)*dh;
    h4=get_h4_second(k,d,h1,T_out,T_in,T_end,Tk);
    
    XI(1,1)=h1+k(1)/h;
    XI(1,2)=-k(1)/h;
    D(1)=h1*(T_out+Tk);
    
    XI(N+1,N+1)=h4+k(4)/h;
    XI(N+1,N)=-k(4)/h;
    D(N+1)=h4*(T_in+Tk);
    
    %% ���㷽���飬ÿ����Tn����D������D���Tn+1
    for n=1:dt:T_sum%���ѭ��ʱ�䣬�ڲ�ѭ���ռ�
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
%% ���㷽����������ͼ��Ѱ�����������
plot(H1,delta);
xlabel('h1/(W/(m^2*C)');
ylabel('T/��C');
[~,position]=min(delta);
disp(H1(position));
%% �����¶ȷֲ���excel�ļ�
T_xls=zeros(T_sum+1,5);
T_xls(:,1)=T(1,:)';
T_xls(:,2)=T(N1+1,:)';%���ģ�͸����紦�¶�
T_xls(:,3)=T(N1+N2+1,:)';
T_xls(:,4)=T(N1+N2+N3+1,:)';
T_xls(:,5)=T(N1+N2+N3+N4+1,:)';
T_xls=T_xls-Tk;
xlswrite('C:\Users\anhuishuangqiao\Desktop\My_Code\Problem1.xlsx',T_xls);
%% ��ͼ
%%
figure(1);
plot(T_give(:,1) , T_give(:,2)-(T(end , : )-Tk)')  ;
xlabel('t/s');
ylabel('delta_T��/');
legend('��Ϻ�����ԭ�������');

figure(2);
plot(1000 * ( 0 : h : sum(d)) ,T(:,end)-Tk);
xlabel('x /mm') ;
ylabel('T��/');
legend('��βʱ���¶�����ȷֲ�');

figure(3);
plot(T_give(:,1) ,T(end,:)-Tk,'.',T_give(:,1) ,T_give(:,2),'r');
xlabel('t/s');
ylabel('T/��');
title('Ƥ������¶���ʱ��ֲ�');
legend('ģ�������¶�','���������¶�����');

figure( 4 ) ;
plot(0:dt:T_sum,T_xls(:,1)',0:dt:T_sum,T_xls(:,2)',0:dt:T_sum,T_xls(:,3)',0:dt:T_sum,T_xls(:,4)',0:dt:T_sum,T_xls(:,5)')
legend( ' ��I�뻷�������� ' , ' ��I���II������ ' , ' ��II���III������'  ,' ��III���IV������ ' , ' ��IV��Ƥ��������' ) ;
xlabel('t/s') ;
ylabel( 'T��/') ;

figure(5) ;
mesh(0:dt:T_sum,1000*(0:h:sum(d)),(T-Tk));
ylabel('x/mm');
xlabel('t/s');
zlabel('T��/');