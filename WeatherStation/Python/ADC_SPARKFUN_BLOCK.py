import mraa
import time

class ADCSPARKFUN:
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
	MODE_SHIFT = 8          #shift the mode bit byt this  
	#OK = 0xc183 #<-----------is what the coreect config should be..
	#DEFAULT = 0x8583 #<------is defualt config..
	scaler = 1.0
          

	ADC = None              # variable that will hold a reference to the sparkfun ADC Block		
	
	#-----------------------------------------------------------------------
	
	def getConfigRegister(self):
		uint16_cfgRegVal = 0
		uint16_cfgRegVal = ADCSPARKFUN.adc.readWordReg(ADCSPARKFUN.CONFIG)
		uint16_cfgRegVal = (uint16_cfgRegVal>>8) | (uint16_cfgRegVal<<8 & 0XFF00)
		return uint16_cfgRegVal         
	#-----------------------------------------------------------------------
	def setConfigRegister(self,configValue):
	
		#data = [0]*3;
		#data[0] = CONFIG;  #// address of the config register
		#data[1] = configValue>>8;
		#data[2] = configValue;
	        configValue = (configValue>>8) | (configValue<<8 & 0XFF00) 
	        ADCSPARKFUN.adc.writeWordReg(ADCSPARKFUN.CONFIG,configValue) 
		
	
	
	#-----------------------------------------------------------------------
	#-----------------------------------------------------------------------
	def getRawResult(self,channel):
	
		cfgRegVal = getConfigRegister();
		cfgRegVal &= ~ADCSPARKFUN.CHANNEL_MASK; #// clear existing channel settings
		cfgRegVal |= ADCSPARKFUN.SINGLE_ENDED;  #// set the SE bit for a s-e read
		cfgRegVal |= (channel<<ADCSPARKFUN.CHANNEL_SHIFT) & ADCSPARKFUN.CHANNEL_MASK; #// put the channel bits in
		cfgRegVal |= ADCSPARKFUN.START_READ;    #// set the start read bit
		setConfigRegister(cfgRegVal);
		return ADCSPARKFUN.readADC();
	#-----------------------------------------------------------------------
	def readADC(self):
	
		cfgRegVal = ADCSPARKFUN.getConfigRegister();
		cfgRegVal |= ADCSPARKFUN.START_READ; #// set the start read bit
		ADCSPARKFUN.setConfigRegister(cfgRegVal);
	
		result = 0;
		fullValue=0;
		busyDelay = 0;
	        result_mio = 0;
	
		while (ADCSPARKFUN.getConfigRegister() & ADCSPARKFUN.BUSY_MASK) == 0 :
			time.sleep(0.100);
	                busyDelay+=1 
			if busyDelay > 100:
				return 0xffff
	
		
	        data = ADCSPARKFUN.adc.readWordReg(ADCSPARKFUN.CONVERSION)        
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
	def getResult(self,channel):
	
	  rawVal = ADCSPARKFUN.getRawResult(channel);
	  return float(rawVal) * ADCSPARKFUN.scaler/1000;
	
	#-----------------------------------------------------------------------
	def setRange(self,range_):
	  cfgRegVal = ADCSPARKFUN.getConfigRegister();
	  cfgRegVal &= ~ADCSPARKFUN.RANGE_MASK;
	  cfgRegVal |= (range_ << ADCSPARKFUN.RANGE_SHIFT) & ADCSPARKFUN.RANGE_MASK;
	  setConfigRegister(cfgRegVal);
	  if range_ == ADCSPARKFUN._6_144V:
	     ADCSPARKFUN.scaler = 3.0;
	  elif range_ == ADCSPARKFUN._4_096V:
	       ADCSPARKFUN.scaler = 2.0;  
	  elif range_ == ADCSPARKFUN._2_048V:
	       ADCSPARKFUN.scaler = 1.0;
	  elif range_ == ADCSPARKFUN._1_024V:
	       ADCSPARKFUN.scaler = 0.5;
	  elif range_ == ADCSPARKFUN._0_512V:
	       ADCSPARKFUN.scaler = 0.25;
	  elif range_ == ADCSPARKFUN._0_256V:
	       ADCSPARKFUN.scaler = 0.125;
	
	#-----------------------------------------------------------------------
	def getScaler(self):
	  return ADCSPARKFUN.scaler;
	#-----------------------------------------------------------------------
	def setOperationMode(self,mode):
	
	  cfgRegVal = ADCSPARKFUN.getConfigRegister();
	  cfgRegVal &= ~ADCSPARKFUN.MODE_MASK;
	  cfgRegVal |= (mode << ADCSPARKFUN.MODE_SHIFT) & ADCSPARKFUN.MODE_MASK;
	  ADCSPARKFUN.setConfigRegister(cfgRegVal);
	#-----------------------------------------------------------------------
	def __init__(self, PORT, ADDRESS):
	  ADCSPARKFUN.adc = mraa.I2c(PORT)
          ADCSPARKFUN.adc.address(ADDRESS)
	   
	#-----------------------------------------------------------------------
	#-----------------------------------------------------------------------
	
	
	#adc = mraa.I2c(1)
	#adc.address(0x48)
	#setRange(_6_144V)
	#print getResult(0)
	#print hex(getConfigRegister())
		
