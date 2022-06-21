function [pop] = initializega(num, bounds, evalFN,evalOps,options)

if nargin<5
  options=[1e-6 1];
end
if nargin<4
  evalOps=[];
end

if any(evalFN<48) 
  if options(2)==1 %Float GA
    estr=['x=pop(i,1); pop(i,xZomeLength)=', evalFN ';'];  
  else %Binary GA
    estr=['x=b2f(pop(i,:),bounds,bits); pop(i,xZomeLength)=', evalFN ';']; 
  end
else %A .m file
  if options(2)==1 %Float GA
    estr=['[ pop(i,:) pop(i,xZomeLength)]=' evalFN '(pop(i,:),[0 evalOps]);']; 
  else %Binary GA
    estr=['x=b2f(pop(i,:),bounds,bits);[x v]=' evalFN ...
	'(x,[0 evalOps]); pop(i,:)=[f2b(x,bounds,bits) v];'];  
    end
end


numVars     = size(bounds,1); 		%Number of variables
rng         = (bounds(:,2)-bounds(:,1))'; %The variable ranges'

if options(2)==1 %Float GA
  xZomeLength = numVars+1; 		%Length of string is numVar + fit
  pop         = zeros(num,xZomeLength); 	%Allocate the new population
  pop(:,1:numVars)=(ones(num,1)*rng).*(rand(num,numVars))+...
    (ones(num,1)*bounds(:,1)');
else %Binary GA
  bits=calcbits(bounds,options(1));
  xZomeLength = sum(bits)+1; 		%Length of string is numVar + fit
  pop = round(rand(num,sum(bits)+1));
end

for i=1:num
  eval(estr);
end
