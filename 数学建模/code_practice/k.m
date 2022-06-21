function y = k(x1,x2)
    y = exp(-0.5*norm(x1 - x2).^2);
end