function [final]=rest(n,ohms)
resistances=[];
Rn=ohms;
resistances(1)=Rn;
for i=2:n
    resistances(i)=(resistances(i-1)*ohms)/(resistances(i-1)+ohms);
  
end
final=resistances;
x=[1:1:n];
plot(x,final);