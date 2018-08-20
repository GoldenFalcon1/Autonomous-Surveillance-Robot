import time
import picamera
import pyexiv2
import fractions
import serial
import math
from PIL import Image
from PIL.ExifTags import TAGS
import sys

delay=1
no_of_pic=5
base_flag=0
lat_dummy=52.130723
lng_dummy=-106.655752

def to_deg(value, loc):
        if value < 0:
            loc_value = loc[0]
        elif value > 0:
            loc_value = loc[1]
        else:
            loc_value = ""
        abs_value = abs(value)
        deg =  int(abs_value)
        t1 = (abs_value-deg)*60
        min = int(t1)
        sec = round((t1 - min)* 60, 5)
        return (deg, min, sec, loc_value)

# Read the GPS data for Latitude and Longitude
def getCoord():
	# Start the serial connection
	ser=serial.Serial('/dev/ttyAMA0', 115200, bytesize=serial.EIGHTBITS, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE, timeout=1)
	ser.write("AT+CGNSINF\r")
	while True:
		response = ser.readline()
		if "+CGNSINF: 1," in response:
			# Split the reading by commas and return the parts referencing lat and long
			array = response.split(",")
			lat = array[3]
			print lat
			lon = array[4]
			print lon
			return (lat,lon)

def set_gps_location(file_name, lat, lng):
    """Adds GPS position as EXIF metadata
    Keyword arguments:
    file_name -- image file 
    lat -- latitude (as float)
    lng -- longitude (as float)
    """
    lat_deg = to_deg(lat, ["S", "N"])
    lng_deg = to_deg(lng, ["W", "E"])
    
    print lat_deg
    print lng_deg
    
    # convert decimal coordinates into degrees, munutes and seconds
    exiv_lat = (pyexiv2.Rational(lat_deg[0]*60+lat_deg[1],60),pyexiv2.Rational(lat_deg[2]*100,6000), pyexiv2.Rational(0, 1))
    exiv_lng = (pyexiv2.Rational(lng_deg[0]*60+lng_deg[1],60),pyexiv2.Rational(lng_deg[2]*100,6000), pyexiv2.Rational(0, 1))

    exiv_image = pyexiv2.ImageMetadata(file_name)
    exiv_image.read()
    exif_keys = exiv_image.exif_keys
    
    exiv_image["Exif.GPSInfo.GPSLatitude"] = exiv_lat
    exiv_image["Exif.GPSInfo.GPSLatitudeRef"] = lat_deg[3]
    exiv_image["Exif.GPSInfo.GPSLongitude"] = exiv_lng
    exiv_image["Exif.GPSInfo.GPSLongitudeRef"] = lng_deg[3]
    exiv_image["Exif.Image.GPSTag"] = 654
    exiv_image["Exif.GPSInfo.GPSMapDatum"] = "WGS-84"
    exiv_image["Exif.GPSInfo.GPSVersionID"] = '2 0 0 0'
    
    exiv_image.write()

with picamera.PiCamera() as camera:
    camera.start_preview(fullscreen=False,window = (100,20,640,480))
    try:
        for i, filename in enumerate(
                camera.capture_continuous('./cap/rand_{counter:02d}.jpg')):
            print("-----------------------------------------------------")
            print("Capturing...")
            print("-----------------------------------------------------")
            print(filename)
            print("-----------------------------------------------------")
            print("Geotagging...")
            print("-----------------------------------------------------")
            print("Getting Cordinates") 
            if getCoord():
	        	lat_dummy, lng_dummy = getCoord()
                        set_gps_location(filename,lat_dummy,lng_dummy)
                        if base_flag == 0:
                            base_lat = lat_dummy
                            base_lng = lng_dummy
                            print("#####################################################")
                            print("Base GPS Location..")
                            print("#####################################################")
                            print base_lat
                            print base_lng
                            print("#####################################################")             
                            base_flag = 1   
                        if base_flag == 1:      
                            dist = math.hypot(lat_dummy - base_lat, lng_dummy - base_lng)
                            print("Distance from Base Location")
                            print dist
            print("#####################################################")
            print("Done...")
            print("#####################################################")
            time.sleep(delay)  #// 10 second delay
            if i == no_of_pic:     #// 15 PICTURES 
                break
    finally:
        camera.stop_preview()
