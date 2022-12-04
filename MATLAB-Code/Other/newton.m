function x_n=newton(y,n,a,b)
x_n=rand(a,b);
f_x=y;
f_1x=diff(y(x));
for i=0:n
   
    x_n=x_n-(f_x/f_1x);
    x_n=eval(x_n);
    f_x=y;
    f_1x=diff(y(x));
  
end