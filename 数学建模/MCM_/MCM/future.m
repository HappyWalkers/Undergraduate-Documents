clear

load('C:\Users\mashed potato\Desktop\MCM_data\A3');

time=2021:2070;
[time,ps_t]=mapminmax(time,0,1);
guess=zeros(16,11,12,50);%Î»ÖÃ£¬12ÔÂ£¬50Äê
guess_y=zeros(16,11,50);
for i=1:16
    for j=1:11
        for k=1:12
            if degree(i,j,k,2)~=-327.6800
                guess(i,j,k,:)=sim(net{i,j,k},time);
                guess(i,j,k,:)=mapminmax('reverse',reshape(guess(i,j,k,:),1,50),ps_d(i,j,k));
            end
        end
    end
end

for i=1:16
    for j=1:11
        for l=1:50
            if degree(i,j,2,2)~=-327.6800
                guess_y(i,j,l)=mean( reshape(guess(i,j,:,l),1,12));
            end
        end
    end
end

time=mapminmax('reverse',time,ps_t);
save('C:\Users\mashed potato\Desktop\MCM_data\guess50','guess_y');


