data vital;
infile 'C:\MyRawData\populations.txt';
title 'Crude Birth and Death Tates in 1976';
input country $19. birth death;
run;
proc print data = vital;
run;
proc plot formchar='|-----|--' hpct=100 vpct=100;
plot death*birth / hpos=86 vpos=26;
run;
proc cluster data = vital out=tree method = average print = 15 ccc pseudo;
var birth death;
title 'Cluster Analysis of Birth and Death Rates in 74 Countries';
run;
proc tree data = tree noprint out = out ncl = 8;
copy birth death;
run;
proc plot formchar='|-----|--';
plot death*birth = cluster / hpos=86 vpos=26;
title2 'Plot of  Clusters Form Method = Average';
run;
