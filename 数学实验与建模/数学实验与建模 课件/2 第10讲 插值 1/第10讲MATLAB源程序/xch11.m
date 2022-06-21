x=linspace(-6,6,100);
y=1./(x.^2+1);
x1=linspace(-6,6,5);
y1=1./(x1.^2+1);
plot(x,y,x1,y1,x1,y1,'o','LineWidth',1.5),
gtext('n=4'),
