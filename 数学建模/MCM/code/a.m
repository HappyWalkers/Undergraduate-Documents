clear
close all

%以ReviewID作为主键
hair_dryer=readtable('C:\Users\mashed potato\Desktop\MCM\data\NandYandClean\hair_dryer.xlsx','ReadRowNames',true);
micro_wave=readtable('C:\Users\mashed potato\Desktop\MCM\data\NandYandClean\micro_wave.xlsx','ReadRowNames',true);
pacifier=readtable('C:\Users\mashed potato\Desktop\MCM\data\NandYandClean\pacifier.xlsx','ReadRowNames',true);

%review_body
hair_body=hair_dryer.review_body;
%review_headline
hair_tit=hair_dryer.review_headline;
%help
hair_help=hair_dryer.helpful_votes;
%total
hair_total=hair_dryer.total_votes;
% hair_total=zeros(1,1);
% for i=1:size(hair_total_1,1)
%     hair_total(i)=hair_total_1{i};
% end
%stars
hair_star=hair_dryer.star_rating;

hair_num=size(hair_body,1);
body_length=zeros(1,1);
tit_length=zeros(1,1);
for i=1:hair_num
    body_length(i)=length(hair_body{i});
    tit_length(i)=length(hair_body{i});
end
length=body_length+tit_length;
length=reshape(length,size(length,2),size(length,1));

information=length.*(2*hair_help-hair_total+1);
[sort_info,sort_i]=sort(information,'descend');
hair_body10="";
hair_tit10="";
hair_body105="";
hair_tit105="";
hair_body101="";
hair_tit101="";
for i=1:hair_num/10
    hair_body10(i)=hair_body{sort_i(i)};
    hair_tit10(i)=hair_tit{sort_i(i)};
    if hair_star(sort_i(i))==5
        hair_body105(i)=hair_body{sort_i(i)};
        hair_tit105(i)=hair_tit{sort_i(i)};
    end
    if hair_star(sort_i(i))==1
        hair_body101(i)=hair_body{sort_i(i)};
        hair_tit101(i)=hair_tit{sort_i(i)};
    end
end
hair_rev=strcat(hair_tit10,hair_body10);
hair_rev5=strcat(hair_tit105,hair_body105);
hair_rev1=strcat(hair_tit101,hair_body101);
hair_rev=preprocessTextData(hair_rev);
hair_rev5=preprocessTextData(hair_rev5);
hair_rev1=preprocessTextData(hair_rev1);


% figure
% wordcloud(hair_rev);
% title("Top 10% information of the hair dryer review");

figure
subplot(1,2,1);
wordcloud(hair_rev5);
% title("Top 10% information of the 5 stars hair dryer review");
title({'Top 10% information of the 5 stars';' hair dryer review'});
subplot(1,2,2);
wordcloud(hair_rev1);
% title("Top 10% information of the 1 star hair dryer review");
title({'Top 10% information of the 1 stars';'hair dryer review'});



