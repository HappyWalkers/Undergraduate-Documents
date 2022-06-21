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
textdata={hair_tit,micro_tit,pacifier_tit,hair_body,micro_body,pacifier_body};

documents=preprocessTextData(textdata{1});
bag=bagOfWords(documents);
bag = removeInfrequentWords(bag,2);
bag = removeEmptyDocuments(bag);
numTopics = 3;
mdl = fitlda(bag,numTopics,'Verbose',0);
figure;
for topicIdx = 1:numTopics
    subplot(numTopics,1,topicIdx)
    wordcloud(mdl,topicIdx);
    title("Topic " + topicIdx)
end

% for i=1:6
%     documents=preprocessTextData(textdata{i});
%     bag=bagOfWords(documents);
%     bag = removeInfrequentWords(bag,2);
%     bag = removeEmptyDocuments(bag);
%     numTopics = 5;
%     mdl = fitlda(bag,numTopics,'Verbose',0);
%     figure;
%     for topicIdx = 1:numTopics
%         subplot(numTopics,1,topicIdx)
%         wordcloud(mdl,topicIdx);
%         title("Topic " + topicIdx)
%     end
% end
