int n;
double f(int n)
{int i;double t,s;
t=1;s=1;
for(i=1;i<n;i++)
{t=(t+1)/t;s=s+t;}
return (s);
}