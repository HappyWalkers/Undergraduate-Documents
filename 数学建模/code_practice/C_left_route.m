clear
clc

load('a','a');
load('flight_dis','flight_dis');
load('lamda_line','lamda_line');
rou_len=442.3+74.6+21.8+11.2+1.8;%ͼ��·���ܳ��ȣ���λkm
hos_l=[598,45];%�����ҽԺ����
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
for i=hos_l(1)-10 : hos_l(1)+10
    for j=hos_l(2): hos_l(2)+40
        flag=0;
        if a(j,i)==0%�����
            qi=[i,j];%���
            hua(1,k)=i;
            hua(2,k)=j;
            k=k+1;
            flag=1;break;
        end
    end
    if flag==1
        break;
    end
end

%% ���Ź�·�����
l_cal=0;%�����Ѿ��ɹ��ĵ���
l_dis=0;%��������������
left=[0,0];%���˻������ʱ����������
for i=qi(1):-1:1
    for j=qi(2)-50:qi(2)+50
        flag=0;
        if a(j,i)==0%�����������ڵ�
            l_cal=l_cal+1;
            l_dis=lamda_line*dis(hos_l,qi)/lamda+l_cal+lamda_line*dis([i,j],hos_l)/lamda;
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

%% ���Ź�·���ҷ�
r_cal=0;%�����Ѿ��ɹ��ĵ���
r_dis=0;%��������������
right=[0,0];%���˻������ʱ��������Ҷ�
for i=qi(1):qi(1)+600
    for j=qi(2)-50:qi(2)+50
        flag=0;
        if a(j,i)==0%�����������ڵ�
            r_cal=r_cal+1;
            r_dis=lamda_line*dis(hos_l,qi)/lamda+r_cal+lamda_line*dis([i,j],hos_l)/lamda;
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
text(hos_l(1),hos_l(2),'o','color','r');
text(qi(1),qi(2),'o','color','r');
text(left(2),left(1),'o','color','r');
text(right(2),right(1),'o','color','r');
save('hua_left','hua');
            
        

