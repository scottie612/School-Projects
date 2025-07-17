function[X1,X2]= quadroots(x1,x2,x3)
a=x1;
b=x2;
c=x3;
X=sqrt((b.^2)-4.*a.*c);
Y=b.^2;

X1=((-b+X)./Y).*log(8)-2;
X2=((-b-X)./Y).*log(8)-2;