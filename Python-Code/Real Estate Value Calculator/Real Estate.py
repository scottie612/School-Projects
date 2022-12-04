
def showlist(x):
    x.sort()
    for i in x:
        print("$","{:.2f}".format(i));
def median(x):
    sorted_list = sorted(x)
    length = len(sorted_list)
    center = length // 2
    if length == 1:
        return sorted_list[0]
    elif length % 2 == 0:
        return sum(sorted_list[center - 1: center + 1]) / 2.0
    else:
        return sorted_list[center]
def average(x):
    sum=0
    for i in x:
        sum=sum+i
    return sum



print("\t\tReal Estate Values\t\t\n\n")
print("*************************************")

list=[]
do="true";
while do=="true":
    print("Enter cost of one home or -99 to quit: ")
    x = int(input())
    if  x!=-99:
        list.append(x)
    else:
        if len(list)==0:
            print("Your list is empty, try again\n")

        else:
            do="false"
print("*************************************")
print("The Prices of homes in your area:")
showlist(list)
print("*************************************")
print("The median value is: $",median(list))
print("The average sale price is: %",average(list))
print("The minimum sale price is: $",min(list))
print("The maximum sale price is: $",max(list))