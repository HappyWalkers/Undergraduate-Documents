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

d2=0.1;
dmin=17;%�ڶ����ȷ�Χ
dmax=19;
D_enough=dmin:d2:dmax;%�ڶ�����������
D_select=100*ones(250,1);%���������ĵڶ�����ֵ
for m=1:length(D_enough)%�Եڶ����Ƚ���������ȡ������������Сֵ
    d_enough=dmin+(m-1)*d2;
    %% ����3������ɢ����
    T_sum=3600;%��ʱ��
    d=[0.6;d_enough;3.6;5.5]*10^-3;%���
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
    T_out=65;%����¶�
    T_end=48.08;%��̬ʱ���¶�
    T(:,1)=T_in+Tk;%0sʱ�����·���������
    
    h1=117.4000;
    h4=8.3653;
    
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
    
    %% �ҳ�������������С�ڶ����ȣ��¶Ȳ�����47?C���ҳ���44?C��ʱ�䲻����5���ӣ�
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