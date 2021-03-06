data southentrance;
infile 'c:\MyRawData\South.dat';
input Entrance $ PassNumber PartySize Age;
proc print data = southentrance;
title 'South Entrance Data';
run;
data northentrance;
infile 'c:\MyRawData\North.dat';
input Entrance $ PassNumber PartySize Age Lot;
proc sort data = northentrance;
by PassNumber;
proc print data = northentrance;
title 'North Entrance Data';
run;
* Interleave observations by PassNumber;
data sortbothentrance;
set northentrance southentrance;
by PassNumber;
run;
proc print data = sortbothentrance;
title 'Both Entrances, By Pass Number';
run;
