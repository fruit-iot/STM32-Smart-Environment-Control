import serial
import re

from database import save_data



ser=serial.Serial(

    "COM3",

    9600,

    timeout=1

)



def read_serial():


    while True:


        line=ser.readline().decode().strip()


        if line:


            print(line)



            try:


                temp=float(
                    re.search(
                    "temp=(.*?),",
                    line
                    ).group(1)
                )


                threshold=float(
                    re.search(
                    "threshold=(.*?),",
                    line
                    ).group(1)
                )


                speed=int(
                    re.search(
                    "speed=(.*?),",
                    line
                    ).group(1)
                )


                humidity=float(
                    re.search(
                    "humidity=(.*)",
                    line
                    ).group(1)
                )


                save_data(
                    temp,
                    threshold,
                    speed,
                    humidity
                )



            except Exception as e:

                print(e)