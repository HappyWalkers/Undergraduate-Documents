clear
close all

load('C:\Users\mashed potato\Desktop\MCM\data\data');
%title
hair_tit=hair_pre.review_headline;
micro_tit=micro_pre.review_headline;
pacifier_tit=pacifier_pre.review_headline;
%body
hair_body=hair_pre.review_body;
micro_body=micro_pre.review_body;
pacifier_body=pacifier_pre.review_body;
%stars
hair_stars=hair_pre.star_rating;
micro_stars=micro_pre.star_rating;
pacifier_stars=pacifier_pre.star_rating;

hair_tit=preprocessTextData(hair_tit);
micro_tit=preprocessTextData(micro_tit);
pacifier_tit=preprocessTextData(pacifier_tit);

hair_body=preprocessTextData(hair_body);
micro_body=preprocessTextData(micro_body);
pacifier_body=preprocessTextData(pacifier_body);

% figure
% wordcloud(hair_tit);
% title("the review headline of hair_dryer");

%title wordcloud
figure
subplot(3,1,1);
wordcloud(hair_tit);
title("the review headline of hair dryer");
subplot(3,1,2);
wordcloud(micro_tit);
title("the review headline of micro wave");
subplot(3,1,3);
wordcloud(pacifier_tit);
title("the review headline of pacifier");

%body wordcloud
figure
subplot(3,1,1);
wordcloud(hair_body);
title("the review body of hair dryer");
subplot(3,1,2);
wordcloud(micro_body);
title("the review body of micro wave");
subplot(3,1,3);
wordcloud(pacifier_body);
title("the review body of pacifier");

%bad review title
figure
subplot(3,1,1);
idx=hair_stars==1 | hair_stars==2;
wordcloud(hair_tit(idx));
title("the bad review headline of hair dryer");
subplot(3,1,2);
idx=micro_stars==1 | micro_stars==2;
wordcloud(micro_tit(idx));
title("the bad review headline of micro wave");
subplot(3,1,3);
idx=pacifier_stars==1 | pacifier_stars==2;
wordcloud(pacifier_tit(idx));
title("the bad review headline of pacifier");
% title("Top 10% information of the 1 star pacifier review");

%bad review body
figure
subplot(3,1,1);
idx=hair_stars==1 | hair_stars==2;
wordcloud(hair_body(idx));
title("the bad review body of hair dryer");
subplot(3,1,2);
idx=micro_stars==1 | micro_stars==2;
wordcloud(micro_body(idx));
title("the bad review body of micro wave");
subplot(3,1,3);
idx=pacifier_stars==1 | pacifier_stars==2;
wordcloud(pacifier_body(idx));
title("the bad review body of pacifier");

%good review title
figure
subplot(3,1,1);
idx=hair_stars==5;
wordcloud(hair_tit(idx));
title("the good review headline of hair dryer");
subplot(3,1,2);
idx=micro_stars==5;
wordcloud(micro_tit(idx));
title("the good review headline of micro wave");
subplot(3,1,3);
idx=pacifier_stars==1 | pacifier_stars==2;
wordcloud(pacifier_tit(idx));
title("the good review headline of pacifier");

%good review body
figure
subplot(3,1,1);
idx=hair_stars==5;
wordcloud(hair_body(idx));
title("the good review body of hair dryer");
subplot(3,1,2);
idx=micro_stars==1 | micro_stars==2;
wordcloud(micro_body(idx));
title("the good review body of micro wave");
subplot(3,1,3);
idx=pacifier_stars==1 | pacifier_stars==2;
wordcloud(pacifier_body(idx));
title("the good review body of pacifier");