# -*- coding: utf-8 -*-
"""
@author: Scottie
"""
import tkinter

class calc():
    def __init__(self, master):
        
        frame = tkinter.Frame(master)
        frame.pack()
        
        self.opp1=tkinter.DoubleVar()
        self.opp2=tkinter.DoubleVar()
        self.result=tkinter.DoubleVar()
        self.opp1.set(3.14)
        self.opp2.set(1.42)
       
        tkinter.Label(frame, text='1. Operand = ').grid(row=0,column=0)
        tkinter.Entry(frame,textvariable=self.opp1).grid(row=0,column=1)
        
        tkinter.Label(frame, text='2. Operand = ').grid(row=1,column=0)
        tkinter.Entry(frame,textvariable=self.opp2).grid(row=1,column=1)
        
        add = tkinter.Button(frame,text='ADD',command=self.Add,bg='sky blue')
        add.grid(row=2,column=0)
        
        sub = tkinter.Button(frame,text='SUB',command=self.Sub,bg='antique white')
        sub.grid(row=2,column=1)
        
        clear = tkinter.Button(frame,text='CLEAR',command=self.Clear,bg='#00A86B')
        clear.grid(row=2,column=3)
        
        tkinter.Label(frame, text='Result=').grid(row=3,column=0)
        tkinter.Label(frame, textvariable=self.result).grid(row=3,column=1)
        
    def Add(self):
        a=self.opp1.get()
        b=self.opp2.get()
        self.result.set(a+b)
        
    def Sub(self):
        a=self.opp1.get()
        b=self.opp2.get()
        self.result.set(a-b)     
        
    def Clear(self):
       self.opp1.set(0.0)
       self.opp2.set(0.0)
       self.result.set(0.0)    
       
       
root = tkinter.Tk()
root.wm_title('SAJ Calculator')

app = calc(root)
root.mainloop()