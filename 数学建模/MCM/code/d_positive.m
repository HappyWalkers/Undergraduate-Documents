clear
close all

opts = detectImportOptions('C:\Users\mashed potato\Desktop\MCM\data\NandYandProduct\hair_pro5.xlsx');
opts.Sheet='Sheet1';
hair_pro=readtable('C:\Users\mashed potato\Desktop\MCM\data\NandYandProduct\hair_pro5.xlsx',opts,'ReadRowNames',true);

%star
hair_star=hair_pro.star_rating;

num_star=size(hair_star,1);
rate=zeros(1,1);
num_all=zeros(1,1);
num_1=zeros(1,1);
for guest_see=1:10
    influence=zeros(1,1);
    for i=num_star:-1:1+guest_see
        if sum(hair_star(i:-1:i-guest_see+1)==5)==guest_see%如果连续guest_see个数为5
            influence(i-guest_see)=hair_star(i-guest_see)/5;
        end
    end
    num_1(guest_see)=sum(influence(1:end)>0.6);
    num_all(guest_see)=sum(influence(1:end)>0);
    rate(guest_see)=num_1(guest_see)/num_all(guest_see);
end

figure
plot(1:guest_see,rate);
title("the relation between 5-stars guest saw and his feedback");
xlabel('the num of 5-stars guest saw');
ylabel('the percentage of good feedback');
ylim([0 1.2]);

figure
plot(1:guest_see,num_1);
hold on
plot(1:guest_see,num_all);
title("the relation between 5-stars guest saw and his feedback");
legend('the number of postive review after see some 5-stars','the number of all views after see some 5-stars');
xlabel('the num of 5-stars guest saw');
ylabel('the number of n 5-stars');