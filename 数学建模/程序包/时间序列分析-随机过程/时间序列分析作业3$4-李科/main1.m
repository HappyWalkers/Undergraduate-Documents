% 读取处理后的平稳时间序列
processed_data = csvread('detrend_deT_data.csv');
figure(1)
autocorr(processed_data,60)
figure(2)
parcorr(processed_data,25)
data_autocorr = autocorr(processed_data,666);
%% 参数估计和定阶
% 自相关系数向量转换为自相关系数矩阵
autocorr_matrix = vec2mat(data_autocorr);
max_p = 20;
max_q = 20;
AICs = ones(max_p,max_q);
BICs = ones(max_p,max_q);
N = 666;
for p=1:max_p
    for q = 1:max_q
        % 计算I
        P = max(p+q)+q;
        I = autocorr_matrix(1:P,1:P)\autocorr_matrix(1,2:P+1)';
        % 计算MA部分的滑动平均系数
        seta = calu_MA_parameter(I,p,q);
        % 计算AR部分的自回归系数
        fine = calu_AR_parameter(seta,I,p,q);
        % 计算方差
        [~,residual_var] = calu_var(p,q,fine,seta,N,processed_data);
        % 计算AIC和BIC并存储
        [AICs(p,q),BICs(p,q)] = calu_AIC_BIC(p,q,N,residual_var);
    end
end
% 找出最小BIC下的阶数p,q
[min_BIC_p,min_BIC_q] = find(BICs == min(BICs(:)));
% 绘制不同怕，q下对应的BIC值三维散点图
figure(3)
[X,Y] = meshgrid(1:max_p,1:max_q);
scatter3(X(:),Y(:),BICs(:),'b')
xlabel('自回归阶数'),ylabel('滑动平均阶数'),zlabel('BIC value')
hold on
scatter3(min_BIC_p,min_BIC_q,min(BICs(:)),'r')
%% 模型检验部分
% 检验初始定阶下的残差序列和参数显著性
P = max(min_BIC_p+min_BIC_q)+min_BIC_q;
I = autocorr_matrix(1:P,1:P)\autocorr_matrix(1,2:P+1)';
% 计算MA部分的滑动平均系数
seta = calu_MA_parameter(I,min_BIC_p,min_BIC_q);
% 计算AR部分的自回归系数
fine = calu_AR_parameter(seta,I,min_BIC_p,min_BIC_q);
[error,~] = calu_var(min_BIC_p,min_BIC_q,fine,seta,N,processed_data);
figure(4)
autocorr(error,25)
% 计算LB统计量-检验残差是否为白噪声序列 
lb1 = calu_LB(error, 6);
lb2 = calu_LB(error, 12);
lb3 = calu_LB(error, 18);