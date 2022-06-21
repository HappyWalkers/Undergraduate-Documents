clear
close all

opts = detectImportOptions('C:\Users\mashed potato\Desktop\MCM\data\YandProduct\micro.xlsx');
opts.Sheet='Sheet1';
hair_pro=readtable('C:\Users\mashed potato\Desktop\MCM\data\YandProduct\micro.xlsx',opts,'ReadRowNames',true);

%stars
hair_stars=hair_pro.star_rating;
%help
hair_help=hair_pro.helpful_votes;
%all
hair_all=hair_pro.total_votes;
%year
hair_y=hair_pro.year;
%month
hair_m=hair_pro.month;
%day
hair_d=hair_pro.day;

hair_rep=(hair_stars-3).*(2*hair_help-hair_all+1);
hair_num=size(hair_rep,1);
for i=1:hair_num
%     if (2*hair_help(i)-hair_all(i)+1)~=0
%         hair_rep(i)=(hair_stars(i)-3).*log(2*hair_help(i)-hair_all(i)+1);
%     end
%     if abs(hair_rep(i))>100
%         hair_rep(i)=100;
%     end
    if abs(hair_rep(i))>0
        hair_rep(i)=log(hair_rep(i));
    end
end
hair_rep_ch=hair_rep;

hair_rep_sum(hair_num)=hair_rep(hair_num);
for i=hair_num-1:-1:1%累加
    hair_rep_sum(i)=hair_rep(i);
    for j=hair_num:-1:i+1%计算之前所有衰减
        %         if hair_m(i)<hair_m(j)
        %             t=abs(hair_y(i)-hair_y(j))*365+abs(12+(hair_m(i)-hair_m(j)))*30+abs(hair_d(i)-hair_d(j))*1;
        %         else
        %             t=abs(hair_y(i)-hair_y(j))*365+abs(hair_m(i)-hair_m(j))*30+abs(hair_d(i)-hair_d(j))*1;
        %         end
        t=(hair_y(i)-hair_y(j))*365+(hair_m(i)-hair_m(j))*30+(hair_d(i)-hair_d(j))*1;
        hair_rep_ch(j)=hair_rep(j)*(1-t/(365*5));
        hair_rep_sum(i)=hair_rep_sum(i)+hair_rep_ch(j);
    end
%     if i/199==1
%         plot(hair_rep_sum);
%     end
end

hair_last=hair_rep_sum(size(hair_rep_sum,2):-1:1);
time=(hair_y-hair_y(hair_num))*365+(hair_m-hair_m(hair_num))*30+(hair_d-hair_d(hair_num))*1;
time_last=time(size(time,1):-1:1);
figure
plot(time_last,hair_last);
title("the reputation of a kind of micro wave");
xlabel("time");
ylabel("reputation");
xticks([0 365 2*365 3*365 4*365 5*365]);
xticklabels({'2012','2013','2014','2015'});