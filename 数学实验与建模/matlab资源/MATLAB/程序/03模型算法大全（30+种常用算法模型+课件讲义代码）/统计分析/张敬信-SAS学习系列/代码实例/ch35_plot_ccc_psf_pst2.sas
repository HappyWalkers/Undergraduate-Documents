data vital;
infile 'C:\MyRawData\populations.txt';
input country $19. birth death;
run;
proc cluster data = vital out=tree method = average print = 15 ccc pseudo;
var birth death;
title1 'Cluster Analysis of Birth and Death Rates in 74 Countries';
run;
proc print data=tree;
title 'tree';
run;
proc sort data=tree;
by _ncl_;
goptions reset=global gunit=pct cback=white border htitle=6 htext=3 ftext=swissb colors=(back);
proc gplot data=tree;
plot  _ccc_*_ncl_ / haxis = axis1 vaxis = axis2;
plot2 _psf_*_ncl_  _pst2_*_ncl_ / vaxis = axis3 overlay;
symbol1 i=join v='C' l=3 h=2.5 w=1.5;
symbol2 i=join v='F' l=1 h=2.5 w=1.5;
symbol3 i=join v='T' l=1 h=2.5 w=1.5;
axis1 label = ('Number of Clusters')  order=(1 to 15  by 1) ;
axis2 label = ('CCC')                 order=(0 to 6   by 0.5);
axis3 label = ('PSF and PST2')        order=(0 to 300 by 25);
title2  "Plot of _CCC_ *_NCL_.  Symbol used is 'C' ";
title3  "Plot of _PSF_ *_NCL_.  Symbol used is 'F' ";
title4  "Plot of _PST2_*_NCL_.  Symbol used is 'T' ";
run;
