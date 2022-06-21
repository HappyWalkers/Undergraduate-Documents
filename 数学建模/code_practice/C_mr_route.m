clear
clc

load('a','a');
load('flight_dis','flight_dis');
load('lamda_line','lamda_line');
rou_len=442.3+74.6+21.8+11.2+1.8;%ͼ��·���ܳ��ȣ���λkm
hos_mr=[1237,30];
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

%% ��ҽԺ�ɵ���·
for i=hos_mr(1):hos_mr(1)+10
    if a(hos_mr(2),i)==0
        qi=[i,hos_mr(2)];
    end
end

%% ���Ź�·���ҷ�
r_cal=0;%�����Ѿ��ɹ��ĵ���
r_dis=0;%��������������
right=[0,0];%���˻������ʱ��������Ҷ�
for i=qi(1)-10:qi(1)+100
    for j=qi(2)-10:qi(2)+50
        flag=0;
        if a(j,i)==0%�����������ڵ�
            r_cal=r_cal+1;
            r_dis=dis(hos_mr,qi)*lamda_line/lamda+r_cal+dis([i,j],hos_mr)*lamda_line/lamda;
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
text(hos_mr(1),hos_mr(2),'o','color','r');
text(qi(1),qi(2),'o','color','r');
text(right(2),right(1),'o','color','r');
save('hua_mr','hua');