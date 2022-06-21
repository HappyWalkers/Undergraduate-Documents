%列主元gauss消去函数
function [A,u]=gauss(a,n)
%消去过程
for k=1:n-1
   %选主元
   c=0;
   for q=k:n
      if abs(a(q,k))>c
         c=a(q,k);
         l=q;
      end
   end
   %如果主元为0，则矩阵A不可逆
   if abs(c)<1e-10
      disp('error');
      pause;
      exit;
   end
   %如果l不等于k，则交换第l行和第k行
   if l~=k 
      for q=k:n+1
         temp=a(k,q);
         a(k,q)=a(l,q);
         a(l,q)=temp;
      end
   end
   %计算第k步的元素值
   for i=k+1:n
      for  j=k+1:n+1
         a(i,j)=a(i,j)-a(i,k)/a(k,k)*a(k,j);
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
%返回列主元gauss消去后的增广矩阵
A=triu(a);
%返回方程组的解
u=x;<i