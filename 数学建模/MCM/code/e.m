clear
close all

%以ReviewID作为主键，需要清洗
hair_pre=readtable('C:\Users\mashed potato\Desktop\MCM\data\NandY\hair_dryer.xlsx','ReadRowNames',true);%懒得改变量名了
micro_pre=readtable('C:\Users\mashed potato\Desktop\MCM\data\NandY\micro_wave.xlsx','ReadRowNames',true);
pacifier_pre=readtable('C:\Users\mashed potato\Desktop\MCM\data\NandY\pacifier.xlsx','ReadRowNames',true);

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

hair_body=strjoin(hair_body);
 hair_body=preprocessTextData(hair_body);
hair_body=doc2cell(hair_body);
hair_body=hair_body{1};
hair_body=reshape(hair_body,[size(hair_body,2),size(hair_body,1)]);

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
hair_body_test = word2vec(emb,hair_body);
[hair_body_pred,hair_body_scores]=predict(mdl,hair_body_test);

% figure
% confusionchart(YTest,YPred);

figure
subplot(1,2,1)
idx = hair_body_pred== "Positive";
% wordcloud(wordsTest(idx),scores(idx,1));
% wordcloud(hair_body(idx),hair_body_scores(idx,1));
wordcloud(hair_body(idx));
title("Predicted Positive Sentiment")

subplot(1,2,2)
% wordcloud(wordsTest(~idx),scores(~idx,2));
idx = hair_body_pred== "Negative";
% wordcloud(hair_body(idx),hair_body_scores(idx,2));
wordcloud(hair_body(idx));
title("Predicted Negative Sentiment")