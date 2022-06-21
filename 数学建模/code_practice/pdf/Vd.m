a=[   
    12,52    
    4,50 
    8,48
    21,49
    11,57 
    11,60 
    19,54 
    21,54  
    20,56  
    23,62];
x=[52 50 48 49 57 60 54 54 56 62] ;
y=[12 4 8 21 11 11 19 21 20 23] ;
voronoi(x,y) 
hold on
plot(61,15,'-xr',61,25,'-*k',57,6,'-*k',51,11,'-*k') 
legend('Obstacles','Safest route','Starting point','Destination')
ylabel('The abscissa of the grid') 
xlabel('The ordinate of the grid') 
set(gca,'XAxisLocation','top');
 set(gca,'YDir','reverse');