format long; H=hilb(4); H1=inv(H)

H*H1

norm(H*inv(H)-eye(size(H)))

H2=invhilb(4); norm(H*H2-eye(size(H)))

H=hilb(10); H1=inv(H); norm(H*H1-eye(size(H)))

H2=invhilb(10); norm(H*H2-eye(size(H)))

H=hilb(13); H1=inv(H); norm(H*H1-eye(size(H)))

H2=invhilb(13); norm(H*H2-eye(size(H)))

H=sym(hilb(7)); inv(H)

H=sym(hilb(30)); norm(double(H*inv(H)-eye(size(H))))