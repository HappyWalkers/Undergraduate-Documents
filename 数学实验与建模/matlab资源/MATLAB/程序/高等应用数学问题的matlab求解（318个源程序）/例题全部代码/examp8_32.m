b=1.2296e-6*conv([1 4 6 4 1],[1 3 3 1]); a=conv([1,-0.7265],...
    conv([1,-1.488,0.5644],conv([1,-1.595,0.6769],[1,-1.78,0.8713])));
x=0:0.002:2; y=exp(-x).*sin(5*x); r=0.05*randn(size(x)); y1=y+r;
[h,w]=freqz(b,a,100); plot(w,abs(h))    % 放大倍数绘制
figure; y2=filter(b,a,y1);  plot(x,y1,x,y2)   % 滤波效果
