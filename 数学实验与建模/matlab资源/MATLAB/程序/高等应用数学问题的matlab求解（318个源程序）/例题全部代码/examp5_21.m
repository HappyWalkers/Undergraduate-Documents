syms z; f=(sin(z)-z)/z^6;
limit(diff(f*z^6,z,5)/prod(1:5),z,0)

syms z; f=(sin(z)-z)/z^6;
limit(diff(f*z^2,z,1)/prod(1:1),z,0)

limit(diff(f*z^3,z,2)/prod(1:2),z,0) % 再增加阶次

limit(diff(f*z^20,z,19)/prod(1:19),z,0) % 再进一步增加阶次