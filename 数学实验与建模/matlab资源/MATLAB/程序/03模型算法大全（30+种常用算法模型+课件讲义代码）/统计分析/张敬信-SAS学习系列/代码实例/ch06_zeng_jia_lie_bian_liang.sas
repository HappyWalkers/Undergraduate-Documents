data homegarden;
infile 'c:\MyRawData\Garden.dat';
input Name $ 1-7 Tomato Zucchini Peas Grapes;
Zone = 14;
Type = 'home';
Zucchini = Zucchini * 10;
Total = Tomato + Zucchini + Peas + Grapes;
PerTom = (Tomato / Total) * 100;
run;
proc print data = homegarden;
title 'Home Gardening Survey';
run;
