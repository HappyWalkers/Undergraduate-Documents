%顺序gauss消去法，gauss函数
function [A,u]=gauss(a,n)
for k=1:n-1
   %消去过程
   for i=k+1:n
      for  j=k+1:n+1
         %如果a(k,k)=0,则不能消去
         if abs(a(k,k))>1e-6
            %计算第k步的增广矩阵
            a(i,j)=a(i,j)-a(i,k)/a(k,k)*a(k,j);
         else
            %a(k,k)=0,顺序gauss消去失败
            disp('顺序gauss消去失败');
            pause;
            exit;
         end
      end
   end
end
%回代过程
x(n)=a(n,n+1)/a(n,n);
for i=n-1:-1:1
   s=0;
   for j=i+1:n
      s=s+a(i,j)*x(j);
   end
   x(i)=(a(i,n+1)-s)/a(i,i);
end
%返回gauss消去后的增广矩阵
A=triu(a);
%返回方程组的解
u=x;<i