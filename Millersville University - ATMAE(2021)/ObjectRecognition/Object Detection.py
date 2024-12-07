#Import Everything Needed
import sensor, image, time, math, pyb
from pyb import Pin
import  ustruct, time



#Setting where the robot should be lined up with
EndEffectorCenter = 160


#SETTING COLOR THRESHOLDS

#Color Array Values:
#Red == 1
#Yellow == 2
#Blue == 4
thresholds = [(50, 67, 54, 87, 17, 66),(59, 99, -22, 15, 47, 80),(19, 62, -10, 39, -75, -25)]


#SETTING SHAPE VALUES-

#Object Array Values:
#Not established = 0
#Crate = 1
#Barrel = 2
Shapes =["Not established","Crate","Barrel","Sphere"]

#Initialize Shape Detected Variable
isShape = 0


#Initialize Camera Settings
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False) # must be turned off for color tracking
sensor.set_auto_whitebal(False) # must be turned off for color tracking
clock = time.clock()


#Determine the shape of object
def checkForShapes(Height, Width, pixels, isShape):

    #Area formula
    area = Height*Width

    #Is a Barrel
    if Height >= Width*1.2:
        isShape = 2

    #Is a Cube
    elif pixels*1.27>=area:
        isShape = 1

    #Is a Sphere
    else:
        isShape = 3

    #Return the shape of object
    return isShape






while(True):
    clock.tick()
    img = sensor.snapshot()
    blobs = img.find_blobs(thresholds, pixels_threshold=200, area_threshold=200, merge=True)


    #INITIALIZE PINS BEING USED:

    #RED
    p6 = pyb.Pin("P6", pyb.Pin.OUT_PP)

    #YELLOW
    p7 = pyb.Pin("P7", pyb.Pin.OUT_PP)

    #BLUE
    p8 = pyb.Pin("P8", pyb.Pin.OUT_PP)

    #MOVE RIGHT
    p9 = pyb.Pin("P9", pyb.Pin.OUT_PP)
    #MOVE LEFT
    p10 = pyb.Pin("P10", pyb.Pin.OUT_PP)


    #RETURN ALL PINS TO LOW AFTER BEING TURNED TO HIGH
    p6.low()
    p7.low()
    p8.low()

    p9.low()
    p10.low()




    for blob in img.find_blobs(thresholds, pixels_threshold=1500, area_threshold=1500, merge=True):


        if blob.code() == 1:

            #Draw Rectangle Surrounding Blob
            img.draw_rectangle(blob.rect(), color=(255, 0, 0), thickness=3)
            #Draw Cross at Center of Blob
            img.draw_cross(blob.cx(), blob.cy())
            #Draw Shape Text on Object
            img.draw_string(blob.cx(), blob.cy(), Shapes[checkForShapes(blob.rect()[3], blob.rect()[2], blob.pixels(), isShape)])

            #Print Shape Detected in Terminal
            print(Shapes[checkForShapes(blob.rect()[3], blob.rect()[2], blob.pixels(), isShape)])


            p6.high()



            #if(blob.cx < .9*EndEffectorCenter):
             #   p9.high()
            #if(blob.cx > 1.1*EndEffectorCenter)
              #  p10.high()

           # print("pixels "+str(blob.pixels()*1.3))
           # print("area "+str(blob.rect()[3]* blob.rect()[2]))
           # print("height" + str(blob.rect()[3]))
           # print("width" + str(blob.rect()[2]))
            print("Red Found")




        if blob.code() == 2:
            #Draw Rectangle Surrounding Blob
            img.draw_rectangle(blob.rect(), color=(255, 0, 0), thickness=3)
            #Draw Cross at Center of Blob
            img.draw_cross(blob.cx(), blob.cy())
            #Draw Shape Text on Object
            img.draw_string(blob.cx(), blob.cy(), Shapes[checkForShapes(blob.rect()[3], blob.rect()[2], blob.pixels(), isShape)])

            #Print Shape Detected in Terminal
            print(Shapes[checkForShapes(blob.rect()[3], blob.rect()[2], blob.pixels(), isShape)])

            p7.high()




            #if(blob.cx < .9*EndEffectorCenter):
             #   p9.high()
            #if(blob.cx > 1.1*EndEffectorCenter)
              #  p10.high()



           # print("pixels "+str(blob.pixels()*1.3))
           # print("area "+str(blob.rect()[3]* blob.rect()[2]))
           # print("height" + str(blob.rect()[3]))
           # print("width" + str(blob.rect()[2]))
            print("Yellow Found")




        if blob.code() == 4:
            #Draw Rectangle Surrounding Blob
            img.draw_rectangle(blob.rect(), color=(255, 0, 0), thickness=3)
            #Draw Cross at Center of Blob
            img.draw_cross(blob.cx(), blob.cy())
            #Draw Shape Text on Object
            img.draw_string(blob.cx(), blob.cy(), Shapes[checkForShapes(blob.rect()[3], blob.rect()[2], blob.pixels(), isShape)])

            #Print Shape Detected in Terminal
            print(Shapes[checkForShapes(blob.rect()[3], blob.rect()[2], blob.pixels(), isShape)])



            p8.high()



            #if(blob.cx < .9*EndEffectorCenter):
             #   p9.high()
            #if(blob.cx > 1.1*EndEffectorCenter)
              #  p10.high()



           # print("pixels "+str(blob.pixels()*1.3))
           # print("area "+str(blob.rect()[3]* blob.rect()[2]))
           # print("height" + str(blob.rect()[3]))
           # print("width" + str(blob.rect()[2]))
            print("Blue Found")

