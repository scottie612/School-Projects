

with open("test.hex",'r') as f:
    contents=f.read()
    nums=[x for x in contents.split()]
    print(nums)
    binaryval=[]
print("dst  src  mode  value")
print("=====================")
for i in range(len(nums)):
   
    binaryval=str(bin(int(nums[i][0],16))[2:].zfill(4))+str(bin(int(nums[i][1],16))[2:].zfill(4))+str(bin(int(nums[i][2],16))[2:].zfill(4))+str(bin(int(nums[i][3],16))[2:].zfill(4))
    operand1=binaryval[0:4]
    operand2=binaryval[4:8]
    mode=binaryval[8]
    value=binaryval[9:16]


    print('{:>2}'.format(int(operand1,2))," ",'{:>2}'.format(int(operand2,2))," ",'{:>2}'.format(mode),"",'{:>3}'.format(int(value,2)))
   
    
  
  
    

   











