# -*- coding: utf-8 -*-
"""
@author: Scottie
"""
import tkinter


root = tkinter.Tk()
root.wm_title('Powder Calculator')


root.geometry('1000x300')

rows = 0
columns = 0
while rows < 10:
    root.rowconfigure(rows, weight=1)
    rows += 1

while columns < 10:
    root.columnconfigure(columns, weight=1)
    columns += 1
class calc():
    def __init__(self, master):
        
        frame = tkinter.Frame(master)
        frame.pack()



        self.linearinches=tkinter.DoubleVar()
        self.length=tkinter.DoubleVar()
        self.width=tkinter.DoubleVar()
        self.ratelin=tkinter.DoubleVar()
        self.ratesquare=tkinter.DoubleVar()
        self.pieceslin=tkinter.DoubleVar()
        self.piecessquare=tkinter.DoubleVar()
        self.result=tkinter.DoubleVar()
        self.ratelin.set(3.5)
        self.ratesquare.set(7.0)
        self.pieceslin.set(1)
        self.piecessquare.set(1)
        self.result.set(0)
        
        tkinter.Label(frame, text='Linear Feet',font=('Helvetica',20,'bold')).grid(row=0,column=0)
        tkinter.Label(frame, text='Items',font=('Helvetica',20,'bold')).grid(row=0,column=9)
        self.listbox = tkinter.Listbox(frame, background="White", fg="blue",selectbackground="Red",highlightcolor="Red")
        self.listbox.grid(row=1, column=9,rowspan=20)
        tkinter.Label(frame, text='Linear Length').grid(row=1,column=0)
        tkinter.Entry(frame,textvariable=self.linearinches).grid(row=1,column=1)
        
        
        tkinter.Label(frame, text='Rate').grid(row=1,column=4)
        tkinter.Entry(frame,textvariable=self.ratelin).grid(row=1,column=5)
        
        tkinter.Label(frame, text='Pieces').grid(row=1,column=6)
        tkinter.Entry(frame,textvariable=self.pieceslin).grid(row=1,column=7)
        
        tkinter.Label(frame, text='Square Feet',font=('Helvetica',20,'bold')).grid(row=2,column=0,)
        tkinter.Label(frame, text='Length').grid(row=3,column=0)
        tkinter.Entry(frame,textvariable=self.length).grid(row=3,column=1)
        
        tkinter.Label(frame, text='Width').grid(row=3,column=2)
        tkinter.Entry(frame,textvariable=self.width).grid(row=3,column=3)
        
        tkinter.Label(frame, text='Rate').grid(row=3,column=4)
        tkinter.Entry(frame,textvariable=self.ratesquare).grid(row=3,column=5)
        
        tkinter.Label(frame, text='Pieces').grid(row=3,column=6)
        tkinter.Entry(frame,textvariable=self.piecessquare).grid(row=3,column=7)
        
      
       
        add = tkinter.Button(frame,text='ADD',command=self.Addlinear,bg='sky blue',padx=25)
        add.grid(row=1,column=8)
        
        sub = tkinter.Button(frame,text='ADD',command=self.AddSquare,bg='sky blue',padx=25)
        sub.grid(row=3,column=8)
        
        clear = tkinter.Button(frame,text='CLEAR',command=self.Clear,bg='#00A86B')
        clear.grid(row=5,column=3)
        
        tkinter.Label(frame, text='Total $',font=('Helvetica',20,'bold')).grid(row=4,column=7)
        tkinter.Label(frame, textvariable=self.result,font=('Helvetica',20,'bold')).grid(row=4,column=8)
        
    def Addlinear(self):
        a=self.linearinches.get()
        b=self.ratelin.get()
        c=self.pieceslin.get()
        tot=round((a/12)*b*c,2)
        self.listbox.insert(tkinter.END,  str(round(a/12,2))+" ft     "+"$"+str(tot)+"    "+str(c))
        e=self.result.get()+tot
        round(e,2)
        self.result.set(round(e,2))
        
    def AddSquare(self):
        a=self.length.get()
        b=self.width.get()
        c=self.ratesquare.get()
        d=self.piecessquare.get()
        tot=round((a/12)*(b/12)*c*d)
        self.listbox.insert(tkinter.END,  str(round((a/12)*(b/12),2))+" ft^2  "+"$"+str(tot)+"   "+str(d))
        e=self.result.get()+tot
        round(e,2)
        self.result.set(round(e,2))
        

    def Clear(self):
        self.ratelin.set(3.5)
        self.ratesquare.set(7.0)
        self.pieceslin.set(1)
        self.piecessquare.set(1)
        self.result.set(0)
        self.listbox.delete(0,tkinter.END)
       
app = calc(root)          
root.mainloop()