#Import Everything Needed
import sensor, image, time, math, pyb
from pyb import Pin
import  ustruct, time



#Setting where the robot should be lined up with
EndEffectorCenter = 150


#SETTING COLOR THRESHOLDS

#Color Array Values:
#Red == 1
#Yellow == 2
#Blue == 4
thresholds = [(26, 49, 30, 72, 10, 52) ,(21, 82, -19, 24, 27, 64),(12, 36, 7, 34, -64, -29)]


#SETTING SHAPE VALUES-

#Object Array Values:
#Not established = 0
#Crate = 1
#Barrel = 2
#Sphere = 3
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
    if Height >= Width*1.4:
        isShape = 2

    #Is a Cube
    elif pixels*1.3>=area:
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
    img.draw_string(0, 0, "FPS:%.2f"%(clock.fps()))

    #INITIALIZE PINS BEING USED:

    #MOVE RIGHT
    p4 = pyb.Pin("P4", pyb.Pin.OUT_PP)

    #MOVE LEFT
    p5 = pyb.Pin("P5", pyb.Pin.OUT_PP)

    #CENTERED
    p6 = pyb.Pin("P6", pyb.Pin.OUT_PP)









    for blob in img.find_blobs(thresholds, pixels_threshold=1000, area_threshold=1500, merge=True):


        #if blob.blob.cx(), blob.cy(), Shapes[checkForShapes(blob.rect()[3], blob.rect()[2], blob.pixels(), isShape)] == "Crate"

        if blob.code() == 1:

            #Draw Rectangle Surrounding Blob
            img.draw_rectangle(blob.rect(), color=(255, 0, 0), thickness=3)
            #Draw Cross at Center of Blob
            img.draw_cross(blob.cx(), blob.cy())
            #Draw Shape Text on Object
            img.draw_string(blob.cx(), blob.cy(), Shapes[checkForShapes(blob.rect()[3], blob.rect()[2], blob.pixels(), isShape)])


            difference = blob.cx()-EndEffectorCenter
            img.draw_string(blob.cx(), blob.cy()-20, str(difference))

            #FOR CALIBRATING SHAPE
            #print("pixels: "+str(blob.pixels()*1.5))
            #print("area: "+ str(blob.rect()[3]* blob.rect()[2]))
            print(Shapes[checkForShapes(blob.rect()[3], blob.rect()[2], blob.pixels(), isShape)])


            if(Shapes[checkForShapes(blob.rect()[3], blob.rect()[2], blob.pixels(), isShape)] == "Barrel"):
                print("Barrel Detected")
                print("Right")
                p4.high()
            elif(Shapes[checkForShapes(blob.rect()[3], blob.rect()[2], blob.pixels(), isShape)] == "Sphere"):
                print("Sphere Detected")
                print("Left")
                p5.high()
            elif(Shapes[checkForShapes(blob.rect()[3], blob.rect()[2], blob.pixels(), isShape)] == "Crate"):
                if (difference <-10):
                    print("Left")
                    p5.high()
                else:
                    p5.low()
                if(difference  > 10):
                    print("Right")
                    p4.high()
                else:
                    p4.low()
                if(-10<difference<10):
                    print("Centered")
                    p6.high()
                else:
                    p6.low()


            print(str(difference))
            print(blob.cx())
            print("Red Found")



        if blob.code() == 2:
            #Draw Rectangle Surrounding Blob
            img.draw_rectangle(blob.rect(), color=(255, 0, 0), thickness=3)
            #Draw Cross at Center of Blob
            img.draw_cross(blob.cx(), blob.cy())
            #Draw Shape Text on Object
            img.draw_string(blob.cx(), blob.cy(), Shapes[checkForShapes(blob.rect()[3], blob.rect()[2], blob.pixels(), isShape)])


            difference = blob.cx()-EndEffectorCenter
            img.draw_string(blob.cx(), blob.cy()-20, str(difference))

            #FOR CALIBRATING SHAPE
            #print("pixels: "+str(blob.pixels()*1.5))
            #print("area: "+ str(blob.rect()[3]* blob.rect()[2]))


            if(Shapes[checkForShapes(blob.rect()[3], blob.rect()[2], blob.pixels(), isShape)] == "Barrel"):
                print("Barrel Detected")
                print("Left")
                p5.high()
            elif(Shapes[checkForShapes(blob.rect()[3], blob.rect()[2], blob.pixels(), isShape)] == "Barrel"):
                if (difference <-10):
                    print("Left")
                    p5.high()
                else:
                    p5.low()
                if(difference  > 10):
                    print("Right")
                    p4.high()
                else:
                    p4.low()
                if(-10<difference<10):
                    print("Centered")
                    p6.high()
                else:
                    p6.low()


            print(str(difference))
            print(blob.cx())
            print("Yellow Found")



        if blob.code() == 4:
            #Draw Rectangle Surrounding Blob
            img.draw_rectangle(blob.rect(), color=(255, 0, 0), thickness=3)
            #Draw Cross at Center of Blob
            img.draw_cross(blob.cx(), blob.cy())
            #Draw Shape Text on Object
            img.draw_string(blob.cx(), blob.cy(), Shapes[checkForShapes(blob.rect()[3], blob.rect()[2], blob.pixels(), isShape)])


            difference = blob.cx()-EndEffectorCenter
            img.draw_string(blob.cx(), blob.cy()-20, str(difference))

            #FOR CALIBRATING SHAPE
            #print("pixels: "+str(blob.pixels()*1.5))
            #print("area: "+ str(blob.rect()[3]* blob.rect()[2]))


            if(Shapes[checkForShapes(blob.rect()[3], blob.rect()[2], blob.pixels(), isShape)] == "Barrel"):
                print("Barrel Detected")
                print("Left")
                p5.high()
            elif(Shapes[checkForShapes(blob.rect()[3], blob.rect()[2], blob.pixels(), isShape)] == "Barrel"):
                if (difference <-10):
                    print("Left")
                    p5.high()
                else:
                    p5.low()
                if(difference  > 10):
                    print("Right")
                    p4.high()
                else:
                    p4.low()
                if(-10<difference<10):
                    print("Centered")
                    p6.high()
                else:
                    p6.low()


            print(str(difference))
            print(blob.cx())

            print("Blue Found")

