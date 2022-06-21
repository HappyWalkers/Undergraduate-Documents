%dv_hop.m

% square_L: ����������ı߳�����λ��m 
% comm_r: ͨ�Ű뾶����λ��m 
% node_n(1): ����ڵ�ĸ��� 
% anchor_n: �ű�ڵ���� 
% unknown_n: δ֪�ڵ���� 
% xy:�洢������ÿ��������� 
% adjacency_m: �ڽӾ��� 
% hop: ��������
clear
close all
clc

square_L = 200;
comm_r = 20;
anchor_n = 0; %ê�ڵ�
unknown_n = 0; %δ֪�ڵ�
xy = load('/Users/mine/study/�γ�/���߶�λ/��������λ����ʵ��2020/ʵ�����ο�����/net1_pos.txt');
Data_road1 = load('/Users/mine/study/�γ�/���߶�λ/��������λ����ʵ��2020/ʵ�����ο�����/net1_topo-error free.txt');
% Data_road1= load('/Users/mine/study/�γ�/���߶�λ/��������λ����ʵ��2020/ʵ�����ο�����/net1_topo-error 5.txt');
% Data_road1= load('/Users/mine/study/�γ�/���߶�λ/��������λ����ʵ��2020/ʵ�����ο�����/net1_topo-error 10.txt');

node_n = size(xy);
dis_n = size(Data_road1);
anchor = [];
unknown = [];
%�ֱ�ê�ڵ��δ֪�ڵ�
for i = 1:node_n(1)
    if xy(i,4) == 1
        anchor_n = anchor_n+1;%ê�ڵ����
        anchor = [anchor transpose(xy(i,:))];%ê�ڵ����
    else
        unknown_n = unknown_n+1;%��ͨ�ڵ����
        unknown = [unknown transpose(xy(i,:))];%��ͨ�ڵ����
    end
end
if anchor_n < 3
    disp('ê�ڵ����� 3 ��,DV-hop �㷨�޷�ִ��');
    return;
end
xy = [anchor unknown];%��ê�ڵ㣬����ͨ�ڵ�
for i=1:node_n(1)%��ʼ�����������Լ����Լ�Ϊ0����������Ϊ����
    for j=1:node_n(1)
        if i==j
            hop(i,j) = 0;
            dis(i,j) = 0;
        else
            hop(i,j) = inf;
            dis(i,j) = inf;
        end
    end
end
% ����ê�ڵ�֮�����
adjacency_m = zeros(node_n(1),node_n(1));
%�������
for i=1:dis_n(1)%��ʼ�������������ڽӾ���dis�и��˵ģ���������1��������Ϊֱ�Ӿ���
    hop(Data_road1(i,1),Data_road1(i,2)) = 1;
    dis(Data_road1(i,1),Data_road1(i,2)) = Data_road1(i,3);
    hop(Data_road1(i,2),Data_road1(i,1)) = 1;
    dis(Data_road1(i,2),Data_road1(i,1)) = Data_road1(i,3);
end
for i=1:anchor_n%�����ê�ڵ�֮��ľ��룬����������
    for j=1:anchor_n
        dis(i,j) = sqrt( (xy(2,i)-xy(2,j))^2+(xy(3,i)-xy(3,j))^2 );
    end
end
% �ڵ�ֲ�ͼ
plot(anchor(2,:), anchor(3,:), 'r*'); 
hold on
plot(unknown(2,:),unknown(3,:), 'bo');
xlim([0,square_L]);
ylim([0,square_L]);
title(['�ڵ�ֲ�ͼ: ��',num2str(node_n(1)),'���ڵ�,','����',num2str(anchor_n),'��ê�ڵ�']);
% �ھӹ�ϵͼ
figure
for i=1:node_n(1)
    for j=i:node_n(1)
        if(hop(i,j) == 1)%������
            line([xy(2,i),xy(2,j)],[xy(3,i),xy(3,j)],'Color','g')
            hold on;
        end
    end
end
plot(anchor(2,:), anchor(3,:), 'r*'); hold on;
plot(unknown(2,:),unknown(3,:), 'b.'); hold on;
xlim([0,square_L]);
ylim([0,square_L]);
title('�ھӹ�ϵͼ');
saveas(gcf,'/Users/mine/study/�γ�/���߶�λ/result_and_plot/neighbours.jpg')
% Flyod �㷨�����������������������
for k=1:node_n(1)
    for i=1:node_n(1)
        for j=1:node_n(1)
            if hop(i,k)+hop(k,j)<hop(i,j)
                hop(i,j)=hop(i,k)+hop(k,j);
            end
        end
    end
