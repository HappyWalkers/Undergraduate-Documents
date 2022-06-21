clear
clc

load('a','a');
load('flight_dis','flight_dis');
load('lamda_line','lamda_line');
rou_len=442.3+74.6+21.8+11.2+1.8;%图上路线总长度，单位km
hos_d=[1302,239];%图中坐标
D=max(flight_dis);%航程最大的无人机航程
hua=zeros(2,2000);%存储坐标，画出路线
k=1;%计数

%% 用点代表长度
m=size(a,1);
n=size(a,2);
count=0;%地图上总点数
for i=1:m
    for j=1:n
        if a(i,j)==0
            count=count+1;
        end
    end
end
lamda=rou_len/count;%每个点代表的长度，单位：km/点
count_fli=D/lamda;%无人机航程代表的点数

%% 先从医院飞上公路
for i=hos_d(1):-1:hos_d(1)-50
    if a(hos_d(2),i)==0
        qi=[i,hos_d(2)];
    end
end

%% 向下飞
d_cal=0;%计算已经飞过的点数
d_dis=0;%往返共经过点数
down=[0,0];%无人机往左飞时到达的最下端
for i=qi(1):-1:qi(1)-300
    for j=qi(2):qi(2)+200
        flag=0;
        if a(j,i)==0%矩阵中遇到黑点
            d_cal=d_cal+1;
            d_dis=dis(hos_d,qi)*lamda_line/lamda+d_cal+3*dis([i,j],hos_d)*lamda_line/lamda;
            hua(1,k)=i;
            hua(2,k)=j;
            k=k+1;
            if d_dis>=count_fli
                down=[i,j];
                flag=1;break;
            end
        end
    end
    if flag==1
        break;
    end
end

%% 向上飞
u_cal=0;%计算已经飞过的点数
u_dis=0;%往返共经过点数
up=[0,0];%无人机往左飞时到达的最左端
for i=qi(1):-1:qi(1)-50
    for j=qi(2):-1:qi(2)-140
        flag=0;
        if a(j,i)==0%矩阵中遇到黑点
            u_cal=u_cal+1;
            u_dis=dis(hos_d,qi)*lamda_line/lamda+u_cal+dis([i,j],hos_d)*lamda_line/lamda;
            hua(1,k)=i;
            hua(2,k)=j;
            k=k+1;
        end
    end
    if flag==1
        break;
    end
end
for i=qi(1)-40:-1:qi(1)-60
    for j=qi(2)-140:-1:qi(2)-230
        flag=0;
        if i==1237 && j==30%到达另一医院
            up=[i,j];
            flag=1;break;
        end
        if a(j,i)==0%矩阵中遇到黑点
            u_cal=u_cal+1;
            u_dis=dis(hos_d,qi)*lamda_line/lamda+u_cal+dis([i,j],hos_d)*lamda_line/lamda;
            hua(1,k)=i;
            hua(2,k)=j;
            k=k+1;
            if u_dis>=count_fli%最大距离
                up=[i,j];
                flag=1;break;
            end
        end
    end
    if flag==1
        break;
    end
end
%% 往右飞
r_cal=0;%计算已经飞过的点数
r_dis=0;%往返共经过点数
right=[0,0];%无人机往左飞时到达的最右端
for i=qi(1)-10:qi(1)+300
    for j=qi(2)-100:qi(2)+100
        flag=0;
        if a(j,i)==0%矩阵中遇到黑点
            r_cal=r_cal+1;
            r_dis=dis(hos_d,qi)*lamda_line/lamda+r_cal+dis([i,j],hos_d)*lamda_line/lamda;
            hua(1,k)=i;
            hua(2,k)=j;
            k=k+1;
            if r_dis>=count_fli
                right=[i,j];
                flag=1;break;
            end
        end
    end
    if flag==1
        break;
    end
end

%% plot
imshow(a);
text(hua(1,:),hua(2,:),'*','color','b');
text(hos_d(1),hos_d(2),'o','color','r');
text(qi(1),qi(2),'o','color','r');
text(down(1),down(2),'o','color','r');
text(up(1),up(2),'o','color','r');
text(right(1),right(2),'o','color','r');
save('hua_down','hua');