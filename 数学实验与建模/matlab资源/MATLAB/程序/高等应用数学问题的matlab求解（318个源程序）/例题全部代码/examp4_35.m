B=[1:4]'; C=[A B]; [rank(A), rank(C)]

x=pinv(A)*B

norm(A*x-B)

