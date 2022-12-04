function h=fn_sin(x,n)
h = 0;
for k = 0:n-1
      h = h + (-1).^k * x.^(2*k+1)/factorial(2*k+1);
end