end
% ����ƽ����������(��ê�ڵ���㣩
% hopAvg=sum(dis(1:anchor_n,1:anchor_n),'all')/sum(hop(1:anchor_n,1:anchor_n),'all');
hopsize=zeros(1, anchor_n);%����ê�ڵ��ƽ��ÿ������
for i=1:anchor_n
    distance = 0;
    h = 0;
    for j=1:anchor_n
        % accoroding to the formula(6-7)
        if (i~=j)
            distance=distance+dis(i,j);
            h=h+hop(i,j);
        end
    end
    hopsize(i)=distance/h;
end
%����ê�ڵ�ƽ��ÿ������
hopAvg = 0;
for i=1:anchor_n
    hopAvg = hopAvg + hopsize(i);
end
hopAvg = hopAvg/anchor_n;

% �õ����ê�ڵ��ƽ���������� %count = 0; 
%����仯��ԭ������ʹ���˷�ê�ڵ�֮��ľ�����Ϊ��������ѡȡê�ڵ���ƽ��ÿ������
%���Գ��������������ê�ڵ��ƽ��ÿ�����루���ڵķ�����ѡ����δ֪�ڵ������ê�ڵ��ƽ��ÿ�����룬���ձ���õķ�����
hopdis=zeros(1,node_n(1));
for i =anchor_n+1:node_n(1)%������ͨ�ڵ�
    min=inf;
    index=0;
    for j=1:anchor_n%��������ê�ڵ�
        % simulate the first broadcast nodes gets
        % the first means the nearest
        % that is the distance is shortest
        if(dis(i,j)<min)%�����ͨ�ڵ���ê�ڵ����С���룬���Ӧ��ê�ڵ�
            min=dis(i,j);
            index=j;
        end
        % count = count+1;
    end
%     disp(index);%��ӡÿ����ͨ�ڵ���������ê�ڵ����
    if index ==0%���ĳ����ͨ�ڵ�û�е�ê�ڵ��ֱ�����ӣ�����ƽ��ÿ������Ϊȫ��ƽ��ÿ������
        hopdis(i)=hopAvg;
    else hopdis(i)=hopsize(index);%��Ȼ ��ƽ��ÿ������ ��Ϊ �����ê�ڵ� ƽ��ÿ������
    end
end
% ������Ȼ������λ��
esxy=[xy(2,1:node_n(1));xy(3,1:node_n(1))];% �����������
for i=anchor_n+1:node_n(1)%����������ͨ�ڵ�
    A=zeros(anchor_n-1,2);
    b=zeros(anchor_n-1,1);
    X=zeros(2,1);% [x;y]
    for j=1:anchor_n-1%ê�ڵ�
        A(j,1)=2*(anchor(2,j)-anchor(2,anchor_n)); % 2(xj-xn)
        A(j,2)=2*(anchor(3,j)-anchor(3,anchor_n)); % 2(yj-yn)
        %bj = xj^2-xn^2+yj^2-yn^2+dn^2-dj^2
        %dn^2 - dj^2 = (hop(i,n)*hopdis(i))^2-(hop(i,j)*hopdis(i))^2
        b(j)=anchor(2,j)^2 - anchor(2,anchor_n)^2 + anchor(3,j)^2 ...
            -anchor(3,anchor_n)^2 + hopdis(i)^2*hop(i,anchor_n)^2-hopdis(i)^2*hop(i,j)^2;
    end
    %X=(A'*A)^-1*A'*b
    X=inv(A'*A)*A'*b;
    esxy(1,i)=X(1);
    esxy(2,i)=X(2);
end
% ����λ���ͼ
figure
avg = 0;
dx = 0; %����

plot(xy(2,:),xy(3,:), 'bO',esxy(1,:),esxy(2,:),'r*'); hold on;
for i=1:node_n(1)
    line([xy(2,i),esxy(1,i)],[xy(3,i),esxy(2,i)],'Color','g')
    hold on;
end
legend('��ʵ��','���Ƶ�');
xlim([0,200]);
ylim([0,200]);
title('dv-hop��λ���ͼ');
xlabel('x')
ylabel('y')
saveas(gcf,'/Users/mine/study/�γ�/���߶�λ/result_and_plot/dvhop_real_and_esti.jpg')
%���㷽����ڹ��Ƶ㣩
for i=anchor_n:node_n(1)
    avg = avg+sqrt((xy(2,i)-esxy(1,i))^2+(xy(3,i)-esxy(2,i))^2);%��ʵ������Ƶ��ŷʽ����֮��
end
avg = avg/unknown_n;%��ʵ������Ƶ��ƽ������
for i=anchor_n:node_n(1)
    dx =(sqrt((xy(2,i)-esxy(1,i))^2+(xy(3,i)-esxy(2,i))^2)-avg)^2+dx;
end
dx = sqrt(dx/unknown_n);%����
disp(['���',num2str(dx)])
esxy=esxy';
save('/Users/mine/study/�γ�/���߶�λ/result_and_plot/dvhop_results.mat','esxy')
