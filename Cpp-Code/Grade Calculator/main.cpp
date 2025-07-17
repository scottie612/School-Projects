#include <iostream>
#include <string>
using namespace std;
int main() {
    double q1,q2,q3,midterm, final;
    int goal;

   cout<<"Enter Grade For Quiz 1: ";
   cin>>q1;
   cout<<"Enter Grade For Quiz 2: ";
   cin>>q2;
   cout<<"Enter Grade For Quiz 3: ";
   cin>>q3;
   cout<<"Enter Grade For Midterm: ";
   cin>>midterm;
   cout<<"A : 1\nA- : 2\nB+ : 3\nB : 4\nB- : 5\nC+ : 6\nC : 7\nC- : 8\nD+ : 9\nD : 10\nD- : 11\nF : 12\n";
   cout<<"Enter Goal for final Grade:";
   cin>>goal;
   final=(q1*.05)+(q2*.05)+(q3*.05)+(midterm*.25);
   switch(goal){
       case 1:
           if(final+60<=94){
               cout<<"Not Possible"<<endl;
           }else{
               cout<<((94-final)/60)*100<<"%";
           }
           break;
       case 2:
           if(final+60<=90){
               cout<<"Not Possible"<<endl;
           }else{
               cout<<((90-final)/60)*100<<"%";
           }
           break;
       case 3:
           if(final+60<=87){
               cout<<"Not Possible"<<endl;
           }else{
               cout<<((87-final)/60)*100<<"%";
           }
           break;
       case 4:
           if(final+60<=84){
               cout<<"Not Possible"<<endl;
           }else{
               cout<<((84-final)/60)*100<<"%";
           }
           break;
       case 5:
           if(final+60<=80){
               cout<<"Not Possible"<<endl;
           }else{
               cout<<((80-final)/60)*100<<"%";
           }
           break;
       case 6:
           if(final+60<=77){
               cout<<"Not Possible"<<endl;
           }else{
               cout<<((77-final)/60)*100<<"%";
           }
           break;
       case 7:
           if(final+60<=74){
               cout<<"Not Possible"<<endl;
           }else{
               cout<<((74-final)/60)*100<<"%";
           }
           break;
       case 8:
           if(final+60<=70){
               cout<<"Not Possible"<<endl;
           }else{
               cout<<((70-final)/60)*100<<"%";
           }
           break;
       case 9:
           if(final+60<=67){
               cout<<"Not Possible"<<endl;
           }else{
               cout<<((67-final)/60)*100<<"%";
           }
           break;
       case 10:
           if(final+60<=64){
               cout<<"Not Possible"<<endl;
           }else{
               cout<<((64-final)/60)*100<<"%";
           }
           break;
       case 11:
           if(final+60<=60){
               cout<<"Not Possible"<<endl;
           }else{
               cout<<((60-final)/60)*100<<"%";
           }
           break;
       case 12:

               cout<<0<<"%";

           break;

   }

    return 0;
}