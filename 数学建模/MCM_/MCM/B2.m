clear

load('C:\Users\mashed potato\Desktop\MCM_data\position');

r=4;%²¶ÀÌ°ë¾¶
pos=[11,8];
fy_d=zeros(50,1);
qy_d=zeros(50,1);
for k=1:50
    m=1;
    n=1;
    for i=1:16
        for j=1:11
            
            if fy_j(i,j,k)==1
                fy_d(k,m)=dis(pos,[i,j]);
                m=m+1;
            end
            
            if qy_j(i,j,k)==1
                qy_d(k,n)=dis(pos,[i,j]);
                n=n+1;
            end
        end
    end
end

%% best
best_fyd=zeros(1,50);
best_qyd=zeros(1,50);
for best=1:50
    m=1;
    n=1;
    for i=1:size(fy_d,2)
        if fy_d(best,i)~=0
            fy_dc(m)=fy_d(best,i);
            m=m+1;
        end
    end
    for i=1:size(qy_d,2)
        if qy_d(best,i)~=0
            qy_dc(n)=qy_d(best,i);
            n=n+1;
        end
    end
    best_fyd(1,best)=min(fy_dc);
    best_qyd(1,best)=min(qy_dc);
end
best_flag=0;
for best=1:50
    if best_fyd(1,best)>r && best_qyd(1,best)>r
        best_flag=best_flag+1;
    end
    if best_flag==3
        best=best-2;
        break
    end
    if best<50
        if best_fyd(1,best+1)<r || best_qyd(1,best+1)<r
            best_flag=0;
        end
    end
end
%% worst
worst_fyd=zeros(1,50);
worst_qyd=zeros(1,50);

for worst=1:50
    m=1;
    n=1;
    for i=1:size(fy_d,2)
        if fy_d(worst,i)~=0
            fy_dc(m)=fy_d(worst,i);
            m=m+1;
        end
    end
    for i=1:size(qy_d,2)
        if qy_d(worst,i)~=0
            qy_dc(n)=qy_d(worst,i);
            n=n+1;
        end
    end
    worst_fyd(1,worst)=max(fy_dc);
    worst_qyd(1,worst)=max(qy_dc);
end
worst_flag=0;
for worst=1:50
    if worst_fyd(1,worst)>r && worst_qyd(1,worst)>r
        worst_flag=worst_flag+1;
    end
    if worst_flag==3
        worst=worst-2;
        break
    end
    if worst<50
        if worst_fyd(1,worst+1)<r || worst_qyd(1,worst+1)<r
            worst_flag=0;
        end
    end
end

%% possible
possible_fyd=zeros(1,50);
possible_qyd=zeros(1,50);

for possible=1:50
    m=1;
    n=1;
    for i=1:size(fy_d,2)
        if fy_d(possible,i)~=0
            fy_dc(m)=fy_d(possible,i);
            m=m+1;
        end
    end
    for i=1:size(qy_d,2)
        if qy_d(possible,i)~=0
            qy_dc(n)=qy_d(possible,i);
            n=n+1;
        end
    end
    possible_fyd(1,possible)=mean(fy_dc);
    possible_qyd(1,possible)=mean(qy_dc);
end
possible_flag=0;
for possible=1:50
    if possible_fyd(1,possible)>r && possible_qyd(1,possible)>r
        possible_flag=possible_flag+1;
    end
    if possible_flag==3
        possible=possible-2;
        break;
    end
    if possible<50
        if possible_fyd(1,possible+1)<r || possible_qyd(1,possible+1)<r
            possible_flag=0;
        end
    end
end
save('C:\Users\mashed potato\Desktop\MCM_data\B','best','worst','possible');