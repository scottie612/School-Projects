from adafruit_ble.uart import UARTServer
import time
import board
from digitalio import DigitalInOut, Direction, Pull

uart = UARTServer()

Rled = DigitalInOut(board.LED2_R)
Bled = DigitalInOut(board.LED2_B)
Gled = DigitalInOut(board.LED2_G)

Rled.direction = Direction.OUTPUT
Gled.direction = Direction.OUTPUT
Bled.direction = Direction.OUTPUT

b_cmd = str.encode("b")
g_cmd = str.encode("g")
r_cmd = str.encode("r")
x_cmd = str.encode("x")

flag = True

while True:
    uart.start_advertising()
    # Wait for a connection
    while not uart.connected:
        Gled.value = True
        Bled.value = True
        Rled.value = False
        pass

    while uart.connected:
        if flag:
            flag = False
            Gled.value = False
            Bled.value = True
            Rled.value = True

        one_byte = uart.read(1)
        if one_byte:
            if one_byte == b_cmd:
                Gled.value = True
                Bled.value = False
                Rled.value = True
                print("b command")
            if one_byte == g_cmd:
                Gled.value = False
                Bled.value = True
                Rled.value = True
                print("g command")
            if one_byte == r_cmd:
                Gled.value = True
                Bled.value = True
                Rled.value = False
                print("r command")
            if one_byte == x_cmd:
                Gled.value = True
                Bled.value = True
                Rled.value = True
                print("x command")
            uart.write(one_byte)