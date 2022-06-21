clear all
close all
clc

hours=1:12;
temps=[5 8 9 15 25 29 31 30 22 25 27 24];
h=1:0.1:12;
t=interp1(hours,temps,h,'spline');  
plot(hours,temps,'+',h,t,hours,temps,'r:')    
xlabel('Hour'),ylabel('Degrees Celsius')
