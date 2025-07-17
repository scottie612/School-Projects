function [EX,EY,EZ]=coulmbseq(Q0,x1,y1,z1,x0,y0,z0)

R=sqrt(((x1-x0).^2)+((y1-y0).^2)+((z1-z0).^2));

E0=-8.8541881*10^(-12);

EX=(Q0/(4*pi*E0))*((x1-x0)/(R.^3));
EY=(Q0/(4*pi*E0))*((y1-y0)/(R.^3));
EZ=(Q0/(4*pi*E0))*((z1-z0)/(R.^3));