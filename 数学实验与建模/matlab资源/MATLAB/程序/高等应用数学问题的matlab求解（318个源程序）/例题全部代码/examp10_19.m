syms t; f=(1-t^2)*exp(-t^2/2)/sqrt(2*pi);
ezplot(f,-4,4), hold on;  % 绘制基小波，并保护坐标系不被刷新
ezplot(subs(f,t,t-1),-4,4); ezplot(subs(f,t,t+1),-4,4)  % 小波平移
figure; ezplot(f,-4,4), hold on;
ezplot(subs(f,t,t/2),-4,4); ezplot(subs(f,t,2*t),-4,4)  % 小波缩放

