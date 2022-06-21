clear
close all

load('C:\Users\mashed potato\Desktop\MCM\data\d\data_1');%length,sentiment

opts = detectImportOptions('C:\Users\mashed potato\Desktop\MCM\data\NandYandProduct\hair_pro5.xlsx');
opts.Sheet='Sheet1';
hair_pro=readtable('C:\Users\mashed potato\Desktop\MCM\data\NandYandProduct\hair_pro5.xlsx',opts,'ReadRowNames',true);

%star
hair_star=hair_pro.star_rating;

length_1=reshape(length_1,size(length_1,2),size(length_1,1));
sentimentScore_1=reshape(sentimentScore_1,size(sentimentScore_1,2),size(sentimentScore_1,1));

num=size(hair_star,1);
star_time=hair_star;
for i=1:num-10
    star_time(i)=mean(hair_star(i+1:i+10));
end

% [corral_sentiment,pval_sentiment]=corr(hair_star,sentimentScore_1,'Type','Kendall')
% [corral_length,pval_length]=corr(hair_star,length_1,'Type','Kendall')
% 
% [corral_sentiment,pval_sentiment]=corr(hair_star,sentimentScore_1,'Type','Pearson')
% [corral_length,pval_length]=corr(hair_star,length_1,'Type','Pearson')

[corral_sentiment,pval_sentiment]=corr(hair_star-3,sentimentScore_1,'Type','Spearman')
[corral_length,pval_length]=corr(hair_star-3,length_1,'Type','Spearman')

    