x=0:0.002:2*pi; y=sin(x.^2); r=0.1*randn(size(x));
y1=y+r; subplot(211); plot(x,y1)   % ����ԭʼ�ź�
[cA,cD]=dwt(y1,'db4');             % ��ɢС���任
subplot(223), plot(cA); subplot(224), plot(cD)  % ���ƽ��ƺ�ϸ���ź�

y2=idwt(cA,cD,'db4'); norm(y1-y2)  % ���鷴�任���źŵĻ�ԭ�̶