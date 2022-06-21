syms t y; u=sin(t); uu=3*diff(u)+3*u

y=dsolve('D5y+5*D4y+12*D3y+16*D2y+12*Dy+4*y=3*cos(t)+3*sin(t)',...
    'y(0)=0','Dy(0)=0','D2y(0)=0','D3y(0)=0','D4y(0)=0')