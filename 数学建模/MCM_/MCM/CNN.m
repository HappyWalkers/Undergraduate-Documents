clear

MCM_data='C:\Users\mashed potato\Desktop\MCM_data\scdata';
load(MCM_data);

scdata(scdata<0)=nan;
data=scdata;

data=reshape(data,[16 11 1 1800]);

numTrainImages=floor(0.9*size(data,3));
dataTrain=data(:,:,:,1:numTrainImages+1);
dataTest = data(:,:,:,numTrainImages+1:end);

mu = mean(dataTrain,'all','omitnan');
sig = std(dataTrain,0,'all','omitnan');
dataTrainStandardized = (dataTrain - mu) / sig;

XTrain = dataTrainStandardized(:,:,:,1:end-1);
YTrain = dataTrainStandardized(:,:,:,2:end);

% numTrainImages = size(YTrain,3);
figure
idx = randperm(numTrainImages,20);
for i = 1:numel(idx)
    subplot(4,5,i)    
    imshow(dataTrain(:,:,:,idx(i)))
    drawnow
end

% figure
% histogram(YTrain)
% axis tight
% ylabel('Counts')
% xlabel('Rotation Angle')

layers = [
    imageInputLayer([16 11 1])

    convolution2dLayer(3,8,'Padding','same')
    batchNormalizationLayer
    reluLayer
    
    averagePooling2dLayer(2,'Stride',2)

    convolution2dLayer(3,16,'Padding','same')
    batchNormalizationLayer
    reluLayer
    
    averagePooling2dLayer(2,'Stride',2)
  
    convolution2dLayer(3,32,'Padding','same')
    batchNormalizationLayer
    reluLayer
    
    convolution2dLayer(3,32,'Padding','same')
    batchNormalizationLayer
    reluLayer
    
    dropoutLayer(0.2)
    fullyConnectedLayer(1)
    regressionLayer];

miniBatchSize  = 128;
validationFrequency = floor(size(data,3)/miniBatchSize);
options = trainingOptions('sgdm', ...
    'MiniBatchSize',miniBatchSize, ...
    'MaxEpochs',30, ...
    'InitialLearnRate',1e-3, ...
    'LearnRateSchedule','piecewise', ...
    'LearnRateDropFactor',0.1, ...
    'LearnRateDropPeriod',20, ...
    'Shuffle','every-epoch', ...
    'ValidationData',{XValidation,YValidation}, ...
    'ValidationFrequency',validationFrequency, ...
    'Plots','training-progress', ...
    'Verbose',false);

net = trainNetwork(data,data,layers,options);