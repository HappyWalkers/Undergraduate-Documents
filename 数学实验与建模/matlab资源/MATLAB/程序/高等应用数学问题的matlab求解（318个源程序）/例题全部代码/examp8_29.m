t=0:0.01:5; x=t.*exp(-4*t).*sin(3*t); y=t.*exp(-4*t).*cos(3*t);
N=150; c1=xcorr(x,N); x1=[-N:N]; stem(x1,c1)  % ʵ�ʻ�ͼ��ѡ�ø�ϡ��
figure; c1=xcorr(x,y,N); x1=[-N:N]; stem(x1,c1)