clear
close all

MCM_data='C:\Users\mashed potato\Desktop\MCM_data\scdata';
load(MCM_data);

time=1870:2019;
degree=scdata(1,1,:);
degree=reshape(degree,1,1800);

data=degree;
figure
plot(data)
xlabel("time")
ylabel("degree")
title("the degree of (65.5N,10.5W)")

numTimeStepsTrain = floor(0.9*numel(data));
dataTrain = data(1:numTimeStepsTrain+1);
dataTest = data(numTimeStepsTrain+1:end);

mu = mean(dataTrain);
sig = std(dataTrain);
dataTrainStandardized = (dataTrain - mu) / sig;

XTrain = dataTrainStandardized(1:end-1);
YTrain = dataTrainStandardized(2:end);

numFeatures = 1;
numResponses = 1;
numHiddenUnits = 175;
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
XTest = dataTestStandardized(1:end-1);

net = predictAndUpdateState(net,XTrain);
[net,YPred] = predictAndUpdateState(net,YTrain(end));

YPred_pra=dataTrainStandardized(1);
for i=2:size(dataTrain,2)
    [net,YPred_pra(:,i)]=predictAndUpdateState(net,YPred_pra(:,i-1),'ExecutionEnvironment','cpu');
end

numTimeStepsTest = numel(XTest);
for i = 2:numTimeStepsTest
    [net,YPred(:,i)] = predictAndUpdateState(net,YPred(:,i-1),'ExecutionEnvironment','cpu');
end

YPred = sig*YPred + mu;
YPred_pra = sig*YPred_pra + mu;

YTest = dataTest(2:end);
rmse = sqrt(mean((YPred-YTest).^2));
rmse_pra=sqrt(mean((YPred_pra-dataTrain).^2));

figure
plot(dataTrain(1:end-1))
hold on
idx = numTimeStepsTrain:(numTimeStepsTrain+numTimeStepsTest);
plot(idx,[data(numTimeStepsTrain) YPred],'.-')
hold off
xlabel("time")
ylabel("degree")
title("Forecast")
legend(["Observed" "Forecast"])

figure
subplot(2,1,1)
plot(dataTrain(1:end-1))
hold on
plot(YPred_pra);
hold off
xlabel("time")
ylabel("degree")
title("Forecast and Observed")
legend(["Observed" "Forecast"])
subplot(2,1,2)
stem(YPred_pra - dataTrain)
xlabel("time")
ylabel("Error")
title("RMSE = " + rmse_pra)

figure
subplot(2,1,1)
plot(YTest)
hold on
plot(YPred,'.-')
hold off
legend(["Observed" "Forecast"])
ylabel("degree")
title("Forecast")
subplot(2,1,2)
stem(YPred - YTest)
xlabel("time")
ylabel("Error")
title("RMSE = " + rmse)

