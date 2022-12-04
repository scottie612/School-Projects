function n=rgiven(R,m)
Rn=R;
n=1;

while (Rn > 10^(-1*m))
    Rn=((Rn*R)/(Rn+R));
    n=n+1;
end

