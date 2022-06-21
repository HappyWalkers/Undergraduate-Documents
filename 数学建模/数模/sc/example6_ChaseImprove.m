close all
clear
clc

v=1;
dt=0.0001;
epsilon = 0.1;
x=[0 0 10 10];
y=[0 10 10 0];
d = inf;

tic
N = ceil(pi*max(x)/(2*v*dt));
X = zeros(N, 5);
Y = zeros(N, 5);

j = 1;
X(j,1:4) = x;
Y(j,1:4) = y;
X(j,5) = X(j,1);
Y(j,5) = Y(j,1);

while(d>epsilon)
    j = j + 1;
    X(j,:) = X(j-1,:);
    Y(j,:) = Y(j-1,:);
    for i=1:4
        d=sqrt((X(j,i+1)-X(j,i))^2+(Y(j,i+1)-Y(j,i))^2);
        X(j,i)=X(j,i)+v*dt*(X(j,i+1)-X(j,i))/d;
        Y(j,i)=Y(j,i)+v*dt*(Y(j,i+1)-Y(j,i))/d;
    end
    X(j,5) = X(j,1);
    Y(j,5) = Y(j,1);
end
X = X(1:j,:);
Y = Y(1:j,:);

figure;
plot(X(:,1), Y(:,1),'-k.');
hold on;
plot(X(:,2), Y(:,2),'-r.');
plot(X(:,3), Y(:,3),'-b.');
plot(X(:,4), Y(:,4),'-y.');
toc


