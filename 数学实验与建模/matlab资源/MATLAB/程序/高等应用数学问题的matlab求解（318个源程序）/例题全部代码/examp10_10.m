net=newff([0,1; -1,5],[8,1],{'tansig','logsig'});

net=newff([0,1; -1,5],[4 6 1],{'purelin','tansig','logsig'});

net.trainParam.epochs=300; net.trainFcn='trainlm'