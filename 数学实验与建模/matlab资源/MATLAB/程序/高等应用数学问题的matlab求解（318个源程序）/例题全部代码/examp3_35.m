fh=inline('sqrt(1-x.^2/2)','x');  % �ڻ�������
fl=inline('-sqrt(1-x.^2/2)','x'); % �ڻ�������
f=inline('exp(-x.^2/2).*sin(x.^2+y)','y','x');  % ����˳��ı�������
y=quad2dggen(f,fl,fh,-1/2,1,eps),

syms x y   % ���ڿ��ǽ����ⷽ��
i1=int(exp(-x^2/2)*sin(x^2+y),y,-sqrt(1-x^2/2),sqrt(1-x^2/2));
int(i1,x,-1/2,1) % ��ȡ������ʱ�ó�������Ϣ
vpa(ans)

vpa(ans,70)   % �����ڽ����⣬��������߾�����ֵ��

fh=inline('sqrt(1-y.^2)','y');  % �ڻ�������
fl=inline('-sqrt(1-y.^2)','y'); % �ڻ�������
f=inline('exp(-x.^2/2).*sin(x.^2+y)','x','y');  % ����˳��ı�������
I=quad2dggen(f,fl,fh,-1,1,eps),
