subplot(5,4,1), [a,y,x]=wavefun('db1'); plot(x,y), % ͬ���������� db С��
subplot(5,4,9), [a,y,x]=wavefun('sym2'); plot(x,y), % ͬ���������� sym С��
subplot(5,4,13), [a,y,x]=wavefun('coif2'); plot(x,y)
subplot(5,4,15), [y,x]=wavefun('gaus2'); plot(x,y)
subplot(5,4,17), [a,y,b,c,x]=wavefun('bior1.3'); plot(x,y)  % ������
