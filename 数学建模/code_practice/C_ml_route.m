clear
clc

load('a','a');
load('flight_dis','flight_dis');
load('lamda_line','lamda_line');
rou_len=442.3+74.6+21.8+11.2+1.8;%图上路线总长度，单位km
hos_ml=[1151,78];
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
for j=hos_ml(2):-1:1
    if a(j,hos_ml(1))==0
        qi=[hos_ml(1),j];
    end
end

%% 沿着公路向左飞
l_cal=0;%计算已经飞过的点数
l_dis=0;%往返共经过点数
left=[0,0];%无人机往左飞时到达的最左端
for i=qi(1):-1:1
    for j=qi(2)-50:qi(2)+50
        flag=0;
        if a(j,i)==0%矩阵中遇到黑点
            l_cal=l_cal+1;
            l_dis=dis(hos_ml,qi)*lamda_line/lamda+l_cal+dis([i,j],hos_ml)*lamda_line/lamda;
            hua(1,k)=i;
            hua(2,k)=j;
            k=k+1;
            if l_dis>=count_fli
                left=[j,i];
                flag=1;break;
            end
        end
    end
    if flag==1 
        break;
    end
end

%% 沿着公路向右飞
r_cal=0;%计算已经飞过的点数
r_dis=0;%往返共经过点数
right=[0,0];%无人机往左飞时到达的最右端
for i=qi(1):qi(1)+600
    for j=qi(2)-50:qi(2)+10
        flag=0;
        if i==1237 && j==30%到达另一医院
            right=[j,i];
            flag=1;break;
        end
        if a(j,i)==0%矩阵中遇到黑点
            r_cal=r_cal+1;
            r_dis=dis(hos_ml,qi)*lamda_line/lamda+r_cal+dis([i,j],hos_ml)*lamda_line/lamda;
            hua(1,k)=i;
            hua(2,k)=j;
            k=k+1;
            if r_dis>=count_fli
                right=[j,i];
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
text(hos_ml(1),hos_ml(2),'o','color','r');
text(qi(1),qi(2),'o','color','r');
text(left(2),left(1),'o','color','r');
text(right(2),right(1),'o','color','r');
save('hua_ml','hua');


