ezplot('exp(-3*t)*sin(4*t+2)+4*exp(-0.5*t)*cos(2*t)-0.5',[0 5])
hold on, line([0,5],[0,0])% Õ¨ ±ªÊ÷∆∫·÷·

syms x; t=3.5203; vpa(exp(-3*t)*sin(4*t+2)+4*exp(-0.5*t)*cos(2*t)-0.5)
