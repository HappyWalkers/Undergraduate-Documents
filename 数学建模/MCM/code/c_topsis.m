clear
close all

load('C:\Users\mashed potato\Desktop\MCM\data\reputation\reputation_1');
load('C:\Users\mashed potato\Desktop\MCM\data\reputation\reputation_2');
load('C:\Users\mashed potato\Desktop\MCM\data\reputation\reputation_3');
load('C:\Users\mashed potato\Desktop\MCM\data\reputation\reputation_4');
load('C:\Users\mashed potato\Desktop\MCM\data\sentiment\sentiment_1');
load('C:\Users\mashed potato\Desktop\MCM\data\sentiment\sentiment_2');
load('C:\Users\mashed potato\Desktop\MCM\data\sentiment\sentiment_3');
load('C:\Users\mashed potato\Desktop\MCM\data\sentiment\sentiment_4');

X=[ave_reputation_1,ave_sentiment_1;ave_reputation_2,ave_sentiment_2;...
    ave_reputation_3,ave_sentiment_3;ave_reputation_4,ave_sentiment_4];
%%  第一步：正向化（极小型、中间型、区间型转极大型）

[n,m] = size(X);

disp(['共有' num2str(n) '个评价对象, ' num2str(m) '个评价指标']) 

Judge = input(['这' num2str(m) '个指标是否需要经过正向化处理，需要请输入1 ，不需要输入0：  ']);

if Judge == 1

    Position = input('请输入需要正向化处理的指标所在的列，例如第2、3、6三列需要处理，那么你需要输入[2,3,6]： '); %[2,3,4]

    disp('请输入需要处理的这些列的指标类型（1：极小型， 2：中间型， 3：区间型） ')

    Type = input('例如：第2列是极小型，第3列是区间型，第6列是中间型，就输入[1,3,2]：  '); %[2,1,3]

        for i = 1 : size(Position,2)  %这里需要对这些列分别处理，因此我们需要知道一共要处理的次数，即循环的次数

            X(:,Position(i)) = Positivization(X(:,Position(i)),Type(i),Position(i));

        end

    disp('正向化后的矩阵 X =  ')

    disp(X)

end

%%  第二步：对正向化矩阵标准化

Z = X ./ repmat(sum(X.*X) .^ 0.5, n, 1);

disp('标准化矩阵 Z = ')

disp(Z)

%%  第三步：计算与最大值和最小值的距离，并计算得分

D_P = sum([(Z - repmat(max(Z),n,1)) .^ 2 ],2) .^ 0.5;   % D+ 与最大值的距离向量

D_N = sum([(Z - repmat(min(Z),n,1)) .^ 2 ],2) .^ 0.5;   % D- 与最小值的距离向量

S = D_N ./ (D_P+D_N);    % 未归一化的得分

disp('最后的得分为：')

stand_S = S / sum(S)

[sorted_S,index] = sort(stand_S ,'descend');

disp('标准化后得分为：')

disp(sorted_S)

disp('对应的下标为:')

disp(index)

