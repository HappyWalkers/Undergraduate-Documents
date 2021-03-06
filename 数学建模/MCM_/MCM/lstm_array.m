clear
close all

MCM_data='C:\Users\mashed potato\Desktop\MCM_data\scdata';
load(MCM_data);

time=1870:2019;
data=scdata;
data(data<0)=nan;
data=reshape(data,16*11,1800);
del=[45 46 60:62 76 77 105:107 122 123 126 139 ...
    140:143 156:159 173:175];
data(del,:)=[];

numTimeStepsTrain=floor(0.9*size(data,2));
dataTrain=data(:,1:numTimeStepsTrain+1);
dataTest = data(:,numTimeStepsTrain+1:end);

mu = mean(dataTrain,'all','omitnan');
sig = std(dataTrain,0,'all','omitnan');
dataTrainStandardized = (dataTrain - mu) / sig;

XTrain = dataTrainStandardized(:,1:end-1);
YTrain = dataTrainStandardized(:,2:end);

numFeatures = 151;
numResponses =151;
numHiddenUnits = 15;
layers = [ ...
    sequenceInputLayer(numFeatures)
    lstmLayer(numHiddenUnits)
    fullyConnectedLayer(numResponses)
    regressionLayer];

options = trainingOptions('adam', ...
    'MaxEpochs',200, ...
    'GradientThreshold',1, ...
    'InitialLearnRate',0.005, ...
    'LearnRateSchedule','piecewise', ...
    'LearnRateDropPeriod',125, ...
    'LearnRateDropFactor',0.2, ...
    'Verbose',0, ...
    'Plots','training-progress');

net = trainNetwork(XTrain,YTrain,layers,options);

dataTestStandardized = (dataTest - mu) / sig;
XTest = dataTestStandardized(:,1:end-1);

net = predictAndUpdateState(net,XTrain);
[net,YPred] = predictAndUpdateState(net,YTrain(:,end));

YPred_pra=dataTrainStandardized(:,1);
for i=2:size(dataTrain,2)
    [net,YPred_pra(:,i)]=predictAndUpdateState(net,YPred_pra(:,i-1),'ExecutionEnvironment','cpu');
end

numTimeStepsTest = size(XTest,2);
for i = 2:numTimeStepsTest
    [net,YPred(:,i)] = predictAndUpdateState(net,YPred(:,i-1),'ExecutionEnvironment','cpu');
end


YPred = sig*YPred + mu;
YPred_pra = sig*YPred_pra + mu;

YTest = dataTest(:,2:end);
rmse = sqrt(mean((YPred-YTest).^2));
rmse_pra=sqrt(mean((YPred_pra-dataTrain).^2));

figure
plot(dataTrain(2,1:end-1),'.-')
hold on
idx = numTimeStepsTrain:(numTimeStepsTrain+numTimeStepsTest);
plot(idx,[data(numTimeStepsTrain) YPred(2,:)],'.-')
hold off
xlabel("time")
ylabel("degree")
title("Forecast")
legend(["Observed" "Forecast"])

figure
subplot(2,1,1)
plot(dataTrain(2,1:end-1))
hold on
plot(YPred_pra(2,:));
hold off
xlabel("time")
ylabel("degree")
title("Forecast and Observed")
legend(["Observed" "Forecast"])
subplot(2,1,2)
stem(YPred_pra(2,:) - dataTrain(2,:))
xlabel("time")
ylabel("Error")
title("RMSE = " + rmse_pra(2))

figure
subplot(2,1,1)
plot(YTest(2,:))
hold on
plot(YPred(2,:),'.-')
hold off
legend(["Observed" "Forecast"])
ylabel("degree")
title("Forecast")
subplot(2,1,2)
stem(YPred(2,:) - YTest(2,:))
xlabel("time")
ylabel("Error")
title("RMSE = " + rmse(2))