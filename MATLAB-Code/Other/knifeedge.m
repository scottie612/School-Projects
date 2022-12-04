function x=knifeedge(v)
f_v=(1+.926.*v)./(2+1.792.*v+3.104.*v.^2);
g_v=1./(2+4.142.*v+3.492.*v.^2+6.670.*v.^3);

if v<0
    C_v=-1.*(.5+f_v.*sin((pi/2).*v.^2)-g_v.*cos((pi/2).*v.^2));
    S_v=-1.*(.5-f_v.*cos((pi/2).*v.^2)-g_v.*sin((pi/2).*v.^2));
else
    C_v=(.5+f_v.*sin((pi/2).*v.^2)-g_v.*cos((pi/2).*v.^2));
    S_v=(.5-f_v.*cos((pi/2).*v.^2)-g_v.*sin((pi/2).*v.^2));
end
    
    z=((1+j)/2).*((.5-C_v)-j.*(.5-S_v));
    x=20.*log10(z);