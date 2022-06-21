function data = readLexicon

% Read positive words
fidPositive = fopen('C:\Users\mashed potato\Desktop\MCM\data\opinion-lexicon-English\positive-words.txt');
C = textscan(fidPositive,'%s','CommentStyle',';');
wordsPositive = string(C{1});

% Read negative words
fidNegative = fopen('C:\Users\mashed potato\Desktop\MCM\data\opinion-lexicon-English\negative-words.txt');
C = textscan(fidNegative,'%s','CommentStyle',';');
wordsNegative = string(C{1});
fclose all;

% Create table of labeled words
words = [wordsPositive;wordsNegative];
labels = categorical(nan(numel(words),1));
labels(1:numel(wordsPositive)) = "Positive";
labels(numel(wordsPositive)+1:end) = "Negative";

data = table(words,labels,'VariableNames',{'Word','Label'});

end