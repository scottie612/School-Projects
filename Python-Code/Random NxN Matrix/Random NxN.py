import numpy as np
N = int(input("For a NxN matrix enter N = "))
np.random.seed(N)
A = np.random.randint(100, size=(N, N))
print('A = ', A) 
A=np.reshape(A,-1)
B=A
A=np.sort(A)
zeros=0
top25= round(.75 * len(A))
for i in range(len(B)):
    if B[i]< A[top25]:
        B[i]=0
        zeros+=1

B=np.reshape(B,(N,N))
print('Big A = ', B) 
print('Zeros = ', zeros)