function my=fun_mutv(x,y)
t1=zeros(size(x));
t2=t1;
for i=1:5
    t1=t1+i*cos((i+1)*x+i);
    t2=t2+i*cos((i+1)*y+i);
end
my=t1.*t2;