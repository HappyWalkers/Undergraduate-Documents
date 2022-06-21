% ��ȡ������ƽ��ʱ������
processed_data = csvread('detrend_deT_data.csv');
figure(1)
autocorr(processed_data,60)
figure(2)
parcorr(processed_data,25)
data_autocorr = autocorr(processed_data,666);
%% �������ƺͶ���
% �����ϵ������ת��Ϊ�����ϵ������
autocorr_matrix = vec2mat(data_autocorr);
max_p = 20;
max_q = 20;
AICs = ones(max_p,max_q);
BICs = ones(max_p,max_q);
N = 666;
for p=1:max_p
    for q = 1:max_q
        % ����I
        P = max(p+q)+q;
        I = autocorr_matrix(1:P,1:P)\autocorr_matrix(1,2:P+1)';
        % ����MA���ֵĻ���ƽ��ϵ��
        seta = calu_MA_parameter(I,p,q);
        % ����AR���ֵ��Իع�ϵ��
        fine = calu_AR_parameter(seta,I,p,q);
        % ���㷽��
        [~,residual_var] = calu_var(p,q,fine,seta,N,processed_data);
        % ����AIC��BIC���洢
        [AICs(p,q),BICs(p,q)] = calu_AIC_BIC(p,q,N,residual_var);
    end
end
% �ҳ���СBIC�µĽ���p,q
[min_BIC_p,min_BIC_q] = find(BICs == min(BICs(:)));
% ���Ʋ�ͬ�£�q�¶�Ӧ��BICֵ��άɢ��ͼ
figure(3)
[X,Y] = meshgrid(1:max_p,1:max_q);
scatter3(X(:),Y(:),BICs(:),'b')
xlabel('�Իع����'),ylabel('����ƽ������'),zlabel('BIC value')
hold on
scatter3(min_BIC_p,min_BIC_q,min(BICs(:)),'r')
%% ģ�ͼ��鲿��
% �����ʼ�����µĲв����кͲ���������
P = max(min_BIC_p+min_BIC_q)+min_BIC_q;
I = autocorr_matrix(1:P,1:P)\autocorr_matrix(1,2:P+1)';
% ����MA���ֵĻ���ƽ��ϵ��
seta = calu_MA_parameter(I,min_BIC_p,min_BIC_q);
% ����AR���ֵ��Իع�ϵ��
fine = calu_AR_parameter(seta,I,min_BIC_p,min_BIC_q);
[error,~] = calu_var(min_BIC_p,min_BIC_q,fine,seta,N,processed_data);
figure(4)
autocorr(error,25)
% ����LBͳ����-����в��Ƿ�Ϊ���������� 
lb1 = calu_LB(error, 6);
lb2 = calu_LB(error, 12);
lb3 = calu_LB(error, 18);