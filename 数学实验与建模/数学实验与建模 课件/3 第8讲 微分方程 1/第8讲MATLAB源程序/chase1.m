clear
close all
clc

x=0:0.01:1;
y=-5*(1-x).^(4/5)/8+5*(1-x).^(6/5)/12+5/24;
plot(x,y,'*')