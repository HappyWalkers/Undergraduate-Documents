maple('with(numtheory):'); f=maple(['cfe:=cfrac(pi,20)'])

n=maple('nthnumer','cfe',4); d=maple('nthdenom','cfe',4); [vpa(n),vpa(d)]
