options=odeset; options.Mass=@c7eqdae2; options.RelTol=1e-6;
      [t,x]=ode45(@c7fimp2,[0,10],[0;0],options); plot(t,x)