clear all
close all
clc

% u = dsolve('D1u=1+u^2','y')

% y = dsolve('D2y=0')

% y = dsolve('D2y + 4*Dy + 29*y=0','y(0)=0','Dy(0)=15')

% [x,y,z]=dsolve('Dx=2*x-3*y+3*z',...
%                'Dy=4*x-5*y+3*z',...
%                'Dz=4*x-4*y+2*z', 't');
% x=simple(x) % ½«x»¯¼ò
% y=simple(y)
% z=simple(z)

x = dsolve('D2x-Dx*(1-x^2) - x = 0','x(0)=2','Dx(0)=0')