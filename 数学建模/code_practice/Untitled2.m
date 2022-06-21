clear,clc
a=input('Please input a number:');
f=input('Please input the accuracy:');
b=floor(a);
c=dec2bin(b);
d=a-b;
w=d*2;
if(d==0)
    disp(c);
else
    for i=1:f
        if(w==1)
            h(i)=1;
            break
        else if(floor(w)==1);
            h(i)=1;
            w=w-1;
            else
              h(i)=0;  
            end
        
        end
    end
end
    A=num2str(h);
    A(isspace(A))=[];
    z=strcat(c,'.',A);
    disp(z)