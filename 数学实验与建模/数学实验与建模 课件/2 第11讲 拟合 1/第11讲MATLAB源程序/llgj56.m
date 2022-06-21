t=[0 0.92 1.84 2.95 3.87 4.98 5.9 7.01 7.93 8.97 10.95 12.03 12.95 13.88 14.98 15.90 16.83 17.93 19.04 19.9 20.84 23.88 24.99 25.91];
h=[968 948 931 913 898 881 869 852 839 822 1082 1050 1021 994 965 941 918 892 866 843 822 1059 1035 1018];
c1=polyfit(t(1:10),h(1:10),5)
a1=polyder(c1)
tp1=0:0.1:9;
x1=-polyval(a1,tp1);
plot(tp1,x1,'c.')
axis([0 25 12  34])
hold on
c2=polyfit(t(10.9:21),h(10.9:21),6);
a2=polyder(c2);
tp2=10.9:0.1:21;
x2=-polyval(a2,tp2);
plot(tp2,x2,'c.')
axis([0 25 12  34])
hold on
xx1=-polyval(a1,[8 9]);
xx2=-polyval(a2,[11 12]);
xx12=[xx1 xx2];
c12=polyfit([8 9 11 12],xx12,5)
tp12=9:0.1:11;
x12=polyval(c12,tp12);
plot(tp12,x12,'c.')
axis([0 25 12  34])
hold on
dt3=diff(t(22:24));
dh3=diff(h(22:24));
dht3=-dh3./dt3;
t3=[20 20.8 t(22) t(23)]
xx3=[-polyval(a2,t3(1:2)),dht3];
c3=[-polyfit(t3,xx3,5)];
tp3=20.8:0.1:24;
x3=-polyval(c3,tp3);
plot(tp3,x3,'c.')
axis([0 25 12  34])
xlabel('hour')
ylabel('cm/houor')