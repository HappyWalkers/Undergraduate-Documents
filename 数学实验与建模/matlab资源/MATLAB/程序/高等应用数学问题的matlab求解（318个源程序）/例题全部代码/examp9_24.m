r=normrnd(1,2,400,1); [H,p,ci]=ztest(r,1,2,0.02)

[H,p,ci]=ztest(r,0.5,2,0.02)

[H,p,ci]=ttest(r,1,0.02)
