clear

load('C:\Users\mashed potato\Desktop\MCM_data\scdata');

%% input
time=1870:2015;
[time,ps_t]=mapminmax(time,0,1);
degree=zeros(16,11,12,length(time));%每个点12个月的预测,最后一维放一百多年的数据
% ps_d=repmat(struct('x',1), 10000, 1 );
for i=1:16%行
    for j=1:11%列
        for k=1:12%月
            for l=1:length(time)%年
                degree(i,j,k,l)=scdata(i,j,k+12*(l-1));
            end
            if degree(i,j,k,2)~=-327.6800
                [degree(i,j,k,:),ps_d(i,j,k)]=mapminmax(reshape(degree(i,j,k,:),1,146),-1,1);
            end
        end
    end
end

%% train
net=cell(16,11,12);
guess=zeros(16,11,12,146);
for i=1:16
    for j=1:11
        for k=1:12
            if degree(i,j,k,2)~=-327.6800
                net{i,j,k}=newff(minmax(reshape(degree(i,j,k,:),1,146)),[200,1],{'tansig','purelin'});
                net{i,j,k}.trainParam.epochs=50;   %最大训练次数
                net{i,j,k}.trainParam.goal=0;       %训练目标
                net{i,j,k}.trainParam.show=50;      %两次显示之间的训练次数
                net{i,j,k}.trainParam.min_grad=1e-10;
                net{i,j,k}=train(net{i,j,k},time,reshape(degree(i,j,k,:),1,146));
            end
        end
    end
end

% %% output
% for i=1:16
%     for j=1:11
%         for k=1:12
%             if degree(i,j,k,2)~=-327.6800
%                 guess(i,j,k,:)=sim(net{i,j,k},time);
%                 degree(i,j,k,:)=mapminmax('reverse',reshape(degree(i,j,k,:),1,146),ps_d(i,j,k));
%                 guess(i,j,k,:)=mapminmax('reverse',reshape(guess(i,j,k,:),1,146),ps_d(i,j,k));
%                 %             figure
%                 %             plot(time,reshape(degree(i,j,k,:),1,146),'r*',time,reshape(guess(i,j,k,:),1,146),'b');
%                 %             legend('degree','guess');
%             end
%         end
%     end
% end
% time=mapminmax('reverse',time,ps_t);
save('C:\Users\mashed potato\Desktop\MCM_data\A3','net','ps_t','ps_d','degree');
