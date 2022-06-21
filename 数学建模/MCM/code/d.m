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

% [rho_sentiment,pval_sentiment]=corr(hair_star,sentimentScore_1,'Type','Kendall')
% [rho_length,pval_length]=corr(hair_star,length_1,'Type','Kendall')
% 
% [rho_sentiment,pval_sentiment]=corr(hair_star,sentimentScore_1,'Type','Pearson')
% [rho_length,pval_length]=corr(hair_star,length_1,'Type','Pearson')
% 
[rho_sentiment,pval_sentiment]=corr(hair_star-3,sentimentScore_1,'Type','Spearman')
[rho_length,pval_length]=corr(hair_star-3,length_1,'Type','Spearman')

% save('C:\Users\mashed potato\Desktop\data','length_1','sentimentScore_1','hair_star');




