%plot_points.m

close all
clear
clc

%��������
node_pos=load('/Users/mine/study/�γ�/���߶�λ/result_and_plot/node_pos.mat');
node_dist=load('/Users/mine/study/�γ�/���߶�λ/result_and_plot/node_dist.mat');
imp_result=load('/Users/mine/study/�γ�/���߶�λ/result_and_plot/imp_results.mat');
dvhop_result=load('/Users/mine/study/�γ�/���߶�λ/result_and_plot/dvhop_results.mat');
pdm_result=load('/Users/mine/study/�γ�/���߶�λ/result_and_plot/pdm_results.mat');
mdsmap_result=load('/Users/mine/study/�γ�/���߶�λ/result_and_plot/mdsmap_results.mat');
%�ӽṹ��ȡ��
node_pos=node_pos.NodePos;
node_dist=node_dist.NodeDist;
imp_result=imp_result.Loc;
dvhop_result=dvhop_result.esxy;
pdm_result=pdm_result.esxy;
mdsmap_result=mdsmap_result.save_tmp;
%�����С
node_count=size(node_pos,1);
beacon_count=sum(node_pos(:,4));
normal_count=node_count-beacon_count;
%���������룩
% error(i,1) = sqrt((NodePos(i,2)-Loc(i,1))^2+(NodePos(i,3)-Loc(i,2))^2);
imp_error=zeros(node_count,1);
dvhop_error=zeros(node_count,1);
pdm_error=zeros(node_count,1);
mdsmap_error=zeros(node_count,1);
for i=1:node_count
    imp_error(i,1) = sqrt((node_pos(i,2)-imp_result(i,1))^2+(node_pos(i,3)-imp_result(i,2))^2);
    dvhop_error(i,1) = sqrt((node_pos(i,2)-dvhop_result(i,1))^2+(node_pos(i,3)-dvhop_result(i,2))^2);
    pdm_error(i,1) = sqrt((node_pos(i,2)-pdm_result(i,1))^2+(node_pos(i,3)-pdm_result(i,2))^2);
    mdsmap_error(i,1) = sqrt((node_pos(i,2)-mdsmap_result(i,1))^2+(node_pos(i,3)-mdsmap_result(i,2))^2);
end
%����ƽ�����룬���׼��
disp(['impƽ������Ϊ��',num2str(mean(imp_error)),'m'])
disp(['dvhopƽ������Ϊ��',num2str(mean(dvhop_error)),'m'])
disp(['pdmƽ������Ϊ��',num2str(mean(pdm_error)),'m'])
disp(['mdsƽ������Ϊ��',num2str(mean(mdsmap_error)),'m'])
disp(['imp��ע��Ϊ��',num2str(std(imp_error)),'m'])
disp(['dvhop��ע��Ϊ��',num2str(std(dvhop_error)),'m'])
disp(['pdm��ע��Ϊ��',num2str(std(pdm_error)),'m'])
disp(['mds��ע��Ϊ��',num2str(std(mdsmap_error)),'m'])


%plot
figure%������ʵ���Ʒֲ�ͼ
subplot(2,2,1)
plot(node_pos((beacon_count+1):end,2),node_pos((beacon_count+1):end,3),'bO',imp_result((beacon_count+1):end,1),imp_result((beacon_count+1):end,2),'r*')
for i=beacon_count+1:node_count
    line([node_pos(i,2), imp_result(i,1) ], [node_pos(i,3), imp_result(i,2)],'Color','g')
end
title('imp')
legend('��ʵ�ڵ�','Ԥ��ڵ�')
xlabel('x')
ylabel('y')

subplot(2,2,2)
plot(node_pos((beacon_count+1):end,2),node_pos((beacon_count+1):end,3),'bO',dvhop_result((beacon_count+1):end,1),dvhop_result((beacon_count+1):end,2),'r*')
for i=beacon_count+1:node_count
    line([node_pos(i,2), dvhop_result(i,1) ], [node_pos(i,3), dvhop_result(i,2)],'Color','g')
end
title('dv-hop')
legend('��ʵ�ڵ�','Ԥ��ڵ�')
xlabel('x')
ylabel('y')

subplot(2,2,3)
plot(node_pos((beacon_count+1):end,2),node_pos((beacon_count+1):end,3),'bO',pdm_result((beacon_count+1):end,1),pdm_result((beacon_count+1):end,2),'r*')
for i=beacon_count+1:node_count
    line([node_pos(i,2), pdm_result(i,1) ], [node_pos(i,3), pdm_result(i,2)],'Color','g')
end
title('pdm')
legend('��ʵ�ڵ�','Ԥ��ڵ�')
xlabel('x')
ylabel('y')

subplot(2,2,4)
plot(node_pos((beacon_count+1):end,2),node_pos((beacon_count+1):end,3),'bO',mdsmap_result((beacon_count+1):end,1),mdsmap_result((beacon_count+1):end,2),'r*')
for i=beacon_count+1:node_count
    line([node_pos(i,2), mdsmap_result(i,1) ], [node_pos(i,3), mdsmap_result(i,2)],'Color','g')
end
title('mds-map')
legend('��ʵ�ڵ�','Ԥ��ڵ�')
xlabel('x')
ylabel('y')
saveas(gcf,'/Users/mine/study/�γ�/���߶�λ/result_and_plot/subplot_real_and_estimated.jpg')

figure%�������ͼ
subplot(2,2,1)
stem(imp_error(beacon_count+1:node_count,1))
title('imp���ͼ')
xlabel('��ͨ�ڵ����')
ylabel('���')

subplot(2,2,2)
stem(dvhop_error(beacon_count+1:node_count,1))
title('dvhop���ͼ')
xlabel('��ͨ�ڵ����')
ylabel('���')

subplot(2,2,3)
stem(pdm_error(beacon_count+1:node_count,1))
title('pdm���ͼ')
xlabel('��ͨ�ڵ����')
ylabel('���')

subplot(2,2,4)
stem(mdsmap_error(beacon_count+1:node_count,1))
title('mdsmap���ͼ')
xlabel('��ͨ�ڵ����')
ylabel('���')

saveas(gcf,'/Users/mine/study/�γ�/���߶�λ/result_and_plot/subplot_error.jpg')