# -*- coding: utf-8 -*-
"""
@author: Scottie
"""
import re
import numpy as np
import matplotlib
import matplotlib.pyplot as plt
import tkinter

matplotlib.use('TkAgg')

from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import (
    FigureCanvasTkAgg,
    NavigationToolbar2Tk
)


root = tkinter.Tk()
root.wm_title('ECC')


root.geometry('1500x500')

rows = 0
columns = 0
while rows < 10:
    root.rowconfigure(rows, weight=1)
    rows += 1

while columns < 10:
    root.columnconfigure(columns, weight=1)
    columns += 1
class ECC():
    def __init__(self, master):
        
        self.frame1 = tkinter.Frame(master)
        self.frame1.pack()
        frame=self.frame1

        self.fig = Figure(figsize = (5, 5),dpi = 100)

        self.CurveA=tkinter.IntVar()
        self.CurveB=tkinter.IntVar()
        self.Px=tkinter.DoubleVar()
        self.Py=tkinter.DoubleVar()
        self.Qx=tkinter.DoubleVar()
        self.Qy=tkinter.DoubleVar()
        self.PQx=tkinter.DoubleVar()
        self.PQy=tkinter.DoubleVar()
        self.CurveA.set(-7)
        self.CurveB.set(10)
        self.Px.set(1)
        self.Py.set(2)
        self.Qx.set(3)
        self.Qy.set(4)
        self.PQx.set(-3)
        self.PQy.set(2)


      
        
        self.y, self.x = np.ogrid[-5:5:100j, -5:5:100j]
        self.Curve = self.fig.add_subplot(111)



      
    
        
        self.Curve.contour(self.x.ravel(), self.y.ravel(), pow(self.y, 2) - pow(self.x, 3) - self.x * self.CurveA.get() - self.CurveB.get(), [0])
        
        self.Curve.set_autoscaley_on(True)
        self.Curve.set_autoscalex_on(True)
        self.Curve.grid()
        self.Curve.plot(self.Px.get(),self.Py.get(),self.Qx.get(),self.Qy.get())
        self.Curve.arrow(self.Px.get(),self.Py.get(),self.Qx.get(),self.Qy.get(),width=0.02,color='red',head_length=0.0,head_width=0.0)
        self.canvas = FigureCanvasTkAgg(self.fig)  
        self.canvas.draw()
        toolbar = NavigationToolbar2Tk(self.canvas,master)
        toolbar.update()
        self.canvas.get_tk_widget().pack()

        tkinter.Label(frame, text='Elliptic Curve point addition',font=('Helvetica',20,'bold')).grid(row=0,column=0)

        tkinter.Label(frame, text='Curve').grid(row=1,column=4)
        tkinter.Label(frame, text='a').grid(row=1,column=5)
        tkinter.Label(frame, text=round( self.CurveA.get(),2)).grid(row=1,column=6)
        tkinter.Button(frame,text='inc',command=self.incCurveA,bg='sky blue',padx=25).grid(row=1,column=7)
        tkinter.Button(frame,text='dec',command=self.decCurveA,bg='sky blue',padx=25).grid(row=1,column=8)

        tkinter.Label(frame, text='b').grid(row=1,column=9)
        tkinter.Label(frame, text=round( self.CurveB.get(),2)).grid(row=1,column=10)
        tkinter.Button(frame,text='inc',command=self.incCurveB,bg='sky blue',padx=25).grid(row=1,column=11)
        tkinter.Button(frame,text='dec',command=self.decCurveB,bg='sky blue',padx=25).grid(row=1,column=12)        
        
        tkinter.Label(frame, text='P').grid(row=2,column=4)
        tkinter.Label(frame, text='x').grid(row=2,column=5)
        tkinter.Label(frame, text=round( self.Px.get(),2)).grid(row=2,column=6)
        tkinter.Button(frame,text='inc',command=self.incPx,bg='sky blue',padx=25).grid(row=2,column=7)
        tkinter.Button(frame,text='dec',command=self.decPx,bg='sky blue',padx=25).grid(row=2,column=8)  
        tkinter.Label(frame, text='y').grid(row=2,column=9)
        tkinter.Label(frame, textvariable=round( self.Py.get(),2)).grid(row=2,column=10)



        tkinter.Label(frame, text='Q').grid(row=3,column=4)
        tkinter.Label(frame, text='x').grid(row=3,column=5)
        tkinter.Label(frame, text=round( self.Qx.get(),2)).grid(row=3,column=6)
        tkinter.Button(frame,text='inc',command=self.incQx,bg='sky blue',padx=25).grid(row=3,column=7)
        tkinter.Button(frame,text='dec',command=self.decQx,bg='sky blue',padx=25).grid(row=3,column=8)  
        tkinter.Label(frame, text='y').grid(row=3,column=9)
        tkinter.Label(frame, text=round( self.Qy.get(),2)).grid(row=3,column=10)
 




        tkinter.Label(frame, text='R=P+Q').grid(row=4,column=4)
        tkinter.Label(frame, text='x').grid(row=4,column=5)
        tkinter.Label(frame,text=round( self.PQx.get(),2)).grid(row=4,column=6)
        tkinter.Label(frame, text='y').grid(row=4,column=7)
        tkinter.Label(frame,text=self.PQy.get()).grid(row=4,column=8)
        self.Plot()



    


 
    def f(self,x):
        return abs(np.sqrt(x**3 + self.CurveA.get() * x +self.CurveB.get()))




    def update(self):
        self.Py.set(self.f(self.Px.get()))
        self.Qy.set(self.f(self.Qx.get()))
        delta=(self.Qy.get()-self.Py.get())/(self.Qx.get()-self.Px.get())
        self.PQx.set((delta**2)-self.Px.get()-self.Qx.get())
        self.PQy.set(delta*(self.Px.get()-self.PQx.get())-self.Py.get())
        tkinter.Label(self.frame1,text=round( self.PQx.get(),2)).grid(row=4,column=6)
        tkinter.Label(self.frame1,text=round( self.PQy.get(),2)).grid(row=4,column=8)
        tkinter.Label(self.frame1, text=round( self.Py.get(),2)).grid(row=2,column=10)
        tkinter.Label(self.frame1, text=round( self.Qy.get(),2)).grid(row=3,column=10)


    def Plot(self):
        self.fig.delaxes(self.Curve)
        self.Curve = self.fig.add_subplot(111)
        


        



        self.Curve.axvline(self.PQx.get())
        self.Curve.plot(self.PQx.get(),self.PQy.get(),marker='o')
        self.Curve.annotate('R',(self.PQx.get(),self.PQy.get()+.25))
        self.Curve.axline((self.Px.get(),self.Py.get()),(self.Qx.get(),self.Qy.get()))
        self.Curve.plot(self.Qx.get(),self.Qy.get(),marker='o')
        self.Curve.plot(self.Px.get(),self.Py.get(),marker='o')
        self.Curve.annotate('Q',(self.Qx.get(),self.Qy.get()+.25))
        self.Curve.annotate('P',(self.Px.get(),self.Py.get()+.25))
        self.Curve.contour(self.x.ravel(), self.y.ravel(), pow(self.y, 2) - pow(self.x, 3) - self.x * self.CurveA.get() - self.CurveB.get(), [0])
        self.Curve.grid()
        self.canvas.draw()
        
        
        
      

    def incCurveA(self):
        
        a=self.CurveA.get()
        a=a+1
        self.CurveA.set(a)
        self.update()
        tkinter.Label(self.frame1, text=round( self.CurveA.get(),2)).grid(row=1,column=6)
        self.Plot()
        
    def decCurveA(self):
        a=self.CurveA.get()
        a=a-1
        self.CurveA.set(a)
        self.update()
        tkinter.Label(self.frame1, text=round( self.CurveA.get(),2)).grid(row=1,column=6)
        self.Plot()
    def incCurveB(self):
        a=self.CurveB.get()
        a=a+1
        self.CurveB.set(a)
        self.update()
        tkinter.Label(self.frame1, text=round( self.CurveB.get(),2)).grid(row=1,column=10)
        self.Plot()
        
    def decCurveB(self):
        a=self.CurveB.get()
        a=a-1
        self.CurveB.set(a)
        self.update()
        tkinter.Label(self.frame1, text=round( self.CurveB.get(),2)).grid(row=1,column=10)
        self.Plot()

    def incPx(self):
        a=self.Px.get()
        a=a+1
        self.Px.set(a)
        self.update()
        tkinter.Label(self.frame1, text=round( self.Px.get(),2)).grid(row=2,column=6)
        self.Plot()
        
    def decPx(self):
        a=self.Px.get()
        a=a-1
        self.Px.set(a)
        self.update()
        tkinter.Label(self.frame1, text=round( self.Px.get(),2)).grid(row=2,column=6)
        self.Plot()


    def incQx(self):
        a=self.Qx.get()
        a=a+1
        self.Qx.set(a)
        self.update()
        tkinter.Label(self.frame1, text=round( self.Qx.get(),2)).grid(row=3,column=6)
        self.Plot()
        
    def decQx(self):
        a=self.Qx.get()
        a=a-1
        self.Qx.set(a)
        self.update()
        tkinter.Label(self.frame1, text=round( self.Qx.get(),2)).grid(row=3,column=6)
        self.Plot()
     
        
        
        

       
app = ECC(root)          
root.mainloop()