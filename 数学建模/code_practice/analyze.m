clear
close all
clc

v_c=90000;%inch
v_m=3858;
sum_now=411;%��
xi=floor( v_c/v_m);%ÿ�������˻�����ҩ

x=1:floor(411/xi);
y=sum_now-xi*x;
plot(x,y);
title({'relationship between the number of UAV and','the remaining days of drug availability'});
xlabel('number of UAV');
ylabel('The remaining days of drug availability');
