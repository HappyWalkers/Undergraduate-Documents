f=inline('cos(15*x)','x');
tic, S=quadl(f,0,3*pi/2,1e-15), toc

S1=quad(f,0,3*pi/2)   % 采用默认精度

S1=quad(f,0,3*pi/2,1e-15)