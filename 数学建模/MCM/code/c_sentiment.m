clear
close all

opts = detectImportOptions('C:\Users\mashed potato\Desktop\MCM\data\NandYandProduct\hair_pro5.xlsx');
opts.Sheet='Sheet1';
hair_pro=readtable('C:\Users\mashed potato\Desktop\MCM\data\NandYandProduct\hair_pro5.xlsx',opts,'ReadRowNames',true);

hair_body=hair_pro.review_body;
hair_tit=hair_pro.review_headline;

hair_bodys="";
hair_tits="";
hair_num=size(hair_body,1);
for i=1:hair_num
    hair_bodys(i)=hair_body{i};
    hair_tits(i)=hair_tit{i};
end
hair_doc = preprocessText(hair_bodys);
emb = fastTextWordEmbedding;
idx = ~isVocabularyWord(emb,hair_doc.Vocabulary);
hair_doc = removeWords(hair_doc,idx);

data = readLexicon;
idx = ~isVocabularyWord(emb,data.Word);
data(idx,:) = [];
numWords = size(data,1);
cvp = cvpartition(numWords,'HoldOut',0.1);
dataTrain = data(training(cvp),:);
wordsTrain = dataTrain.Word;
words = hair_doc.Vocabulary;
words(ismember(words,wordsTrain)) = [];

XTrain = word2vec(emb,wordsTrain);
YTrain = dataTrain.Label;
mdl = fitcsvm(XTrain,YTrain);
vec = word2vec(emb,words);
[YPred,scores] = predict(mdl,vec);

figure
subplot(1,2,1)
idx = YPred == "Positive";
wordcloud(words(idx),scores(idx,1));
title("Predicted Positive Sentiment")

subplot(1,2,2)
wordcloud(words(~idx),scores(~idx,2));
title("Predicted Negative Sentiment")

sentimentScore_1=zeros(1,1);
for i = 1:hair_num
    words = string(hair_doc(i));
    vec = word2vec(emb,words);
    [~,scores] = predict(mdl,vec);
    sentimentScore_1(i) = mean(scores(:,1));%score
end

figure
plot(sentimentScore_1,'.');
title("The sentiment score of hair dryer review");
xlabel('review');
ylabel('score');

%length
body_length=zeros(1,1);
tit_length=zeros(1,1);
for i=1:hair_num
    body_length(i)=length(hair_body{i});
    tit_length(i)=length(hair_body{i});
end
length_1=body_length+tit_length;

all_sentiment=sentimentScore_1.*length_1;
ave_sentiment_1=mean(all_sentiment,'omitnan');
save('C:\Users\mashed potato\Desktop\MCM\data\sentiment\sentiment_1','ave_sentiment_1');
save('C:\Users\mashed potato\Desktop\MCM\data\d\data_1','length_1','sentimentScore_1');