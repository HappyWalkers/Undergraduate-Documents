syms x; y=sin(x)/(x^2+4*x+3); y1=diff(y);   % �Ժ�����
y0=int(y1); latex(y0)    % �Ե�������Ӧ�õó�ԭ����

y4=diff(y,4); y0=int(int(int(int(y4))));
latex(simple(y0))