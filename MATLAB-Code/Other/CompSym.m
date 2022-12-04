function CompSym
   syms x y b
   S1=(x^4) - (25*x^2) + 144
   S2=(x-3)^4
   S3=((x^2)-(3*x)-10)/(x+2)
   S4=((x^3)-(4/(x^9)))
   S5=(2*x)-(3*y) + (4*x) +(13*b)-(8*y)
   A=factor(S1)
   B=expand(S2)
   C=simplify(S3)
   D=diff(S4)
   E=collect(S5)
   F=int(S1)
   G=solve(S4)