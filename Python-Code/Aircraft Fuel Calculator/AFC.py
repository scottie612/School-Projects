print("Aircraft Fuel Calculator")
do=true
while do==true:

    dist=float(input("\nDistance in nautical miles : "))
    MPH=120
    distance=dist/MPH
    minutes=0
    if(distance<1):
        hours=1
        minutes=0
    else:
        time=dist/MPH
        secs=time*3600
        hours = secs / 3600
        secs %= 3600
        minutes = secs / 60
    print("Flight time : ",hours ," hours(s)and ",minutes ," minutes(s)")
    f=(dist/MPH)+.5
    fuel=f*8.4
    print("Required fuel : ",fuel," gallons")

    cont = input("\nContinue? (y/n) : ")
    if cont == "n":
        do=false
        break