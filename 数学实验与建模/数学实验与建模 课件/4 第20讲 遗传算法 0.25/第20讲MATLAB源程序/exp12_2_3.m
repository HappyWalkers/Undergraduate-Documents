opt_minmax=1;     %Ŀ���Ż����ͣ�1��󻯡�-1��С��
sub=-1;            %����ȡֵ����
up=2.5;            %����ȡֵ����
delt=(up-sub)/5;
yita=0.99;
trace=[];          %ģ���˻�������ܸ�����
k_total=3000;      %�����ܴ���
tx=sub:.01:up;
y=fun_sigv(tx);
T=max(y)-min(y);   %ģ���¶ȳ�ʼ��
plot(tx,y)
xlabel('x')
ylabel('y')
title('һԪ�����Ż����')
hold on
x0=sub+(up-sub)*rand;
f0=fun_sigv(x0);   %���������ʼ��
k=0;
 plot(x0,f0,'ro','linewidth',2)  %�ں���ͼ���ϱ����ʼ��λ��
while k<k_total
   x1=x0+(2*rand-1)*delt;
   x1=min(x1,up);
   x1=max(x1,sub);                        %�ڵ�ǰ�㸽�����������һ��������λ�ã�����֤��������������
   f1=fun_sigv(x1);
   if opt_minmax*f1>opt_minmax*f0         %���������ڵ�ǰ�㣬���ܵ������������Ϊ��ǰ��
       x0=x1;
       f0=f1;
   elseif rand<exp(opt_minmax*(f1-f0)/T)   %���������ڵ�ǰ�㣬��boltzmann���ʽ��ܵ������������Ϊ��ǰ��
        x0=x1;
        f0=f1;
   end
   T=yita*T;                               %�Ի����ٶ�˥���¶�T
    k=k+1;
    trace=[trace;f0];                      %����ģ���˻�ĵ����Ż�����
    [x0,f0]
end
plot(x0,f0,'r*','linewidth',2)
figure
plot(trace(:),'r-*')
hold on
xlabel('��������')
ylabel('Ŀ�꺯���Ż����')
title('һԪ�����Ż�����')
