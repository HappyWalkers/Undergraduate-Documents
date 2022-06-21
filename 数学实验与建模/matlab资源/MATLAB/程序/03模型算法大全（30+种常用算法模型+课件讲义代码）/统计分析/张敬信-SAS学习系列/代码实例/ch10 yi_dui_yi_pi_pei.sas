data descriptions;
infile 'c:\MyRawData\chocolate.dat' TRUNCOVER;
input CodeNum $ 1-4 Name $ 6-14 Description $ 15-60;
run;
data sales;
infile 'c:\MyRawData\chocsales.dat';
input CodeNum $ 1-4 PiecesSold 6-7;
proc sort data = sales;
by CodeNum;
run;
data chocolates;
merge sales descriptions;
by CodeNum;
run;
proc print data = chocolates;
title "Today's Chocolate Sales";
run;
