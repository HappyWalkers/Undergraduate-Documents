f1=figure; f2=figure;
for n=5:2:20
    figure(f1); [b,a]=butter(n,0.1); y2=filter(b,a,y1); plot(x,y2); hold on
    figure(f2); [h,w]=freqz(b,a,100); plot(w,abs(h)); hold on
end

for wn=0.1:0.1:0.7
    figure(f1); [b,a]=butter(7,wn); y2=filter(b,a,y1); plot(x,y2); hold on
    figure(f2); [h,w]=freqz(b,a,100); plot(w,abs(h)); hold on
end