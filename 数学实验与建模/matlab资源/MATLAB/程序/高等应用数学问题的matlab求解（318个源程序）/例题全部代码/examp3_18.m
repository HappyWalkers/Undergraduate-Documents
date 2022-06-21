x0=-2*pi:0.01:2*pi; y0=sin(x0); syms x; y=sin(x);
      plot(x0,y0), axis([-2*pi,2*pi,-1.5,1.5]); hold on
      for n=[8:2:16]
         p=taylor(y,x,n), y1=subs(p,x,x0); line(x0,y1)
      end
      
      