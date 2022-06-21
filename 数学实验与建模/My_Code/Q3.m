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
d2min=18;%�ڶ����ȷ�Χ
d2max=20;
D2_enough=d2min:d2:d2max;%�ڶ�����������

d4=0.1;
d4min=6.0;%���Ĳ��ȷ�Χ
d4max=6.4;
D4_enough=d4min:d4:d4max;%���Ĳ���������

D2_select=100*ones(250,100);%���������ĵڶ�����ֵ���������ʾ�ڶ��㣬�������ʾ���Ĳ�
D4_select=100*ones(250,100);%���������ĵ��Ĳ���ֵ���������ʾ�ڶ��㣬�������ʾ���Ĳ�
for ii=1:length(D2_enough)%�Եڶ����Ƚ���������ȡ������������Сֵ
    for jj=1:length(D4_enough)
        d2_enough=d2min+(ii-1)*d2;%Ϊ�ڶ����ȸ�ֵ
        d4_enough=d4min+(jj-1)*d4;%Ϊ���Ĳ��ȸ�ֵ
        %% ����3������ɢ����
        T_sum=1800;%��ʱ��
        d=[0.6;d2_enough;3.6;d4_enough]*10^-3;%���
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
        T_out=80;%����¶�
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
            D2_select(ii,jj)=d2_enough;
            D4_select(ii,jj)=d4_enough;
        end
    end
end
[d2_get,poisition]=min(D2_select,[],'all','linear');
disp(d2_get);
disp(D4_select(poisition));