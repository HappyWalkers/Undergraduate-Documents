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
%%  ��һ�������򻯣���С�͡��м��͡�������ת�����ͣ�

[n,m] = size(X);

disp(['����' num2str(n) '�����۶���, ' num2str(m) '������ָ��']) 

Judge = input(['��' num2str(m) '��ָ���Ƿ���Ҫ�������򻯴�����Ҫ������1 ������Ҫ����0��  ']);

if Judge == 1

    Position = input('��������Ҫ���򻯴����ָ�����ڵ��У������2��3��6������Ҫ������ô����Ҫ����[2,3,6]�� '); %[2,3,4]

    disp('��������Ҫ�������Щ�е�ָ�����ͣ�1����С�ͣ� 2���м��ͣ� 3�������ͣ� ')

    Type = input('���磺��2���Ǽ�С�ͣ���3���������ͣ���6�����м��ͣ�������[1,3,2]��  '); %[2,1,3]

        for i = 1 : size(Position,2)  %������Ҫ����Щ�зֱ������������Ҫ֪��һ��Ҫ����Ĵ�������ѭ���Ĵ���

            X(:,Position(i)) = Positivization(X(:,Position(i)),Type(i),Position(i));

        end

    disp('���򻯺�ľ��� X =  ')

    disp(X)

end

%%  �ڶ����������򻯾����׼��

Z = X ./ repmat(sum(X.*X) .^ 0.5, n, 1);

disp('��׼������ Z = ')

disp(Z)

%%  �����������������ֵ����Сֵ�ľ��룬������÷�

D_P = sum([(Z - repmat(max(Z),n,1)) .^ 2 ],2) .^ 0.5;   % D+ �����ֵ�ľ�������

D_N = sum([(Z - repmat(min(Z),n,1)) .^ 2 ],2) .^ 0.5;   % D- ����Сֵ�ľ�������

S = D_N ./ (D_P+D_N);    % δ��һ���ĵ÷�

disp('���ĵ÷�Ϊ��')

stand_S = S / sum(S)

[sorted_S,index] = sort(stand_S ,'descend');

disp('��׼����÷�Ϊ��')

disp(sorted_S)

disp('��Ӧ���±�Ϊ:')

disp(index)

