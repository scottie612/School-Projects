

import glob
from logging import root
from tkinter import *
from PIL import Image

import re
import matplotlib.pyplot as plt
from datetime import datetime


from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import (
    FigureCanvasTkAgg,
    NavigationToolbar2Tk
)
class App:

    def __init__(self, master):

        self.event_num = 1

        # Create a container
        frame = Frame(master)

        # Create 2 buttons
        self.button_left = Button(frame,text="< Previous Event",
                                    command=self.decrease)
        self.button_left.grid(row=0,column=0)
        self.button_right = Button(frame,text="Next Event >",
                                    command=self.increase)
        self.button_right.grid(row=0,column=1)


        self.fig = Figure()
        self.ax = self.fig.add_subplot(111)
        self.fig.autofmt_xdate()
        import matplotlib.dates as mdates
        self.ax.fmt_xdata = mdates.DateFormatter('%Y-%m-%d')
        


        self.canvas = FigureCanvasTkAgg(self.fig,master=master)
        self.canvas.show()
        self.canvas.get_tk_widget().grid(row=1,column=0)
        frame.grid(row=0,column=0)

    def decrease(self):
        self.event_num -= 1

        print(self.event_num) 
        self.line, = self.ax.plot(tft[self.event_num],tf1[self.event_num],'.')
        self.canvas.draw()

    def increase(self):
        self.event_num += 1        
        print(self.event_num)
        self.line, = self.ax.plot(tft[self.event_num],tf1[self.event_num],'.')
        self.canvas.draw()
app = App(root)          
app.mainloop()