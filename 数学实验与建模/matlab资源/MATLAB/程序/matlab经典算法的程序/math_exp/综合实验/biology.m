x(1)=0.1;
for i=1:60
   x(i+1)=4*x(i)*(1-x(i));
   plot(i,x(i),'*')
   hold on
end
y(1)=0.1000001;
for i=1:60
   y(i+1)=4*y(i)*(1-y(i));
   plot(i,y(i),'+')
   hold on
end
z(1)=0.10000001;
for i=1:60
   z(i+1)=4*z(i)*(1-z(i));
   plot(i,z(i),'r+')
   hold on
end

<i