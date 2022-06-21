clc
clear
close all
% load('usborder.mat','x','y','xx','yy');
Coord=xlsread("C:\Users\mashed potato\Desktop\校赛\附件1.xlsx");
stopsLon=Coord(:,1);
stopsLat=Coord(:,2);
nStops=length(stopsLon);
% rng(3,'twister') % Makes stops in Maine & Florida, and is reproducible
% nStops = 200; % You can use any number, but the problem size scales as N^2
% stopsLon = zeros(nStops,1); % Allocate x-coordinates of nStops
% stopsLat = stopsLon; % Allocate y-coordinates
% n = 1;
% while (n <= nStops)
%     xp = rand*0.5+120.5;
%     yp = rand*0.1+36.3;
%     if inpolygon(xp,yp,x,y) % tTest if inside the border
%         stopsLon(n) = xp;
%         stopsLat(n) = yp;
%         n = n+1;
%     end
% end
idxs = nchoosek(1:nStops,2);
% dist = hypot(stopsLat(idxs(:,1)) - stopsLat(idxs(:,2)), ...
%              stopsLon(idxs(:,1)) - stopsLon(idxs(:,2)));
longitude=stopsLon*pi/180;
latitude=stopsLat*pi/180;
R=6371;
jiao=acos( cos(latitude(idxs(:,2))) .* cos(latitude(idxs(:,1))) .* cos(longitude(idxs(:,1)) - longitude(idxs(:,2)) ) + sin( latitude(idxs(:,1))) .* sin( latitude(idxs(:,2)) ));
dist=R*jiao;
lendist = length(dist);
G = graph(idxs(:,1),idxs(:,2));
figure
hGraph = plot(G,'XData',stopsLon,'YData',stopsLat,'LineStyle','none','NodeLabel',{});
xlabel('经度');
ylabel('纬度');
% hold on
% Draw the outside border
% plot(x,y,'r-')
% hold off
tsp = optimproblem;
trips = optimvar('trips',lendist,1,'Type','integer','LowerBound',0,'UpperBound',1);
tsp.Objective = dist'*trips;
constr2trips = optimconstr(nStops,1);
for stop = 1:nStops
    whichIdxs = outedges(G,stop); % Identify trips associated with the stop
    constr2trips(stop) = sum(trips(whichIdxs)) == 2;
end
tsp.Constraints.constr2trips = constr2trips;
opts = optimoptions('intlinprog','Display','off');
tspsol = solve(tsp,'options',opts)
tspsol.trips = logical(round(tspsol.trips));
Gsol = graph(idxs(tspsol.trips,1),idxs(tspsol.trips,2));
hold on
highlight(hGraph,Gsol,'LineStyle','-')
title('Solution with Subtours')
tourIdxs = conncomp(Gsol);
numtours = max(tourIdxs); % Number of subtours
fprintf('# of subtours: %d\n',numtours);
% Index of added constraints for subtours
k = 1;
while numtours > 1 % Repeat until there is just one subtour
    % Add the subtour constraints
    for ii = 1:numtours
        inSubTour = (tourIdxs == ii); % Edges in current subtour
        a = all(inSubTour(idxs),2); % Complete graph indices with both ends in subtour
        constrname = "subtourconstr" + num2str(k);
        tsp.Constraints.(constrname) = sum(trips(a)) <= (nnz(inSubTour) - 1);
        k = k + 1;        
    end
    
    % Try to optimize again
    [tspsol,fval,exitflag,output] = solve(tsp,'options',opts);
    tspsol.trips = logical(round(tspsol.trips));
    Gsol = graph(idxs(tspsol.trips,1),idxs(tspsol.trips,2));
    
    % Plot new solution
    hGraph.LineStyle = 'none'; % Remove the previous highlighted path
    highlight(hGraph,Gsol,'LineStyle','-')
    drawnow

    % How many subtours this time?
    tourIdxs = conncomp(Gsol);
    numtours = max(tourIdxs); % Number of subtours
    fprintf('# of subtours: %d\n',numtours)    
end
% title('Solution with Subtours Eliminated');
% title(['minimum distance is: ',num2str(fval),' km']);
title(['最小距离是: ',num2str(fval),' km']);
hold off
disp(output.absolutegap)
% myplot(