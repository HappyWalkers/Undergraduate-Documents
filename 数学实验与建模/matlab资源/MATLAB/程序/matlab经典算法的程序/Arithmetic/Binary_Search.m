function Binary_Search(L,a,b,x)%c����
begin
  if a>b then return(-1)
            else begin
                   m:=(a+b) div 2;
                   if x=L[m] then return(m)
                             else if x>L[m] 
                                    then return(Binary_Search(L,m+1,b,x));
                                    else return(Binary_Search(L,a,m-1,x));
                  end; 
end;<i