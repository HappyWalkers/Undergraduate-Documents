syms x; f=abs(x)/x;  % ���巽���ź�
xx=[-pi:pi/200:pi]; xx=xx(xx~=0); xx=sort([xx,-eps,eps]); % �޳����
yy=subs(f,x,xx); plot(xx,yy), hold on  % ���Ƴ�����ֵ����������ϵ
for n=2:20
    [a,b,f1]=fseries(f,x,n), y1=subs(f1,x,xx); plot(xx,y1)
end
% ������ MATLAB 6.1, 6.5 �� 7.0 �������� ��6.5.1������

[a,b,f1]=fseries(f,x,14); latex(f1)