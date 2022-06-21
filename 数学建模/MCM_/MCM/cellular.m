clear

load('C:\Users\mashed potato\Desktop\MCM_data\guess50');

fy_min=10;
fy_max=11;
qy_min=9;
qy_max=10;
qy_score=zeros(16,11,50);
fy_score=zeros(16,11,50);

%fy
for i=1:16
    if i==1 || i==16
        continue;
    end
    for j=1:11
        if j==1 || j==11
            continue;
        end
        for k=1:50
            if guess_y(i,j,k)>fy_min && guess_y(i,j,k)<fy_max
                fy_score(i,j,k)=fy_score(i,j,k)+1;
            end
            if guess_y(i-1,j,k)>fy_min && guess_y(i-1,j,k)<fy_max
                fy_score(i,j,k)=fy_score(i,j,k)+1;
            end
            if guess_y(i-1,j-1,k)>fy_min && guess_y(i-1,j-1,k)<fy_max
                fy_score(i,j,k)=fy_score(i,j,k)+1;
            end
            if guess_y(i-1,j+1,k)>fy_min && guess_y(i-1,j+1,k)<fy_max
                fy_score(i,j,k)=fy_score(i,j,k)+1;
            end
            if guess_y(i,j-1,k)>fy_min && guess_y(i,j-1,k)<fy_max
                fy_score(i,j,k)=fy_score(i,j,k)+1;
            end
            if guess_y(i,j+1,k)>fy_min && guess_y(i,j+1,k)<fy_max
                fy_score(i,j,k)=fy_score(i,j,k)+1;
            end
            if guess_y(i+1,j,k)>fy_min && guess_y(i+1,j,k)<fy_max
                fy_score(i,j,k)=fy_score(i,j,k)+1;
            end
            if guess_y(i+1,j+1,k)>fy_min && guess_y(i+1,j+1,k)<fy_max
                fy_score(i,j,k)=fy_score(i,j,k)+1;
            end
            if guess_y(i+1,j-1,k)>fy_min && guess_y(i+1,j-1,k)<fy_max
                fy_score(i,j,k)=fy_score(i,j,k)+1;
            end
        end
    end
end

%qy
for i=1:16
    if i==1 || i==16
        continue;
    end
    for j=1:11
        if j==1 || j==11
            continue;
        end
        for k=1:50
            if guess_y(i,j,k)>qy_min && guess_y(i,j,k)<qy_max
                qy_score(i,j,k)=qy_score(i,j,k)+1;
            end
            if guess_y(i-1,j,k)>qy_min && guess_y(i-1,j,k)<qy_max
                qy_score(i,j,k)=qy_score(i,j,k)+1;
            end
            if guess_y(i-1,j-1,k)>qy_min && guess_y(i-1,j-1,k)<qy_max
                qy_score(i,j,k)=qy_score(i,j,k)+1;
            end
            if guess_y(i-1,j+1,k)>qy_min && guess_y(i-1,j+1,k)<qy_max
                qy_score(i,j,k)=qy_score(i,j,k)+1;
            end
            if guess_y(i,j-1,k)>qy_min && guess_y(i,j-1,k)<qy_max
                qy_score(i,j,k)=qy_score(i,j,k)+1;
            end
            if guess_y(i,j+1,k)>qy_min && guess_y(i,j+1,k)<qy_max
                qy_score(i,j,k)=qy_score(i,j,k)+1;
            end
            if guess_y(i+1,j,k)>qy_min && guess_y(i+1,j,k)<qy_max
                qy_score(i,j,k)=qy_score(i,j,k)+1;
            end
            if guess_y(i+1,j+1,k)>qy_min && guess_y(i+1,j+1,k)<qy_max
                qy_score(i,j,k)=qy_score(i,j,k)+1;
            end
            if guess_y(i+1,j-1,k)>qy_min && guess_y(i+1,j-1,k)<qy_max
                qy_score(i,j,k)=qy_score(i,j,k)+1;
            end
        end
    end
end

fy_j=zeros(16,11,50);
qy_j=zeros(16,11,50);
for i=1:16
    for j=1:11
        for k=1:50
            if fy_score(i,j,k)>=9
                fy_j(i,j,k)=1;
            else
                fy_j(i,j,k)=0;
            end
            
            if qy_score(i,j,k)>=9
                qy_j(i,j,k)=1;
            else
                qy_j(i,j,k)=0;
            end
        end
    end
end
save('C:\Users\mashed potato\Desktop\MCM_data\position','fy_j','qy_j','fy_score','qy_score');