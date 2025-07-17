# -*- coding: utf-8 -*-
"""
@author: Scottie Jacobs
3/26/21
CPE languages
"""
import tkinter
import numpy as np

data= []

with open("io.hex",'r') as f:
    contents=f.read()
    nums=[x for x in contents.split()]
    binaryval=[]
    
for i in range(len(nums)):   
    binaryval=str(bin(int(nums[i][0],16))[2:].zfill(4))+str(bin(int(nums[i][1],16))[2:].zfill(4))+str(bin(int(nums[i][2],16))[2:].zfill(4))+str(bin(int(nums[i][3],16))[2:].zfill(4))
    data=np.append(data,binaryval)      
      
class calc():
    def __init__(self, master):
           
        frame = tkinter.Frame(master)
        frame.pack()      
        self.steps=tkinter.IntVar()
        self.STATE=tkinter.StringVar()
        self.PC=tkinter.IntVar()
        self.k=tkinter.IntVar()
        self.mode=tkinter.IntVar()
        self.RD=tkinter.IntVar()
        self.RS=tkinter.IntVar()
        self.ADDRESS=tkinter.IntVar()
        self.IW=tkinter.IntVar()
        self.IR=tkinter.StringVar()
        self.CLOCK=tkinter.IntVar()
        self.Result=tkinter.StringVar()
        self.R=[]
    
        for i in range(16):
            self.R.append(tkinter.IntVar())
            self.R[i].set(-1)
            self.steps.set(0)   
        self.CLOCK.set(0)    
        self.k.set(0)
     
        step = tkinter.Button(frame,text='Step',command=self.Step,bg='sky blue')
        step.grid(row=0,column=0)
        
        step = tkinter.Button(frame,text='Reset',command=self.Reset,bg='antique white')
        step.grid(row=0,column=3)
        
        
        tkinter.Label(frame, text='Steps/clock cycles=').grid(row=1,column=0)
        tkinter.Label(frame, textvariable=self.steps).grid(row=1,column=1)        
        tkinter.Label(frame, text='Clock=').grid(row=2,column=0)
        tkinter.Label(frame, textvariable=self.CLOCK).grid(row=2,column=1)        
        tkinter.Label(frame, text='PC').grid(row=3,column=0)
        tkinter.Label(frame, textvariable=self.PC).grid(row=3,column=1)        
        tkinter.Label(frame, text='IR=').grid(row=4,column=0)
        tkinter.Label(frame, textvariable=self.IR).grid(row=4,column=1)        
        tkinter.Label(frame, text='State=').grid(row=5,column=0)
        tkinter.Label(frame, textvariable=self.STATE).grid(row=5,column=1)       
        tkinter.Label(frame, text='RD').grid(row=6,column=0)
        tkinter.Label(frame, textvariable=self.RD).grid(row=6,column=1)         
        tkinter.Label(frame, text='RS').grid(row=7,column=0)
        tkinter.Label(frame, textvariable=self.RS).grid(row=7,column=1)         
        tkinter.Label(frame, text='Address').grid(row=8,column=0)
        tkinter.Label(frame, textvariable=self.ADDRESS).grid(row=8,column=1)
        tkinter.Label(frame, text='R[0-4]').grid(row=9,column=0)
        tkinter.Label(frame, textvariable=self.R[0]).grid(row=9,column=1)      
        tkinter.Label(frame, textvariable=self.R[1]).grid(row=9,column=2)       
        tkinter.Label(frame, textvariable=self.R[2]).grid(row=9,column=3)      
        tkinter.Label(frame, textvariable=self.R[3]).grid(row=9,column=4)     
        tkinter.Label(frame, textvariable=self.R[4]).grid(row=9,column=5)          
        tkinter.Label(frame, text='R[15]').grid(row=10,column=0)
        tkinter.Label(frame, textvariable=self.R[15]).grid(row=10,column=1)        
        tkinter.Label(frame, text='Mode').grid(row=11,column=0)
        tkinter.Label(frame, textvariable=self.mode).grid(row=11,column=1)
        
        self.STATE.set('FE')

     
    def Step(self):
        self.steps.set(self.steps.get()+1) 
        if self.CLOCK.get()==0:
            self.CLOCK.set(1)
        else: 
            self.CLOCK.set(0)
            if self.STATE.get()=='FE':
                self.STATE.set('DC')
                self.IR.set(data[self.k.get()])
                self.k.set(self.k.get()+1)
                
            elif self.STATE.get()=='DC':
                self.STATE.set('EX') 
                self.mode.set(self.IR.get()[8])
                self.RD.set(int(self.IR.get()[0:4],2))
                if self.RD.get()==15:
                    self.RD.set(-1)
                self.RS.set(int(self.IR.get()[4:8],2))
                if self.RS.get()==15:
                    self.RS.set(-1)
                self.ADDRESS.set(int(self.IR.get()[9:16],2))
            elif self.STATE.get()=='EX':
                self.STATE.set('FE')               
                self.Result.set(self.R[self.RD.get()].get()-self.R[self.RS.get()].get())
                if self.RD.get()>0:
                    self.R[self.RD.get()].set(self.Result.get())
                
                
                if self.mode.get()==1:
                    self.PC.set(self.ADDRESS.get())
                else:
                    self.PC.set(self.PC.get()+self.ADDRESS.get())
                
                self.R[0].set(5)
           
        
    def Reset(self):
        for i in range(16):
            self.R.append(tkinter.IntVar())
            self.R[i].set(-1)
        self.STATE.set('FE')
        self.PC.set(0)
        self.steps.set(0)
        self.IR.set("")
        self.CLOCK.set(0)
        self.k.set(0)
     
       
root = tkinter.Tk()
root.wm_title('SAJ ISS')
root.geometry("480x320")
app = calc(root)
root.mainloop()