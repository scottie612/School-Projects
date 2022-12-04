num1=input("Please enter an integer = ")
num=int(num1)
factors= []
times=[]
nums=[]
i = 2
while i <= num:     
    if num % i == 0:      
        factors.append(i)
        num//= i
    else:
        i+=1
        
print("Result: " + num1 + " = ", end= " ")

for i in range(len(factors)):

   if factors[i]!=factors[i-1]:         
       nums.append(factors[i])
      
for i in range(len(nums)):
   times.append( factors.count(nums[i]))
   print(str(nums[i]) + "^" + str(times[i]), end =" ")
   if i != len(nums)-1:
       print("*",end =" ")