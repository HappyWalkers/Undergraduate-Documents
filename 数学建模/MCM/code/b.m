clear
close all

load('C:\Users\mashed potato\Desktop\MCM\data\data');
%stars
hair_stars=hair_pro.star_rating;
% micro_stars=micro_pro.star_rating;
% pacifier_stars=pacifier_pro.star_rating;
%help
hair_help=hair_pro.helpful_votes;
% micro_help=micro_pro.helpful_votes;
% pacifier_help=pacifier_pro.helpful_votes;
%all
hair_all=hair_pro.total_votes;
% micro_all=micro_pro.total_votes;
% pacifier_all=pacifier_pro.total_votes;
%date
% hair_date=hair_pro.review_date;
% micro_date=micro_pro.review_date;
% pacifier_date=pacifier_pro.review_date;
%year
hair_y=hair_pro.year;
%month
hair_m=hair_pro.month;
%day
hair_d=hair_pro.day;


%reputation=(star-3)*(2*help-all+1);
%rep=b-kt;
%k=b/5*365;

hair_rep=(hair_stars-3).*(2.*hair_help-hair_all+1);
hair_num=size(hair_rep,1);
hair_rep_sum(hair_num)=hair_rep(hair_num);
for i=hair_num-1:-1:1%累加
    hair_rep_sum(i)=hair_rep(i);
    for j=hair_num:-1:i+1%计算之前所有衰减
        t=abs(hair_y(i)-hair_y(j))*365+abs(hair_m(i)-hair_m(j))*30+abs(hair_d(i)-hair_d(j))*1;
        hair_rep(j)=hair_rep(j)*(1-t/(365*5));
        hair_rep_sum(i)=hair_rep_sum(i)+hair_rep(j);
    end
end

figure
x=1:size(hair_rep_sum,1);
plot(x,hair_rep_sum);
