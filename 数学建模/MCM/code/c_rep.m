clear
close all

opts = detectImportOptions('C:\Users\mashed potato\Desktop\MCM\data\NandYandProduct\hair_pro5.xlsx');
opts.Sheet='Sheet5';
hair_pro=readtable('C:\Users\mashed potato\Desktop\MCM\data\NandYandProduct\hair_pro5.xlsx',opts,'ReadRowNames',true);

%stars
hair_stars=hair_pro.star_rating;
%help
hair_help=hair_pro.helpful_votes;
%all
hair_all=hair_pro.total_votes;
%year
hair_y=hair_pro.month_1;
%month
hair_m=hair_pro.month;
%day
hair_d=hair_pro.day;

hair_rep=(hair_stars-3).*(2*hair_help-hair_all+1);
hair_num=size(hair_rep,1);
for i=1:hair_num
    if abs(hair_rep(i))>0
        hair_rep(i)=log(hair_rep(i));
    end
end
hair_rep_ch=hair_rep;

hair_rep_sum(hair_num)=hair_rep(hair_num);
for i=hair_num-1:-1:1%累加
    hair_rep_sum(i)=hair_rep(i);
    for j=hair_num:-1:i+1%计算之前所有衰减
        t=(hair_y(i)-hair_y(j))*365+(hair_m(i)-hair_m(j))*30+(hair_d(i)-hair_d(j))*1;
        hair_rep_ch(j)=hair_rep(j)*(1-t/(365*5));
        hair_rep_sum(i)=hair_rep_sum(i)+hair_rep_ch(j);
    end
end
ave_reputation_5=mean(real(hair_rep),'omitnan');

save('C:\Users\mashed potato\Desktop\MCM\data\reputation\reputation_5','ave_reputation_5');