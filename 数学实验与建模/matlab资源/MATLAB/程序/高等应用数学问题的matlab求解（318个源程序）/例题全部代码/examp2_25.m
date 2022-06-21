t=0:.2:2*pi; y=sin(t);  % 先生成绘图用数据
subplot(2,2,1), stairs(t,y)  % 分割窗口，在左上角绘制阶梯曲线
subplot(2,2,2), stem(t,y)  % 火柴杆曲线绘制
subplot(2,2,3), bar(t,y)  % 直方图绘制
subplot(2,2,4), semilogx(t,y)  % 横坐标为对数的曲线
