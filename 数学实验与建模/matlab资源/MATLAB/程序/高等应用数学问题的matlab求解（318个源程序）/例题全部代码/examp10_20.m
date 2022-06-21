t=0:0.03:2*pi; y=sin(t.^2); plot(t,y)

a=1:32; Z=cwt(y,a,'mexh','plot');  % »æÖÆ¾ø¶ÔÖµÍ¼

surf(t,a,Z); shading flat; axis([0 2*pi,0,32,min(Z(:)) max(Z(:))])