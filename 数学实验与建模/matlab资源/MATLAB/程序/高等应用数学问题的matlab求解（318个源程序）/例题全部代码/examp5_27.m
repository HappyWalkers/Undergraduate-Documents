syms s
G=(2*s^7+2*s^3+8)/...   % 其中 ... 表示续行
    (s^8+30*s^7+386*s^6+2772*s^5+12093*s^4+32598*s^3+52520*s^2+45600*s+16000);
f=residue1(G); latex(f)

simple(f-G)
