clear
clc

load('a','a');
load('flight_dis','flight_dis');
load('lamda_line','lamda_line');
rou_len=442.3+74.6+21.8+11.2+1.8;%ͼ��·���ܳ��ȣ���λkm
hos_d=[1302,239];%ͼ������
D=max(flight_dis);%�����������˻�����
hua=zeros(2,2000);%�洢���꣬����·��
k=1;%����

%% �õ������
m=size(a,1);
n=size(a,2);
count=0;%��ͼ���ܵ���
for i=1:m
    for j=1:n
        if a(i,j)==0
            count=count+1;
        end
    end
end
lamda=rou_len/count;%ÿ�������ĳ��ȣ���λ��km/��
count_fli=D/lamda;%���˻����̴���ĵ���

%% �ȴ�ҽԺ���Ϲ�·
for i=hos_d(1):-1:hos_d(1)-50
    if a(hos_d(2),i)==0
        qi=[i,hos_d(2)];
    end
end

%% ���·�
d_cal=0;%�����Ѿ��ɹ��ĵ���
d_dis=0;%��������������
down=[0,0];%���˻������ʱ��������¶�
for i=qi(1):-1:qi(1)-300
    for j=qi(2):qi(2)+200
        flag=0;
        if a(j,i)==0%�����������ڵ�
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

%% ���Ϸ�
u_cal=0;%�����Ѿ��ɹ��ĵ���
u_dis=0;%��������������
up=[0,0];%���˻������ʱ����������
for i=qi(1):-1:qi(1)-50
    for j=qi(2):-1:qi(2)-140
        flag=0;
        if a(j,i)==0%�����������ڵ�
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
        if i==1237 && j==30%������һҽԺ
            up=[i,j];
            flag=1;break;
        end
        if a(j,i)==0%�����������ڵ�
            u_cal=u_cal+1;
            u_dis=dis(hos_d,qi)*lamda_line/lamda+u_cal+dis([i,j],hos_d)*lamda_line/lamda;
            hua(1,k)=i;
            hua(2,k)=j;
            k=k+1;
            if u_dis>=count_fli%������
                up=[i,j];
                flag=1;break;
            end
        end
    end
    if flag==1
        break;
    end
end
%% ���ҷ�
r_cal=0;%�����Ѿ��ɹ��ĵ���
r_dis=0;%��������������
right=[0,0];%���˻������ʱ��������Ҷ�
for i=qi(1)-10:qi(1)+300
    for j=qi(2)-100:qi(2)+100
        flag=0;
        if a(j,i)==0%�����������ڵ�
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