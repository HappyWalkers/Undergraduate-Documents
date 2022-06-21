clear ;
close all ;
clc ;
%% 参数设定
pho = [300;862;74.2;1.18] ;%密度
c = [1377;2100;1726;1005] ;%比热容
lamda = [0.082;0.37;0.045;0.028] ;%热导率
a=lamda./( pho.* c ) ;
TT=273.15;
T_in=37;
T_out=80;
T_s=48.08;
N=1800;%time %30min
h=0.05*10^-3;%d e l t a x
k=1;%d e l t a time
r=k/h ^ 2 ;
h1 =117.41;
h5 = 8.36 ;
D2_min=18.9;%怎么来的，伪代码直接省略啦？不合适吧。。。。。。。。。
D2_max= 19.3 ;
D2_delta =0.05;
D2=D2_min : D2_delta : D2_max ;
D4_min= 6.2 ;
D4_max= 6.4 ;
D4_delta =0.05;
D4=D4_min : D4_delta : D4_max ;
flags=zeros ( length (D2) , length (D4) ) ;
for ii =1: length (D2)%再来一遍第二题。。
for jj =1: length (D4)
d2=D2_min+( ii -1)* D2_delta ;
d4=D4_min+( jj -1)* D4_delta ;
% d2 =19.3;
% d4 =6.4;
d = [ 0.6 ; d2 ; 3.6 ; d4 ]*10^-3;
xmin =0;
xmax=sum( d ) ;
I=round ( ( xmax-xmin ) /h ) ;
A=zeros ( 1 , I ) ;
B=zeros ( 1 , I +1) ;
C=zeros ( 1 , I ) ;
N1=round ( d ( 1 ) /h ) ;
N2=round ( d ( 2 ) /h ) ;
N3=round ( d ( 3 ) /h ) ;
N4=round ( d ( 4 ) /h ) ;
for i =1:N1
A( i )=-a ( 1 ) * r ;
B( i )=2+2*r *a ( 1 ) ;
C( i )=-r *a ( 1 ) ;
end
for i=N1+1:N1+N2
A( i )=-a ( 2 ) * r ;
B( i )=2+2*r *a ( 2 ) ;
C( i )=-r *a ( 2 ) ;
end
for i=N1+N2+1:N1+N2+N3
A( i )=-a ( 3 ) * r ;
B( i )=2+2*r *a ( 3 ) ;
C( i )=-r *a ( 3 ) ;
end
for i=N1+N2+N3+1:N1+N2+N3+N4
A( i )=-a ( 4 ) * r ;
B( i )=2+2*r *a ( 4 ) ;
C( i )=-r *a ( 4 ) ;
end
T=zeros ( I +1,N+1) ;
T ( : , 1 ) =(T_in+TT) * ones ( I +1 ,1) ;%一开始整件衣服都是体温
AA=diag (B)+diag (A, 1 )+diag (C,-1) ;
AA( 1 , 1 )=lamda ( 1 ) /h+h1 ;
AA( 1 , 2 )=-lamda ( 1 ) /h ;
AA( I +1, I )=-lamda ( 4 ) /h ;
AA( I +1, I +1)=lamda ( 4 ) /h+h5 ;
AA(N1+1,N1)=-lamda ( 1 ) ;
AA(N1+1,N1+1)=lamda ( 1 )+lamda ( 2 ) ;
AA(N1+1,N1+2)=-lamda ( 2 ) ;
AA(N1+N2+1,N1+N2)=-lamda ( 2 ) ;
AA(N1+N2+1,N1+N2+1)=lamda ( 2 )+lamda ( 3 ) ;
AA(N1+N2+1,N1+N2+2)=-lamda ( 3 ) ;
AA(N1+N2+N3+1,N1+N2+N3)=-lamda ( 3 ) ;
AA(N1+N2+N3+1,N1+N2+N3+1)=lamda ( 3 )+lamda ( 4 ) ;
AA(N1+N2+N3+1,N1+N2+N3+2)=-lamda ( 4 ) ;
for n=1:k :N
D=zeros ( I +1 ,1) ;
D( 1 )=h1 *( T_out+TT) ;
D( I +1)=h5 *( T_in+TT) ;
for i = 2 : 1 :N1
D( i )=r *a ( 1 ) *T( i -1,n ) +(2-2* r *a ( 1 ) ) *T( i , n )+r *a ( 1 ) *T( i +1,n ) ;
end
for i=N1+ 1 : 1 :N1+N2
D( i )=r *a ( 2 ) *T( i -1,n ) +(2-2* r *a ( 2 ) ) *T( i , n )+r *a ( 2 ) *T( i +1,n ) ;
end
for i=N1+N2+ 1 : 1 :N1+N2+N3
D( i )=r *a ( 3 ) *T( i -1,n ) +(2-2* r *a ( 3 ) ) *T( i , n )+r *a ( 3 ) *T( i +1,n ) ;
end
for i=N1+N2+N3+ 1 : 1 :N1+N2+N3+N4
D( i )=r *a ( 4 ) *T( i -1,n ) +(2-2* r *a ( 4 ) ) *T( i , n )+r *a ( 4 ) *T( i +1,n ) ;
end
D(N1+1)=0;
D(N1+N2+1)=0;
D(N1+N2+N3+1)=0;
T ( : , n+1)=AA\D;
end
T_skin=T( end , : )-TT;
count =0;
flag=false ;
for j =1: length ( T_skin )
if T_skin ( j ) >44
count=count +1;
end
end
tc=count ;%tc没啥用啊。。。。。
if (max( T_skin ) >47) || ( count >300)
flag=true ;%不符合条件的flag=true
end
flags(ii,jj )=flag ;
end
end
display(flags ) ;
%% 绘图部分
figure(1);
plot(0:1:1800,T_skin);
hold on ;
plot ( [ 0 N] , [ T_skin(N-tc ) T_skin(N-tc ) ],'--r' ) ;
plot ( [ N-tc N-tc ] , [36 T_skin(N-tc ) ],'--k' ) ;
plot ( [N N] , [36 T_skin( end ) ],'--k' ) ;
xlabel ( ' t/s ' ) ;
ylabel ( 'T/℃' ) ;
legend ( ' ( d2_{min } , d4_{min }) =(19.3mm, 6 . 4mm)情况下的体表温度' ) ;