x=0:0.002:2*pi; y=sin(x.^2); r=0.1*randn(size(x));
y1=y+r; subplot(211); plot(x,y1)   % 绘制原始信号
[cA,cD]=dwt(y1,'db4');             % 离散小波变换
subplot(223), plot(cA); subplot(224), plot(cD)  % 绘制近似和细节信号

y2=idwt(cA,cD,'db4'); norm(y1-y2)  % 检验反变换对信号的还原程度