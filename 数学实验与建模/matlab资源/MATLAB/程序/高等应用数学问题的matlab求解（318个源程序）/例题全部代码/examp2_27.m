t=0:.1:2*pi;   % 构造 t 向量，注意下面的点运算
x=t.^3.*sin(3*t).*exp(-t); y=t.^3.*cos(3*t).*exp(-t); z=t.^2;
plot3(x,y,z), grid  % 三维曲线绘制

stem3(x,y,z); hold on; plot3(x,y,z), grid
