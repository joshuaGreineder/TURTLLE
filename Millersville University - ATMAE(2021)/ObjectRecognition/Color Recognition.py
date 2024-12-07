
#This code was adapted from examples given in the
#OpenMV IDE on color tracking and outputs.
# This example shows off single color code tracking using
#the OpenMV Cam. A color code is a blob composed of
#two or more colors. The example below will only track
#colored objects which have both the colors below in
#them.
import sensor, image, time, math, pyb
from pyb import Pin
from colorama import Fore, Back, Style




# Color Tracking Thresholds (L Min, L Max, A Min, A Max, B
#Min, B Max) The below thresholds track in general
#red/green things. You may wish to tune them... First is
#generic_red_thresholds –> index is 0 so code == (1 << 0)
#Second is generic_green_thresholds -> index is 1 so code
#== (1 << 1)


#Red == 1
#Yellow == 2
#Blue == 3


red_threshold = [(41, 70, 46, 81, 29, 63)]
blue_threshold = [(75, 95, -19, 8, 53, 96)]
yellow_threshold = [(53, 76, -21, -3, -56, -19)]


#thresholds = [(41, 70, 46, 81, 29, 63),(75, 95, -19, 8, 53, 96),(53, 76, -21, -3, -56, -19)]



sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False) # must be turned off for color
#tracking
sensor.set_auto_whitebal(False) # must be turned off for
#color tracking
clock = time.clock()
# Only blobs that with more pixels than "pixel_threshold"
#and more area than "area_threshold" are



# returned by "find_blobs" below. Change
#"pixels_threshold" and "area_threshold" if you change the
#camera resolution. "merge=True" must be set to merge
#overlapping color blobs for color codes.
while(True):
    clock.tick()
    img = sensor.snapshot()
    for blob in img.find_blobs(red_thresholds,
    pixels_threshold=100, area_threshold=100, merge=True):



        if 1==1:
        print(thresholds[1]
        if blob.code() == 1:
            img.draw_rectangle(blob.rect(), color=(255,0,0), thickness=2)
            print("Red Found")
        if blob.code() == 2:
            img.draw_rectangle(blob.rect(), color=(255, 0, 0), thickness=2)
            print("Yellow Found")
        if blob.code() == 3:
            img.draw_rectangle(blob.rect(), color=(255, 0, 0), thickness=2)
            print("Blue Found")
while(True):
    clock.tick()
    img = sensor.snapshot()
    for blob in img.find_blobs(yellow_thresholds,
    pixels_threshold=100, area_threshold=100, merge=True):



        if 1==1:
        print(thresholds[1]
        if blob.code() == 1:
            img.draw_rectangle(blob.rect(), color=(255,0,0), thickness=2)
            print("Red Found")
        if blob.code() == 2:
            img.draw_rectangle(blob.rect(), color=(255, 0, 0), thickness=2)
            print("Yellow Found")
        if blob.code() == 3:
            img.draw_rectangle(blob.rect(), color=(255, 0, 0), thickness=2)
            print("Blue Found")

while(True):
    clock.tick()
    img = sensor.snapshot()
    for blob in img.find_blobs(blue_thresholds,
    pixels_threshold=100, area_threshold=100, merge=True):



        if 1==1:
        print(thresholds[1]
        if blob.code() == 1:
            img.draw_rectangle(blob.rect(), color=(255,0,0), thickness=2)
            print("Red Found")
        if blob.code() == 2:
            img.draw_rectangle(blob.rect(), color=(255, 0, 0), thickness=2)
            print("Yellow Found")
        if blob.code() == 3:
            img.draw_rectangle(blob.rect(), color=(255, 0, 0), thickness=2)
            print("Blue Found")
