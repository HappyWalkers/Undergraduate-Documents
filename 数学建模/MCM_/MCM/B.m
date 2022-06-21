clear

load('C:\Users\mashed potato\Desktop\MCM_data\position');

r=2;%²¶ÀÌ°ë¾¶
pos=[11,8];
fy_d=zeros(16,11,50);
qy_d=zeros(16,11,50);
for k=1:50
    for i=1:16
        for j=1:11
            
            if fy_j(i,j,k)==1
                fy_d(i,j,k)=dis(pos,[i,j]);
            end
            
            if qy_j(i,j,k)==1
                qy_d(i,j,k)=dis(pos,[i,j]);
            end
            
        end
    end
end

%% best
best_fyd=zeros(1,50);
best_qyd=zeros(1,50);

for k=1:50
    for i=1:16
        for j=1:11
            if fy_d(i,j,k)==0
                fy_d(i,j,k)=100;
            end
            if qy_d(i,j,k)==0
                qy_d(i,j,k)=100;
            end
        end
    end
end

for best=1:50
    best_fyd(1,best)=min( fy_d(:,:,best),[],'all');
    best_qyd(1,best)=min(qy_d(:,:,best),[],'all');
    if best_fyd(1,best)>r && best_qyd(1,best)>r
        break
    end
end

for k=1:50
    for i=1:16
        for j=1:11
            if fy_d(i,j,k)==100
                fy_d(i,j,k)=0;
            end
            if qy_d(i,j,k)==100
                qy_d(i,j,k)=0;
            end
        end
    end
end
%% worst
worst_fyd=zeros(1,50);
worst_qyd=zeros(1,50);

for worst=1:50
    worst_fyd(1,worst)=max( fy_d(:,:,worst),[],'all');
    worst_qyd(1,worst)=max(qy_d(:,:,worst),[],'all');
    if worst_fyd(1,worst)>r && worst_qyd(1,worst)>r
        break
    end
end


%% possible
possible_fyd=zeros(1,50);
possible_qyd=zeros(1,50);

for possible=1:50
    possible_fyd(1,possible)=median( fy_d(:,:,possible),'all');
    possible_qyd(1,possible)=median(qy_d(:,:,possible),'all');
    if possible_fyd(1,possible)>r && possible_qyd(1,possible)>r
        break
    end
end


save('C:\Users\mashed potato\Desktop\MCM_data\B','best','worst','possible');