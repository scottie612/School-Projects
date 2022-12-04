import random
N = int(input("Please enter Number of students = "))
random.seed(N)
data=random.sample(range(100), N)
print('Data =', data)
print("Maximum = " + str(max(data)))
print("Minimum = " + str(min(data)))
mean = sum(data)/len(data)
print("Mean = " + str(mean))

print("Sorted = "+ str(sorted(data)))
index= len(data)//2
if len(data) % 2:
    median= sorted(data)[index]
else:
    median= sum(sorted(data)[index-1:index+1])/2
print("Median = " + str(median))
print("Grade distribution: ")
Grades=[0,0,0,0,0]
for i in range(len(data)):
    if data[i]>= 90:
        Grades[0]+=1
    elif data[i]>= 80 and data[i]< 90: 
        Grades[1]+=1
    elif data[i]>= 70 and data[i]< 80: 
        Grades[2]+=1
    elif data[i]>= 60 and data[i]< 70: 
        Grades[3]+=1
    else:
        Grades[4]+=1
print("A="+ str(Grades[0]) +" B="+ str(Grades[1]) +" C="+ str(Grades[2]) +" D="+ str(Grades[3]) +" F="+ str(Grades[4]))