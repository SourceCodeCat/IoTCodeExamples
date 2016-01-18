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
CONVERSION = 0x0     #// Conversion result register.
CONFIG   =  0x1      #// 16-bit configuration register.
THRESHL  =  0x2      #// Low threshold setting. Not used (yet).
THRESHH  =  0x3      #// High threshold setting. Not used (yet).
#--------------------------------------------------------------------------------------------

#Voltage Ranges------------------------------------------------------------------------------
_6_144V = 0x0	     #//  _6_144V - Range is -6.144V to 6.141V, and step size is 3mV.
_4_096V = 0x1        #//  _4_096V - Range is -4.096V to 4.094V, and step size is 2mV.
_2_048V = 0x2        #//  _2_048V - Range is -2.048V to 2.047V, and step size is 1mV.
_1_024V = 0x3        #//  _1_024V - Range is -1.024V to 1.0235V, and step size is 500uV.
_0_512V = 0x4        #//  _0_512V - Range is -0.512V to 0.51175V, and step size is 250uV.
_0_256V = 0x5        #//  _0_256V - Range is -0.256V to 0.255875V, and step size is 125uV.
#// The default setting is _2_048V.
#--------------------------------------------------------------------------------------------

#Operation Mode------------------------------------------------------------------------------
CONTINUOUS = 0x0     #: Continuous conversion mode
SINGLE_SHOT = 0x1    #: Power-down single-shot mode (default)
#--------------------------------------------------------------------------------------------

#Data Rate-----------------------------------------------------------------------------------
_128SPS = 0x0        #: 128SPS 
_250SPS = 0x1  	     #: 250SPS 
_490SPS = 0x2        #: 490SPS 
_920SPS = 0x3        #: 920SPS 
_1600SPS = 0x4       #: 1600SPS (default)
_2400SPS = 0x5       #: 2400SPS
_3300SPS = 0x6       #: 3300SPS
_3300SPS = 0x7       #: 3300SPS
#--------------------------------------------------------------------------------------------

#Operation Mode------------------------------------------------------------------------------
MODE_CONTINUOUS = 0x0 #: Continuous conversion mode
MODE_SINGLESHOT = 0x1 #: Power-down single-shot mode (default)
#--------------------------------------------------------------------------------------------
#Channel selection and read start stuff- the high nibble of the 16-bit cfg
#register controls the start of a single conversion, the channel(s) read,
#and whether they're read single ended or differential.
CHANNEL_MASK  = 0x3000  # There are four channels, and single ended reads
                        # are specified by a two-bit address at bits 13:12
RANGE_MASK = 0x0E00     #// bits to clear for gain parameter
RANGE_SHIFT = 9         #// how far to shift our prepared data to drop it into the
                        #//  right spot in the cfg reg
SINGLE_ENDED = 0x4000   # Set for single-ended
START_READ =  0x8000    # To start a read, we set the highest bit of the
CFG_REG_CHL_MASK = 0xf000 # Used to clear the high nibble of the cfg reg
BUSY_MASK = 0x8000 # When the highest bit in the cfg reg is set, the
CHANNEL_SHIFT = 12   # shift the raw channel # by this
MODE_MASK = 0x100       #Used to clear the mode bit
MODE_SHIFT = 9          #shift the mode bit byt this  
#OK = 0xc183 #<-----------is what the coreect config should be..
#DEFAULT = 0x8583 #<------is defualt config..
scaler = 1.0


#-----------------------------------------------------------------------

def getConfigRegister():
	uint16_cfgRegVal = 0
	uint16_cfgRegVal = adc.readWordReg(CONFIG)
	uint16_cfgRegVal = (uint16_cfgRegVal>>8) | (uint16_cfgRegVal<<8 & 0XFF00)
	return uint16_cfgRegVal         
#-----------------------------------------------------------------------
def setConfigRegister(configValue):

	#data = [0]*3;
	#data[0] = CONFIG;  #// address of the config register
	#data[1] = configValue>>8;
	#data[2] = configValue;
        configValue = (configValue>>8) | (configValue<<8 & 0XFF00) 
        adc.writeWordReg(CONFIG,configValue) 
	#adc.write(bytearray(configValue));


#-----------------------------------------------------------------------
def getScaler():

	return _scaler;


#-----------------------------------------------------------------------
def getRawResult(channel):

	cfgRegVal = getConfigRegister();
	cfgRegVal &= ~CHANNEL_MASK; #// clear existing channel settings
	cfgRegVal |= SINGLE_ENDED;  #// set the SE bit for a s-e read
	cfgRegVal |= (channel<<CHANNEL_SHIFT) & CHANNEL_MASK; #// put the channel bits in
	cfgRegVal |= START_READ;    #// set the start read bit
	setConfigRegister(cfgRegVal);
	return readADC();
