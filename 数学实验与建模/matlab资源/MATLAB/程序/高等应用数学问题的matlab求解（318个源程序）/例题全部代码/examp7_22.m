lags=[1 0.5]; tx=dde23('c7exdde',lags,zeros(3,1),[0,10]);
plot(tx.x,tx.y(2,:))