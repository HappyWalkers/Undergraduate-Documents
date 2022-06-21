%Gauss-Seidel迭代程序
function [x,sp]=gausei(a,b,n,x1)
%误差
e=ones(n,1);
%迭代的解向量
x2=zeros(n,1);
%迭代的次数
k=0;
%当误差没有满足要求时继续迭代
while norm(e,2)>1e-6
   %每隔5步显示迭代结果
   if (rem(k,5)==0)
      str=sprintf('X%d= %g %g %g %g\n',k,x1);
      disp(str)
   end
   k=k+1;
   %计算x2（i）
   for i=1:n
      s1=0;
      s2=0;
      if i-1>0
         for j=1:i-1
            s1=s1+a(i,j)*x2(j);
         end
      end
      for j=i+1:n
         s2=s2+a(i,j)*x1(j);
      end
      
      x2(i)=(b(i)-s1-s2)/a(i,i);
   end
   %计算误差向量
   e=x2-x1;
   %把x2作为新的迭代初值
   x1=x2;
end
%返回迭代步数
sp=k;
%返回迭代值
x=x2;<i