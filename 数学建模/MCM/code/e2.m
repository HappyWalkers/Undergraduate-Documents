clear
close all

%以ReviewID作为主键，需要清洗

hair_five=readtable('C:\Users\mashed potato\Desktop\MCM\data\FiveandOne\five.xlsx','ReadRowNames',true);
hair_one=readtable('C:\Users\mashed potato\Desktop\MCM\data\FiveandOne\one.xlsx','ReadRowNames',true);

%title
hair_tit5=hair_five.review_headline;
hair_tit1=hair_one.review_headline;
%body
hair_body5=hair_five.review_body;
hair_body1=hair_one.review_body;
%hair_body5
hair_body5=strjoin(hair_body5);
 hair_body5=preprocessTextData(hair_body5);
hair_body5=doc2cell(hair_body5);
hair_body5=hair_body5{1};
hair_body5=reshape(hair_body5,[size(hair_body5,2),size(hair_body5,1)]);
% hair_body1
hair_body1=strjoin(hair_body1);
 hair_body1=preprocessTextData(hair_body1);
hair_body1=doc2cell(hair_body1);
hair_body1=hair_body1{1};
hair_body1=reshape(hair_body1,[size(hair_body1,2),size(hair_body1,1)]);

%train
emb = fastTextWordEmbedding;
data = readLexicon;
idx = ~isVocabularyWord(emb,data.Word);
data(idx,:) = [];
numWords = size(data,1);
cvp = cvpartition(numWords,'HoldOut',0.1);
dataTrain = data(training(cvp),:);
% dataTest = data(test(cvp),:);
wordsTrain = dataTrain.Word;
XTrain = word2vec(emb,wordsTrain);
YTrain = dataTrain.Label;
mdl = fitcsvm(XTrain,YTrain);
% wordsTest = dataTest.Word;
% XTest = word2vec(emb,wordsTest);
% YTest = dataTest.Label;
% [YPred,scores] = predict(mdl,XTest);
hair_body_test5 = word2vec(emb,hair_body5);
[hair_body_pred5,hair_body_scores5]=predict(mdl,hair_body_test5);
hair_body_test1 = word2vec(emb,hair_body1);
[hair_body_pred1,hair_body_scores1]=predict(mdl,hair_body_test1);

% figure
% confusionchart(YTest,YPred);
one_star={'Negative'};
one_star=categorical(one_star);
one_star=repmat(one_star,size(hair_body_pred1));
five_star={'Positive'};
five_star=categorical(five_star);
five_star=repmat(five_star,size(hair_body_pred5));
star=[five_star;one_star];
hair_pred=[hair_body_pred5;hair_body_pred1];

% figure
% confusionchart(star,hair_pred);
% title("The distribution of Sentiment and Stars");

%hair_body5
% figure
% % subplot(1,2,1)
% idx = hair_body_pred5== "Positive";
% wordcloud(hair_body5(idx));
% title("Predicted Positive Sentiment")
% 
% subplot(1,2,2)
% idx = hair_body_pred5== "Negative";
% wordcloud(hair_body5(idx));
% title("Predicted Negative Sentiment")

% hair_body1
% figure
% subplot(1,2,1)
% idx = hair_body_pred1== "Positive";
% wordcloud(hair_body1(idx));
% title("Predicted Positive Sentiment")

% subplot(1,2,2)
% idx = hair_body_pred1== "Negative";
% wordcloud(hair_body1(idx));
% title("Predicted Negative Sentiment")

figure
subplot(1,2,1)
idx = hair_body_pred5== "Positive";
wordcloud(hair_body5(idx));
title("Predicted Positive Sentiment of 5-stars")
subplot(1,2,2)
idx = hair_body_pred1== "Negative";
wordcloud(hair_body1(idx));
title("Predicted Negative Sentiment of 1-star")