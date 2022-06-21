x1=[0:pi/30:pi]'; y=[sin(x1) cos(x1) sin(x1/2)];
x=[x1 x1 x1]; S=sum((2*y(1:end-1,:)+diff(y)).*diff(x))/2

S1=trapz(x1,y)   % 得出和上述完全一致的结果
