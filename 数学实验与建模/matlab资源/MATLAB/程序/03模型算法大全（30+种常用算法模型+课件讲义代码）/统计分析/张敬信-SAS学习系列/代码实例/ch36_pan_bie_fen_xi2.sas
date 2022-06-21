data newiris (drop=species);
set iris;
run;
proc print data=plotdata;
run;
proc discrim data=iris testdata=newiris testout=plotp testoutd=plotd method=normal pool=yes short noclassify crosslisterr;
class species;
var petallen ;
title2 'Using Normal Density Estimates with Equal Variance';
run;
proc discrim data=iris testdata=newiris testout=plotp testoutd=plotd method=normal pool=no short noclassify crosslisterr;
class species;
var petallen ;
title2 'Using Normal Density Estimates with Unequal Variance';
run;
proc print data=plotp;
run;
proc print data=plotd;
run;
proc discrim data=iris testdata=newiris testout=plotp testoutd=plotd method=npar kernel=normal r=.4 pool=yes short noclassify crosslisterr;
class species;
var petallen ;
title2 'Using Kernel Density Estimates with Equal Bandwidth';
run;
proc discrim data=iris testdata=newiris testout=plotp testoutd=plotd method=npar kernel=normal r=.4 pool=no short noclassify crosslisterr;
class species;
var petallen ;
title2 'Using Kernel Density Estimates with Unequal Bandwidth';
run;
