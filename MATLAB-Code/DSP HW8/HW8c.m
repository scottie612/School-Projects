A1=[1,1,1];
A=A1'*A1
rank(A)

A2=[1 2 1];
A=A2'*A2
rank(A)

for w=0:4
    for h=0:4
        A3(w+1,h+1)=w+h;
    end
end
A3

rank(A3)