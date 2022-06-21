%plot_points.m

close all
clear
clc

%加载数据
node_pos=load('/Users/mine/study/课程/无线定位/result_and_plot/node_pos.mat');
node_dist=load('/Users/mine/study/课程/无线定位/result_and_plot/node_dist.mat');
imp_result=load('/Users/mine/study/课程/无线定位/result_and_plot/imp_results.mat');
dvhop_result=load('/Users/mine/study/课程/无线定位/result_and_plot/dvhop_results.mat');
pdm_result=load('/Users/mine/study/课程/无线定位/result_and_plot/pdm_results.mat');
mdsmap_result=load('/Users/mine/study/课程/无线定位/result_and_plot/mdsmap_results.mat');
%从结构体取出
node_pos=node_pos.NodePos;
node_dist=node_dist.NodeDist;
imp_result=imp_result.Loc;
dvhop_result=dvhop_result.esxy;
pdm_result=pdm_result.esxy;
mdsmap_result=mdsmap_result.save_tmp;
%计算大小
node_count=size(node_pos,1);
beacon_count=sum(node_pos(:,4));
normal_count=node_count-beacon_count;
%计算误差（距离）
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
%计算平均距离，与标准差
disp(['imp平均距离为：',num2str(mean(imp_error)),'m'])
disp(['dvhop平均距离为：',num2str(mean(dvhop_error)),'m'])
disp(['pdm平均距离为：',num2str(mean(pdm_error)),'m'])
disp(['mds平均距离为：',num2str(mean(mdsmap_error)),'m'])
disp(['imp标注差为：',num2str(std(imp_error)),'m'])
disp(['dvhop标注差为：',num2str(std(dvhop_error)),'m'])
disp(['pdm标注差为：',num2str(std(pdm_error)),'m'])
disp(['mds标注差为：',num2str(std(mdsmap_error)),'m'])


%plot
figure%所有真实估计分布图
subplot(2,2,1)
plot(node_pos((beacon_count+1):end,2),node_pos((beacon_count+1):end,3),'bO',imp_result((beacon_count+1):end,1),imp_result((beacon_count+1):end,2),'r*')
for i=beacon_count+1:node_count
    line([node_pos(i,2), imp_result(i,1) ], [node_pos(i,3), imp_result(i,2)],'Color','g')
end
title('imp')
legend('真实节点','预测节点')
xlabel('x')
ylabel('y')

subplot(2,2,2)
plot(node_pos((beacon_count+1):end,2),node_pos((beacon_count+1):end,3),'bO',dvhop_result((beacon_count+1):end,1),dvhop_result((beacon_count+1):end,2),'r*')
for i=beacon_count+1:node_count
    line([node_pos(i,2), dvhop_result(i,1) ], [node_pos(i,3), dvhop_result(i,2)],'Color','g')
end
title('dv-hop')
legend('真实节点','预测节点')
xlabel('x')
ylabel('y')

subplot(2,2,3)
plot(node_pos((beacon_count+1):end,2),node_pos((beacon_count+1):end,3),'bO',pdm_result((beacon_count+1):end,1),pdm_result((beacon_count+1):end,2),'r*')
for i=beacon_count+1:node_count
    line([node_pos(i,2), pdm_result(i,1) ], [node_pos(i,3), pdm_result(i,2)],'Color','g')
end
title('pdm')
legend('真实节点','预测节点')
xlabel('x')
ylabel('y')

subplot(2,2,4)
plot(node_pos((beacon_count+1):end,2),node_pos((beacon_count+1):end,3),'bO',mdsmap_result((beacon_count+1):end,1),mdsmap_result((beacon_count+1):end,2),'r*')
for i=beacon_count+1:node_count
    line([node_pos(i,2), mdsmap_result(i,1) ], [node_pos(i,3), mdsmap_result(i,2)],'Color','g')
end
title('mds-map')
legend('真实节点','预测节点')
xlabel('x')
ylabel('y')
saveas(gcf,'/Users/mine/study/课程/无线定位/result_and_plot/subplot_real_and_estimated.jpg')

figure%所有误差图
subplot(2,2,1)
stem(imp_error(beacon_count+1:node_count,1))
title('imp误差图')
xlabel('普通节点序号')
ylabel('误差')

subplot(2,2,2)
stem(dvhop_error(beacon_count+1:node_count,1))
title('dvhop误差图')
xlabel('普通节点序号')
ylabel('误差')

subplot(2,2,3)
stem(pdm_error(beacon_count+1:node_count,1))
title('pdm误差图')
xlabel('普通节点序号')
ylabel('误差')

subplot(2,2,4)
stem(mdsmap_error(beacon_count+1:node_count,1))
title('mdsmap误差图')
xlabel('普通节点序号')
ylabel('误差')

saveas(gcf,'/Users/mine/study/课程/无线定位/result_and_plot/subplot_error.jpg')