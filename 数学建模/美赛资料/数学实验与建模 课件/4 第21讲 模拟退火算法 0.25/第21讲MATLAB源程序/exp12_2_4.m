clc
clear all
opt_minmax=1;     %Ŀ���Ż����ͣ�1��󻯡�-1��С��
sub=-10;           %����ȡֵ����
up=10;            %����ȡֵ����
delt=(up-sub)/5;
yita=0.99;
trace=[];          %ģ���˻�������ܸ�����
k_total=3000;      %�����ܴ���
[tx,ty]=meshgrid(sub:.1:up);
tz=fun_mutv(tx,ty);
T=max(max(tz))-min(min(tz));   %ģ���¶ȳ�ʼ��
mesh(tx,ty,tz)
xlabel('x')
ylabel('y')
zlabel('z')
title('��Ԫ�����Ż����')
hold on
x0=[sub+(up-sub)*rand,sub+(up-sub)*rand];
f0=fun_mutv(x0(1),x0(2));           %���������ʼ��
k=0;
plot3(x0(1),x0(2),f0,'ko','linewidth',2)  %�ں���ͼ���ϱ����ʼ��λ��
while k<k_total
   x1=[x0(1)+(2*rand-1)*delt,x0(2)+(2*rand-1)*delt];
   x1=[min(x1(1),up),min(x1(2),up)];
   x1=[max(x1(1),sub),max(x1(2),sub)];       %�ڵ�ǰ�㸽�����������һ��������λ�ã�����֤��������������
   f1=fun_mutv(x1(1),x1(2));
   if opt_minmax*f1>opt_minmax*f0         %���������ڵ�ǰ�㣬���ܵ������������Ϊ��ǰ��
       x0=x1;
       f0=f1;
   elseif rand<exp(opt_minmax*(f1-f0)/T)   %���������ڵ�ǰ�㣬��boltzmann���ʽ��ܵ������������Ϊ��ǰ��
        x0=x1;
        f0=f1;
   end
   T=yita*T;                             %�Ի����ٶ�˥���¶�T
    k=k+1;
    trace=[trace;f0];                      %����ģ���˻�ĵ����Ż�����
    [x0,f0]
end
plot3(x0(1),x0(2),f0,'k*','linewidth',2)
figure
plot(trace(:),'r-*')
hold on
xlabel('��������')
ylabel('Ŀ�꺯���Ż����')
title('��Ԫ�����Ż�����')
