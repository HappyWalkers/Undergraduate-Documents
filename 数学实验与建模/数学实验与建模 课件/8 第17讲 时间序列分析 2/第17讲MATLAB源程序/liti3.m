
r1=diff(r);        %残差的一阶差分
r11=[0 r1];        %补数列差分后的项为0
plot(t,r11,'o');   %一阶差分散点图
r2=diff(r1);       %二阶差分
r21=[0 0 r2];      %补数列差分后的项为0
plot(t,r21,'o');   %二阶差分散点图

