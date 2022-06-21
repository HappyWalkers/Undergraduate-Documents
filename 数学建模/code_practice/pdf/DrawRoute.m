function DrawRoute(C,R)
    N=length(R);
    scatter(C(:,1),C(:,2));
    hold on
    plot([C(R(1),1),C(R(N),1)],[C(R(1),2),C(R(N),2)],'r')
    hold on
    for ii=2:N plot([C(R(ii-1),1),C(R(ii),1)],[C(R(ii-1),2),C(R(ii),2)],'r')
        hold on
    end
    hold on
    plot(C(1,1),C(1,2),'-*k')
    ylabel('The abscissa of the grid')
    xlabel('The ordinate of the grid')
    set(gca,'XAxisLocation','top');
    set(gca,'YDir','reverse');
    title('Optimization results of drone detection path ')