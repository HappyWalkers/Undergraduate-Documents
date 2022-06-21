function [ v, d, p ] = multi_driveway_with_crossroad_exit( nl,...
    nc,dt,fp,nt,chance,chance1)
% fp:车道入口处新进入车辆的概率向量（2,3,5 车道）——输入参数
% chance:交叉口处车辆行为的概率向量(5 车道右转,3车道右转）——输入参数
 %构造元胞矩阵
 B=ones(nc+1+nl/2,nl+3);
 %不可行车道
 B(nc/2+1,[1:nl/2 nl/2+4:nl+3])=1.2;   
 B(nc+2:nc+1+nl/2,[1:nl/2 nl/2+4:nl+3])=1.2;
 %初始化仿真元胞状态（1 为无车，0 为有车）
 bb1=B([1:nc/2 nc/2+2:nc+1],:);bb2=B(:,nl/2+3);bb3=B(:,nl/2+1);
 bb1(bb1~=0)=1;
 bb2(bb2~=0)=1;
 bb3(bb3~=0)=1;
 B([1:nc/2 nc/2+2:nc+1],:)=bb1;B(:,nl/2+3)=bb2;B(:,nl/2+1)=...
     bb3;B(1:nc+1,nl/2+1:nl/2+3)=1;
 B(1:nc/2,end)=0;B(nc/2+2:nc+1,1)=0;B(end,nl/2+3)=0;
 %显示初始交通流图
 figure();
 H=imshow(B,[]);
 set(gcf,'position',[241 132 560 420]) ;%241 132 560 420
 set(gcf,'doublebuffer','on'); %241
 title('cellular-automation to traffic modeling','color','b');
 %初始化化存储元胞上车辆状态的矩阵
 S(1:nc*2+2,nl/2-2) = 0;
 Q(1:nc*2+2,1:2) = 0;
 C=zeros(nc+1,3);
 %初始化换道频率、平均速度、车流密度相关变量
 ad = 0;
 av(1:nt) = 0;
 ap(1:nt) = 0;
 s = 1;flag= 0;flag1=0;%flag、flag1 用于标示小区出口的车是否为左转车辆
 flag2=0;
 for n = 1:nt
%六个路段的长度。
A=[
B(1:nc/2,nl/2 :-1:1);
B(nc/2+2:nc+1,1:nl/2);
B(1:nc/2,nl+3:-1:nl/2+4);
B(nc/2+2:nc+1,nl/2+4:nl+3);
B(nc+1+nl/2:-1:nc+2,nl/2+3)';
B(nc+2:1:nc+1+nl/2,nl/2+1)'
];
c=B(1:nc+1,nl/2+1:nl/2+3);
 %确定前 n-2 个车辆的状态
 S(:,:) = 0;
 S(A(:,1:end-2)==0&A(:,2:end-1)==1&A(:,3:end)==1)=2;%快速行驶的车
 S(A(:,1:end-2)==0&A(:,2:end-1)==0)=3;%停车的车
 S(A(:,1:end-2)==0&A(:,2:end-1)==1&A(:,3:end)==0)=1;%慢速行驶的车
 %确定最后两个元胞的状态
 Q(:,:)= 0;
 Q(A(:,end-1)==0&A(:,end)==0) = 3;
 Q(A(:,end-1)==0&A(:,end)==1) = 1;
 if c(3,1)==0
     if rand<chance1
         flag2=1;
         c(3,1)=1;
     end
 end   
 if A(1,end)==0
 Q(1,end)=1;
 end
 if A(4,end)==0
 Q(4,end)=1;
 end
 if A(6,end)==0
 Q(6,end)=1;
 end
 if rem(floor(n/50),2)==0 %此时左右向为绿灯
 if A(2,end)==0
 if c(nc/2+2:nc+1,1)==0
 Q(2,end)=3;
 else
     Q(2,end)=1;
 end 
 end
 if A(3,end)==0
 if c(1,3)==0
 Q(3,end)=3;
 else
 Q(3,end)=1;
 end
 end
 %按照既定规则行驶（5 车道右转）
 if A(5,end)==0
 if flag==0
 if rand<chance %路口车右转
 if c(nc/2+2:nc+1,:)==1
 Q(5,end)=1;  
 else
 Q(5,end)=3;
 end
 end
 else %第一辆车为左转车，需要等待                                  
 end
 end
 if c(1,2)==0
 if c(1,1)==1%3道口左转的思路：规避。
 C(1,2)=1;
 else
 C(1,2)=3;
 end
 if c(2,1)==0                
 C(1,2)=3;
 end
 end
 if c(1,3)==0
 if c(1,2)==1
 C(1,3)=1;
 else
 C(1,3)=3;
 end
 end
 if c(3,1)==0
 if c(3,2)==1
 C(3,1)=1;
 else
 C(3,1)=3;
 end
 end
 if c(3,2)==0
 if c(3,3)==1
 C(3,2)=1;
 else
 C(3,2)=3;
 end
 end
 if rem(n,20)==0&&c(3,2)==0%小区出来的车还遗留在路口，特殊处理先行
 if c(2,1)==1
 C(3,2)=5; %特殊的等待状态（小区出来的车）
 else
 C(3,2)=3;
 end
 end
 if c(2,1)==0
 if A(1:nc/2,1)==0
 C(2,1)=3;
 else
 C(2,1)=1;
 end
 end
 if c(1,1)==0
 if A(1,1)==0
 C(1,1) = 3;
 else
 C(1,1) = 1;
 end
 end
 if c(3,3)==0
 if A(nc*3/2+1:2*nc,1)==0
 C(3,3) = 3;
 else
 C(3,3) = 1;
 end
 end
 else %此时小区出入向为绿灯
 Q(2,end)=3;Q(3,end)=3;
 if c(3,2)==0
 if flag1==1
 if c(2,1)==1
 C(3,2)=5;flag1=0;
 else
 C(3,2)=3;
 end
 else
 if c(3,3)==1
 C(3,2)=1;
 else
 C(3,2)=3;
 end
 end
 end
 if c(2,1)==0
 if A(1:nc/2,1)==1&&c(1,1)==1
 C(2,1)=1;
 else
 C(2,1)=3;
 end
 end
 if A(5,end)==0
 if flag==0
 if rand<chance
 if c(nc/2+2:nc+1,:)==1
 Q(5,end)=1;
 else
 Q(5,end)=3;
 end
 else
 if c(nc/2+2:nc+1,1)==1&&c(nc/2+2:nc+1,2)==1
 Q(5,end)=5;flag=0;flag1=1; %小区的左转前进，用以区分右转车辆
 else
 Q(5,end)=3;flag=1;
 end
 end
 else
 if c(nc/2+2:nc+1,1)==1&&c(nc/2+2:nc+1,2)==1
 Q(5,end)=5;flag=0;flag1=1; %小区的左转前进，用以区分右转车辆
 else
 Q(5,end)=3;flag=1;
 end
 end
 end
 if c(1,2)==0
 if c(1,1)==1
 C(1,2)=1;
 else
 C(1,2)=3;
 end
 end
 if c(1,3)==0
 if c(1,2)==1
 C(1,3)=1;
 else
 C(1,3)=3;
 end
 end
 if c(3,1)==0
 if c(3,2)==1
 C(3,1)=1;
 else
 C(3,1)=3;
 end
 end
 if c(1,1)==0
 if A(1:nc/2,1)==0
 C(1,1) = 3;
 else
 C(1,1) = 1;
 end
 end
 if c(3,3)==0
 if A(nc*3/2+1:2*nc,1)==0
 C(3,3) = 3;
 else
 C(3,3) = 1;
 end
 end
 end
 %获得所有元胞上车辆的状态
 Acc = [ S Q ];
 %根据当前状态改变元胞位置
 %路口附近的车辆的行驶控制
 if C(3,2)==5
 c(2,1)=0;
 c(3,2)=1;
 flag=0;
 C(3,2)=0;
 elseif C(3,2)==1
 c(3,3)=0;
 c(3,2)=1;
 C(3,2)=0;
 end
 if C(2,1)==1
 A(1,1)=0;
 c(2,1)=1;
 C(2,1)=0;
 end
 if Acc(3,end)==1
 c(1,3)=0;
 A(3,end)=1;
 Acc(3,end)=0;
 end
 if Acc(2,end)==1
 c(3,1)=0;
 A(2,end)=1;
 Acc(2,end)=0;
 end
 if C(3,1)==1
 c(3,2)=0;
 c(3,1)=1;
 C(3,1)=0;
 end
 if C(1,3)==1
 c(1,2)=0;
 c(1,3)=1;
 C(1,3)=0;
 end
 if C(1,2)==1
 c(1,1)=0;
 c(1,2)=1;
 C(1,2)=0;
 end
 if C(1,1)==1
 A(1,1)=0;
 c(1,1)=1;
 C(1,1)=0;
 end
 if C(3,3)==1
 A(4,1)=0;
 c(3,3)=1;
 C(3,3)=0;
 end
 %慢速运行车辆向前走 1 格
 A( Acc(:,1:end)==1 )=1;
 A( [ zeros(nc*3,1) Acc(:,1:end-1)]==1 ) = 0;
 %高速运行车辆向前走 2 格
 A( Acc(:,1:end)==2) = 1;
 A( [ zeros(nc*3,2) Acc(:,1:end-2)]==2) = 0;
 if Acc(1,1)==1||Acc(1,1)==2
 A(1,1)=1;
 end
 if Acc(4,1)==1||Acc(4,1)==2
 A(4,1)=1;
 end
 if Acc(5,end)==5
 c(3,2)=0;flag=0;
 A(5,end)=1;
 elseif Acc(5,end)==1
 c(3,3)=0;
 A(5,end)=1;
 end
 if Acc(3,end)==1
 c(1,3)=0;
 A(3,end)=1;
 end
 if Acc(2,end)==1
 c(3,1)=0;
 A(2,end)=1;
 end
 if Acc(4,1)==1||Acc(4,1)==2
 A(4,1)=1;
 end
 if Acc(1,1)==1||Acc(1,1)==2
 A(1,1)=1;
 end
 %计算平均速度、换道频率、车流密度等参数
 %获得运行中的车辆数目 N
 matN = A<1;
 N = sum(sum(matN));
 %获得运行中的车辆速度之和 V
 E = S((S==1)|(S==2));
 V = sum(E);
 %计算此时刻的车流密度并保存
 ap(n) = N/( (nc*3)*(nl/2)+9 );
 %计算此时刻的平均速率并保存
 if(N~=0&&n>nl/2)
 av(s) = V/N;
 s = s+1;
 end
 %在车道入口处随机引入新的车辆
 A([2;3;5],1)=(round(fp.*rand(3,1))&A([2;3;5],1));
 A(A~=0)=1;
 if flag2==1
     A(6,1)=0;
     flag2=0;
 end
 %将新的车辆加入元胞矩阵中
 B(1,1:nl/2)=A(1:nc/2,end:-1:1);
 B(3,1:nl/2)=A(nc/2+1:nc,:);
 B(1,nl/2+4:nl+3)=A(nc+1:nc*3/2,end:-1:1);
 B(3,nl/2+4:nl+3)=A(nc*3/2+1:2*nc,:);
 B(nc+2:nc+1+nl/2,nl/2+3)=A(2*nc+1,end:-1:1)';
 B(nc+2:nc+1+nl/2,nl/2+1)=A(3*nc,:)';
 B(1:3,nl/2+1:nl/2+3)=c(:,:);
 %显示交通流图
 set(H,'CData',B);
%计算这个时间段每个时间点的指标（速度与车流量）。
 d = ad;
 p = mean(ap);
 v = sum(av)/s;
 disp([v,p])
%仿真步长
 pause(dt);
 end
end