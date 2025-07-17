function x=binom_coeff(n,k)
z=0;
index=1;
if lt(z,k)==1
    z=z+1;
    index=index*((n+1-z)/z);
end
x=index;