% Q2 .m
clear ;
close all ;
clc ;
%% �����趨
pho = [300;862;74.2;1.18] ;%�ܶ�
c = [1377;2100;1726;1005] ;%������
lamda = [0.082;0.37;0.045;0.028] ;%�ȵ���
a=lamda./( pho.* c ) ;
TT=273.15;
T_in=37;
T_out=65;
T_s=48.08;
h1 =117.41;%��һ��������Ľ��
h5 = 8.36 ;
N=3600;%time
h=0.05*10^-3;%d e l t a x%��λ��Ϊ��
k=1;%d e l t a time
r=k/h ^ 2 ;
%% Ѱ�Ҳ������������С���I I
D2_min=1;%����0.6�𡣡����������������������������������������������������������ν.����
D2_max=25;
D2_delta =2;
D2=D2_min : D2_delta : D2_max ;
flags=zeros ( 4 , length (D2) ) ;%flags����һ����񣬴洢�˸��������Ӧ�Ĺؼ�����
flags ( 1 , : )=D2 ;
for ii =1: length (D2)%ÿ����ȶ�������һ����һ�飬�ҳ�����������44��47������С���
d2=D2_min+( ii-1)* D2_delta ;%�����ı�����λ,mm
d = [ 0.6;d2;3.6;5.5 ] * 10 ^ -3 ;%��λ��Ϊ��
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
T ( : , 1 ) =(T_in+TT) * ones ( I +1 ,1) ;%һ��ʼ�����·���������
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
%% ����Ƿ������Ŀ����������
T_skin=T( end , : )-TT;
count =0;%����44�ȵ�ʱ��
flag=false ;
for j =1: length ( T_skin )
if T_skin ( j ) >44
count=count +1;
end
end
if (max( T_skin ) >47) || ( count >300)
flag=true ;%flag=true˵�������������ˣ�Ϊɶ���ø�min���������������С�ĺ���ء�������
end
flags ( 2 ,ii )=flag ;%����ֹؼ����ݡ���
flags(3,ii )=count ;
flags(4,ii )=max( T_skin ) ;
%%
% tc=281;
% figure( 1 ) ;
% hold on ;
% plot ( 0 : 1 : 3600 , T_skin ) ;
% plot (N-tc , T_skin (N+1-tc ) , 'ro' ) ;
% plot ( [0 1.1*N] , [T_skin(N+1-tc ) T_skin(N+1-tc ) ],'--r ' ) ;
% plot ( [ N-tc N-tc ] , [ 36 T_skin(N+1-tc ) ],'--k ' ) ;
% plot ( [N N] , [ 36 T_skin( end ) ],'--k ' ) ;
% xlabel ( 't/s  ') ;
% ylabel ( 'T��/ ' ) ;
% legend ( ' d2_{min}=17.6�����µ�����¶�mm' ) ;
end
%% ��ͼ����
display(flags ) ;
figure ( 1 ) ;
plot (D2 , flags ( 3 , : ) ) ;
xlabel ( 'd2/mm' ) ;
ylabel ( 't / s ' ) ;
legend ( '����44�� ʱ�����2���ȵĹ�ϵ ' ) ;
figure ( 2 ) ;
plot (D2 , flags ( 4 , : ) ) ;
xlabel ( 'd2/mm' ) ;
ylabel ( 'Tmax��/ ' ) ;
legend ( '����¶����2���ȵĹ�ϵ' ) ;