#-----------------------------------------------------------------------
def readADC():

	cfgRegVal = getConfigRegister();
	cfgRegVal |= START_READ; #// set the start read bit
	setConfigRegister(cfgRegVal);

	result = 0;
	fullValue=0;
	busyDelay = 0;
        result_mio = 0;

	while (getConfigRegister() & BUSY_MASK) == 0 :
		time.sleep(0.100);
                busyDelay+=1 
		if busyDelay > 100:
			return 0xffff

	
        data = adc.readWordReg(CONVERSION)        
	result_mio += (data & 0XF000) >>12;
        result_mio += (data & 0XFF) << 4;
        result_mio = result_mio;
	
	#print(result_mio)
	#result += (data & 0XF000) >>12; 
	#result += (data & 0X00F0) << 4;
	#result += (data & 0X000F) << 4;
	#if result > 0x7FF:
	#	result =  -1*((0x7FF*2+2)+(~result))
        
               

        return result_mio
								    
#-----------------------------------------------------------------------
def getResult(channel):

  rawVal = getRawResult(channel);
  return float(rawVal) * scaler/1000;

#-----------------------------------------------------------------------
def setRange(range_):
  global scaler
  cfgRegVal = getConfigRegister();
  cfgRegVal &= ~RANGE_MASK;
  cfgRegVal |= (range_ << RANGE_SHIFT) & RANGE_MASK;
  setConfigRegister(cfgRegVal);
  if range_ == _6_144V:
     scaler = 3.0;
  elif range_ == _4_096V:
       scaler = 2.0;  
  elif range_ == _2_048V:
       scaler = 1.0;
  elif range_ == _1_024V:
       scaler = 0.5;
  elif range_ == _0_512V:
       scaler = 0.25;
  elif range_ == _0_256V:
       scaler = 0.125;

#-----------------------------------------------------------------------
def getScaler():
  return scaler;
#-----------------------------------------------------------------------
def setOprationMode(mode):
  
  cfgRegVal = getConfigRegister();
  cfgRegVal &= ~MODE_MASK;
  cfgRegVal |= (mode << MODE_SHIFT) & MODE_MASK;
  setConfigRegister(cfgRegVal);
#-----------------------------------------------------------------------
adc = mraa.I2c(1)
adc.address(0x48)
setRange(_6_144V)









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

  
  adc_value_float = getResult(0)# read the result from channel 0 of the ADC
  direction = {'direction_degree': 0 , 'direction_name': ''}
  if(abs(adc_float-2.64)<0.1 ||  abs(adc_float-1.36)<0.1):
	#direction = "0"#"NORTH" #print ("NORTH\n")
        direction['direction_degree']= 0
        direction['direction_name']= "NORTH"
  elif(abs(adc_float-1.55)<0.1 || abs(adc_float-1.282)<0.1):
	#direction = "45"#"NORTH EAST" #print ("NORTH EAST\n")
        direction['direction_degree']= 45
        direction['direction_name']= "NORTH EAST"
  elif(abs(adc_float-0.315)<0.1 || abs(adc_float-0.220)<0.1):                      
        #direction = "90"#"EAST" #print ("EAST\n") 
        direction['direction_degree']= 90
        direction['direction_name']= "EAST"
  elif(abs(adc_float-0.62)<0.1 || abs(adc_float-0.426)<0.1):                      
        #direction = "135"#"SOUTH EAST" #print ("SOUTH EAST\n") 
        direction['direction_degree']= 135
        direction['direction_name']= "SOUTH EAST"
  elif(abs(adc_float-0.965)<0.1 || abs(adc_float-0.82)<0.1):                      
        #direction = "180"#"SOUTH" #print ("SOUTH\n") 
        direction['direction_degree']= 180
        direction['direction_name']= "SOUTH"
  elif(abs(adc_float-2.12)<0.1 || abs(adc_float-2.018)<0.1):                      
        #direction = "225"#"SOUTH WEST" #print ("SOUTH WEST\n") 
        direction['direction_degree']= 225
        direction['direction_name']= "SOUTH WEST"
  elif(abs(adc_float-3.177)<0.1 || abs(adc_float-2.8)<0.1):                      
        #direction = "270"#"WEST" #print ("WEST\n") 
        direction['direction_degree']= 270
        direction['direction_name']= "WEST"
  elif(abs(adc_float-2.9)<0.1 || abs(adc_float-2.36)<0.1):                      
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
       
#       try:
#          dweepy.dweet_for('WZPN1', {'WDIRECTION': tmp3['direction_degree'],'WDIRECTION_NAME': tmp3['direction_name'],'WindSpeed':tmp1,'RAIN_LVL':tmp2}) 
#       except:
#          pass   
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
