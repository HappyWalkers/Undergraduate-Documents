f=inline('2/sqrt(pi)*exp(-x.^2)','x');

f=inline('2/sqrt(pi)*exp(-x.^2)','x');
      y=quad(f,0,1.5)    % �� inline �������屻������
      
      y=quad('c3ffun',0,1.5)  % �� m �������屻������
      
      syms x, y0=vpa(int(2/sqrt(pi)*exp(-x^2),0,1.5),60)
       y=quad(f,0,1.5,1e-20)    % ���ø߾��ȣ����÷���ʧЧ
       