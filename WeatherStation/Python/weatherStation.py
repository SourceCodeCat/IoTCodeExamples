import thread
import mraa
import time
import dweepy

class Counter:
  count = 0

anemometerCounter = Counter()
raingaugeCounter = Counter()
POOLING_TIME_INTERVAL = 1 
ANEMOMETER_GPIO = 7
RAIN_GAUGE_GPIO = 8
CONST_RAIN_MM = 0.2794
CONST_RAIN_INCHES = 0.011
CONST_WIND_SPEED_MPH = 1.492  
CONST_WIND_SPEED_KM_H = 2.4 
ADC_10BIT_RESOLUTION = 0.004887586

#--------------------------------------------------------------
# GPIO Interrupt functions
#--------------------------------------------------------------
# inside a python interupt you cannot use 'basic' types so you'll need to use
# objects
#--------------------------------------------------------------
def anemometerInterrupt(args):
  #print("anemometer")
  #time.sleep(0.50) # sleep the interrupt to avoid false positives
  anemometerCounter.count+=1

def raingaugeInterrupt(args):
  #print("rain-gauge")
  time.sleep(0.125) # sleep the interrupt to avoid false positives 
  raingaugeCounter.count+=1

#--------------------------------------------------------------
# Weather Sensor Getters
#--------------------------------------------------------------
def getWindSpeed():
   temp = anemometerCounter.count
   anemometerCounter.count=0
   return temp/float(POOLING_TIME_INTERVAL)*CONST_WIND_SPEED_KM_H

def getRainLevel():
   temp = raingaugeCounter.count
   raingaugeCounter.count=0
   return temp*CONST_RAIN_MM

def getWindDirection():
  try:                                                    
      sensor = mraa.Aio(0)                                         
      adc_value = sensor.read()                                    
      #print "%s: %.2f" % ("Wind Direction", abs(direction))
                                                                 
  except:                                                   
      print ("Are you sure you have an ADC?") 
  
  adc_value_float = ADC_10BIT_RESOLUTION * adc_value 
  direction = {'direction_degree': 0 , 'direction_name': ''}
  if(3.36 < adc_value_float < 3.82):
	#direction = "0"#"NORTH" #print ("NORTH\n")
        direction['direction_degree']= 0
        direction['direction_name']= "NORTH"
  elif(1.95 < adc_value_float < 2.28):
	#direction = "45"#"NORTH EAST" #print ("NORTH EAST\n")
        direction['direction_degree']= 45
        direction['direction_name']= "NORTH EAST"
  elif(0.40 < adc_value_float < 0.48):                      
        #direction = "90"#"EAST" #print ("EAST\n") 
        direction['direction_degree']= 90
        direction['direction_name']= "EAST"
  elif(0.32 < adc_value_float < 0.93):                      
        #direction = "135"#"SOUTH EAST" #print ("SOUTH EAST\n") 
        direction['direction_degree']= 135
        direction['direction_name']= "SOUTH EAST"
  elif(1.19 < adc_value_float < 1.44):                      
        #direction = "180"#"SOUTH" #print ("SOUTH\n") 
        direction['direction_degree']= 180
        direction['direction_name']= "SOUTH"
  elif(2.87 < adc_value_float < 3.09):                      
        #direction = "225"#"SOUTH WEST" #print ("SOUTH WEST\n") 
        direction['direction_degree']= 225
        direction['direction_name']= "SOUTH WEST"
  elif(4.46 < adc_value_float < 4.64):                      
        #direction = "270"#"WEST" #print ("WEST\n") 
        direction['direction_degree']= 270
        direction['direction_name']= "WEST"
  elif(3.90 < adc_value_float < 4.31):                      
        #direction = "315"#"NORTH WEST" #print ("NORTH WEST\n") 
        direction['direction_degree']= 315
        direction['direction_name']= "NORTH WEST"
#  else:
#        print (adc_value_float)
  return direction
  
 

#--------------------------------------------------------------
# Pooling Thread Function
#--------------------------------------------------------------
def poolSensorsThread( threadName):
   while True: 
        
       tmp1 = getWindSpeed()
       tmp2 = getRainLevel()
       tmp3 = getWindDirection()
       
       try:
          dweepy.dweet_for('WZPN1', {'WDIRECTION': tmp3['direction_degree'],'WDIRECTION_NAME': tmp3['direction_name'],'WindSpeed':tmp1,'RAIN_LVL':tmp2}) 
       except:
          pass   
       print ("WindSpeed: "+str(tmp1)+" Km/h")
       print ("Rain-Level:"+str(tmp2)+" mm")       
       print ("Direction: "+tmp3['direction_name'])
       time.sleep(POOLING_TIME_INTERVAL)
#--------------------------------------------------------------





#--------------------------------------------------------------
# Setting up GPIO's
#--------------------------------------------------------------
# Anemometer
#------------------------
anemometer = mraa.Gpio(ANEMOMETER_GPIO)
anemometer.dir(mraa.DIR_IN)
anemometer.mode(mraa.MODE_PULLDOWN)
anemometer.isr(mraa.EDGE_BOTH, anemometerInterrupt, anemometerInterrupt)
#------------------------
# Rain Gauge
#------------------------
raingauge = mraa.Gpio(RAIN_GAUGE_GPIO)
raingauge.dir(mraa.DIR_IN)
raingauge.mode(mraa.MODE_PULLDOWN)
raingauge.isr(mraa.EDGE_RISING, raingaugeInterrupt, raingaugeInterrupt)
#--------------------------------------------------------------

#--------------------------------------------------------------
# Thread Creation
#--------------------------------------------------------------

thread.start_new_thread( poolSensorsThread, ("poolSensorsThread", ) )

exit = 0
while exit == 0:
   print "%s %d%s" % ("Weather Station: readings will show up every:",POOLING_TIME_INTERVAL,"s")
   VALUE = raw_input("Pressing 'X' at any time, will exit the Weather Station\n")
   if ( VALUE == "X") or (VALUE == "x"):
		exit = 1
