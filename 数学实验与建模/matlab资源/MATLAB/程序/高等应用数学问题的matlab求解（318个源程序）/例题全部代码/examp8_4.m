x0=0:pi/30:pi; y0=sin(x0); I=quadspln(x0,y0,0,pi)

x0=0:pi/10:pi; y0=sin(x0); I1=trapz(x0,y0)

I=quadspln(x0,y0,0,pi)

x0=[0,0.4,1 2,pi]; y0=sin(x0);  % ����������
plot(x0,y0,x0,y0,'o')   % ���Ƴ���������������ͼ 8-3a ��ʾ��
I=quadspln(x0,y0,0,pi)  % ��Լ�� 1% �������Ӧ��˵���൱��ȷ��

I1=trapz(x0,y0)   % �� trapz() �������ó��ܴ�������� (7.9%)

x=[0:0.01:pi,pi]; y0a=sin(x); y=interp1(x0,y0,x,'spline');
plot(x0,y0,x,y,':',x,y0a,x0,y0,'o')