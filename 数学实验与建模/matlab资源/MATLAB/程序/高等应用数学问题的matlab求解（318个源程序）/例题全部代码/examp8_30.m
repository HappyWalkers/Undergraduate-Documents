h=0.01; t=0:h:1; x=12*sin(2*pi*t+pi/4)+5*cos(2*pi*4*t); X=fft(x);
f=t/h; plot(f(1:floor(length(f)/2)),abs(X(1:floor(length(f)/2))))

ix=real(ifft(X)); plot(t,x,t,ix,':'); norm(x-ix)
