syms t k; syms a positive
f1=t; f2=a-t;
Fs=int(f1*sin(k*pi*t/a),t,0,a/2)+int(f2*sin(k*pi*t/a),t,a/2,a);
simple(Fs)
