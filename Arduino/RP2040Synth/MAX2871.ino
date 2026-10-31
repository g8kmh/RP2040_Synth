//Chip specific functions for MAX2871 device
//Adds MAX2871 specific functions
//G8KMH derived from G4EML MAX2870

#define MAX2871CEPin 3         //GPO 3 Connect to Max2871  CE Pin
#define MAX2871MUXPin 4         //GPO 4 Connect to Max2871  MUX_OUT Pin         
#define MAX2871LEPin 5         //GPO 5 Connect to Max2871  LE Pin
#define MAX2871CKPin 6         //GPO 6 Connect to Max2871  CLK Pin 
#define MAX2871DATPin 7         //GPO 7 Connect to Max2871  DATA Pin
#include "SynthChip.h"


//MAX2871 Register bits. Default settings give output at 435.100 MHz with 100MHz reference clock 4MHz PFD.

//Reg 0
bool Max2871_INT;
unsigned int Max2871_N;
unsigned int Max2871_FRAC;

//Reg 1
byte Max2871_CPL;
byte Max2871_CPT;
unsigned int Max2871_P;
unsigned int Max2871_M;

//Reg 2
bool Max2871_LDS;
byte Max2871_SDN;
byte Max2871_MUX;
bool Max2871_DBR;
bool Max2871_RDIV2;
unsigned int Max2871_R;
bool Max2871_REG4DB;
byte Max2871_CP;
bool Max2871_LDF;
bool Max2871_LDP;
bool Max2871_PDP;
bool Max2871_SHDN;
bool Max2871_TRI;
bool Max2871_RST;

//Reg 3
byte Max2871_VCO;
bool Max2871_VAS_SHDN;
bool Max2871_VAS_TEMP; //2871 was RETUNE
bool Max2871_CSM; //2871 only
//bool Max2871_RETUNE;
bool Max2871_MUTEDEL; //2871 only
byte Max2871_CDM;
unsigned int Max2871_CDIV;

//Reg 4
bool Max2871_SDLDO; //2871
bool Max2871_SDDIV; //2871
bool Max2871_SDREF; //2871
byte Max2871_BS_MSBS;
bool Max2871_FB;
byte Max2871_DIVA;
byte Max2871_BS;
bool Max2871_SDVCO; //2871
bool Max2871_MTLD; //2871
bool Max2871_BDIV;
bool Max2871_RFB_EN;
byte Max2871_BPWR;
bool Max2871_RFA_EN;
byte Max2871_APWR;

//Reg 5
byte Max2871_VAS_DLY; //2871
bool Max2871_SDPLL; //2871
bool Max2871_F01;
byte Max2871_LD;
bool Max2871_MUX_MSB;
bool Max2871_ADCS; //2871
byte Max2871_ADCM; //2871


void setDefault(void) override
{
    //Reg 0
  Max2871_INT = 0;
  Max2871_N = 348;
  Max2871_FRAC = 8;

  //Reg 1
  Max2871_CPL = 1;
  Max2871_CPT = 0;
  Max2871_P = 1;
  Max2871_M = 100;

  //Reg 2
  Max2871_LDS = 0;
  Max2871_SDN = 0;
  Max2871_MUX = 6;
  Max2871_DBR = 0;
  Max2871_RDIV2 = 0;
  Max2871_R = 10;
  Max2871_REG4DB = 0;
  Max2871_CP = 15;
  Max2871_LDF = 0;
  Max2871_LDP = 0;
  Max2871_PDP = 1;
  Max2871_SHDN = 0;
  Max2871_TRI = 0;
  Max2871_RST = 0;

  //Reg 3
  Max2871_VCO = 0;
  Max2871_VAS_SHDN = 0;
  Max2871_VAS_TEMP = 0; //was RETUNE
  Max2871_CSM = 0; //2871 only
  Max2871_MUTEDEL = 0 ; //2871
  Max2871_CDM = 0;
  Max2871_CDIV = 1;

  //Reg 4
  Max2871_SDLDO = 0; //2871
  Max2871_SDDIV = 0; //2871
  Max2871_SDREF = 0; //2871
  Max2871_BS_MSBS = 0;
  Max2871_FB = 1;
  Max2871_DIVA = 3;
  Max2871_BS = 80;
  Max2871_SDVCO = 0; //2871
  Max2871_MTLD = 1; //2871 no RF until LOCK DETECT
  Max2871_BDIV = 0;
  Max2871_RFB_EN = 0;
  Max2871_BPWR = 0;
  Max2871_RFA_EN = 1;
  Max2871_APWR = 3;

  //Reg 5
  Max2871_VAS_DLY = 0; //2871
  Max2871_SDPLL = 0; //2871
  Max2871_F01 = 0;
  Max2871_LD = 1;
  Max2871_MUX_MSB = 0;
  Max2871_ADCS = 0; //2871
  Max2871_ADCM = 0; //2871

  

  encodeRegs();
  update();
}

void setParameters(void)
{
  String resp;
  String param;
  String value;
  bool done = false;
  int equals;
  while(!done)
  {
    Serial.print("\nEnter Parameter or ? for help--> ");
    resp = inputString(true);
    if (resp.length() == 0) done = true;
    if(resp.indexOf("?") != -1)
      {
        Serial.println();
        Serial.println("Enter 'Name' to view current Parameter value.");
        Serial.println("Enter 'Name = Value' to set Parameter value.");
        Serial.println("Enter blank line to exit");
        Serial.println("Valid Parameter Names (See Max 2871 Data Sheet) are:-");
        Serial.println("Reg0 = INT N FRAC");
        Serial.println("Reg1 = CPL CPT P M"); 
        Serial.println("Reg2 = LDS SDN MUX DBR RDIV2 R REG4DB CP LDF LDP PDP SHDN TRI RST"); 
        Serial.println("Reg3 = VCO VAS_SHDN VAS_TEMP CSM MUTEDEL CDM CDIV");
        Serial.println("Reg4 = SDLDO SDDIV SDREF BS_MSBS FB DIVA BS SDVCO MTLD BDIV RFB_EN BPWR RFA_EN APWR");
        Serial.println("Reg5 = VAS_DLY SDPLL F01 LD MUX_MSB ADCS ADCM");
        Serial.println();
      }
    
    equals = resp.indexOf("=");

    if(equals > -1)                 // Trying to assigng value
      {
        param = resp.substring(0,equals);
        param.trim();
        value = resp.substring(equals + 1);
        value.trim();
      }
     else
      {
        param = resp;
        param.trim();
        value = "";
      }

// Check each possible Parameter name and process it.

//Reg0
      if(paramBool(param , "INT" , &Max2871_INT , value)) goto handled;
      if(paramUint(param , "N" , &Max2871_N , value , (Max2871_INT == 0) ? 19:16 , (Max2871_INT == 0) ? 4091:65535)) goto handled;
      if(paramUint(param , "FRAC" , &Max2871_FRAC , value , 0 , 4095)) goto handled;

//REG1
      if(paramByte(param , "CPL" , &Max2871_CPL , value , 0 , 3)) goto handled;
      if(paramByte(param , "CPT" , &Max2871_CPT , value , 0 , 3)) goto handled;
      if(paramUint(param , "P" , &Max2871_P , value , 0 , 4095)) goto handled;
      if(paramUint(param , "M" , &Max2871_M , value , 2 , 4095)) goto handled;

//REG2
      if(paramBool(param , "LDS" , &Max2871_LDS , value)) goto handled;
      if(paramByte(param , "SDN" , &Max2871_SDN , value , 0 , 3)) goto handled;
      if(paramByte(param , "MUX" , &Max2871_MUX , value , 0 , 15)) goto handled;
      if(paramBool(param , "DBR" , &Max2871_DBR , value)) goto handled;
      if(paramBool(param , "RDIV2" , &Max2871_RDIV2 , value)) goto handled;
      if(paramUint(param , "R" , &Max2871_R , value , 1 , 1023)) goto handled;
      if(paramBool(param , "REG4DB" , &Max2871_REG4DB , value)) goto handled;
      if(paramByte(param , "CP" , &Max2871_CP , value , 0 , 15)) goto handled;
      if(paramBool(param , "LDF" , &Max2871_LDF , value)) goto handled;
      if(paramBool(param , "LDP" , &Max2871_LDP , value)) goto handled;
      if(paramBool(param , "PDP" , &Max2871_PDP , value)) goto handled;
      if(paramBool(param , "SHDN" , &Max2871_SHDN , value)) goto handled;
      if(paramBool(param , "TRI" , &Max2871_TRI , value)) goto handled;
      if(paramBool(param , "RST" , &Max2871_RST , value)) goto handled;

//REG3
      if(paramByte(param , "VCO" , &Max2871_VCO , value , 0 , 63)) goto handled;
      if(paramBool(param , "VAS_SHDN" , &Max2871_VAS_SHDN , value)) goto handled;
      if(paramBool(param , "VAS_TEMP" , &Max2871_VAS_TEMP , value)) goto handled;
      if(paramBool(param , "CSM" , &Max2871_CSM , value)) goto handled;
      if(paramBool(param , "MUTEDEL" , &Max2871_MUTEDEL , value)) goto handled;
      if(paramByte(param , "CDM" , &Max2871_CDM , value , 0 , 3)) goto handled;
      if(paramUint(param , "CDIV" , &Max2871_CDIV , value , 1 , 4095)) goto handled;

//REG4
      if(paramBool(param , "SDLDO" , &Max2871_SDLDO , value)) goto handled;
      if(paramBool(param , "SDDIV" , &Max2871_SDDIV , value)) goto handled;
      if(paramBool(param , "SDREF" , &Max2871_SDREF , value)) goto handled;
      if(paramByte(param , "BS_MSBS" , &Max2871_BS_MSBS , value , 0 , 3)) goto handled;
      if(paramBool(param , "FB" , &Max2871_FB , value)) goto handled;
      if(paramByte(param , "DIVA" , &Max2871_DIVA , value , 0 , 7)) goto handled;
      if(paramByte(param , "BS" , &Max2871_BS , value , 1 , 255)) goto handled;
      if(paramBool(param , "SDVCO" , &Max2871_SDVCO , value)) goto handled;
      if(paramBool(param , "MTLD" , &Max2871_MTLD , value)) goto handled;
      if(paramBool(param , "BDIV" , &Max2871_BDIV , value)) goto handled;
      if(paramBool(param , "RFB_EN" , &Max2871_RFB_EN , value)) goto handled;
      if(paramByte(param , "BPWR" , &Max2871_BPWR , value , 0 , 3)) goto handled;
      if(paramBool(param , "RFA_EN" , &Max2871_RFA_EN , value)) goto handled;
      if(paramByte(param , "APWR" , &Max2871_APWR , value , 0 , 3)) goto handled;

//REG5
      if(paramByte(param , "VAS_DLY" , &Max2871_VAS_DLY , value, 0 , 3)) goto handled;
      if(paramBool(param , "SDPLL" , &Max2871_SDPLL , value)) goto handled;
      if(paramBool(param , "F01" , &Max2871_F01 , value)) goto handled;
      if(paramByte(param , "LD" , &Max2871_LD , value , 0 , 3)) goto handled;
      if(paramBool(param , "MUX_MSB" , &Max2871_MUX_MSB , value)) goto handled;
      if(paramBool(param , "ADCS" , &Max2871_ADCS , value)) goto handled;
      if(paramByte(param , "ADCM" , &Max2871_ADCM , value , 0 , 7)) goto handled;


    handled:
    encodeRegs();
    update();

  }
}

void init(void) override
{
//  int chip = MAX2871;                  //index to the current chip type
  numberOfRegs = 6;                   //number of registers in the current chip type
  numberOfBits = 32;                   //number of bits in each register
  maxPfd = 50.0;                      //maximum PFD frequency
  minPfd = 0;
  maxOsc = 201;
  minOsc = 10;
  jt4Only = true;
  pinMode(MAX2871CEPin,OUTPUT);
  digitalWrite(MAX2871CEPin,HIGH); 
  pinMode(MAX2871LEPin,OUTPUT);
  digitalWrite(MAX2871LEPin,HIGH);
  SPI.setRX(MAX2871MUXPin);
  SPI.setTX(MAX2871DATPin);
  SPI.setSCK(MAX2871CKPin);
  SPI.beginTransaction(SPISettings(400000,MSBFIRST,SPI_MODE0));
  SPI.begin();
}

void Max2871Send(int32_t val)
{
  int a=(val >> 24) & 0xFF;
  int b=(val >> 16) & 0xFF;
  int c=(val >> 8) & 0xFF;
  int d=val & 0xFF;
  
  digitalWrite(MAX2871LEPin,LOW);
  delayMicroseconds(10);
  SPI.transfer((byte)a);
  SPI.transfer((byte)b);
  SPI.transfer((byte)c);
  SPI.transfer((byte)d);
  delayMicroseconds(10);
  digitalWrite(MAX2871LEPin,HIGH);
  delayMicroseconds(10);  
}


void Max2871EncodeRegs(void)
{
  chanData[channel].reg[0] = (Max2871_INT << 31) | (Max2871_N << 15) | (Max2871_FRAC << 3);
  chanData[channel].reg[1] = (Max2871_CPL << 29) | (Max2871_CPT << 27) | (Max2871_P << 15) | (Max2871_M << 3) | 1 ;
  chanData[channel].reg[2] = (Max2871_LDS << 31) | (Max2871_SDN << 29) | (Max2871_MUX << 26) | (Max2871_DBR << 25) | (Max2871_RDIV2 << 24) | (Max2871_R << 14) | (Max2871_REG4DB <<13) | (Max2871_CP << 9) | (Max2871_LDF << 8) | (Max2871_LDP << 7) | (Max2871_PDP << 6) | (Max2871_SHDN << 5) | (Max2871_TRI << 4) | (Max2871_RST << 3) | 2;
  chanData[channel].reg[3] = (Max2871_VCO << 26) | (Max2871_VAS_SHDN << 25) | (Max2871_VAS_TEMP << 24) | (Max2871_CSM << 18) | (Max2871_MUTEDEL << 17) | (Max2871_CDM << 15) | (Max2871_CDIV << 3) | 3;
  chanData[channel].reg[4] = (3 << 29) | (Max2871_SDLDO << 28) |  (Max2871_SDDIV << 27) |  (Max2871_SDREF << 26) |  (Max2871_BS_MSBS << 24) | (Max2871_FB << 23) | (Max2871_DIVA << 20) | (Max2871_BS << 12) | (Max2871_SDVCO << 11) |  (Max2871_MTLD << 10) |  (Max2871_BDIV << 9) | (Max2871_RFB_EN << 8) | (Max2871_BPWR << 6) | (Max2871_RFA_EN << 5) | (Max2871_APWR << 3) | 4;
  chanData[channel].reg[5] = (Max2871_VAS_DLY << 29) |  (Max2871_SDPLL << 25) | (Max2871_F01 << 24) | (Max2871_LD << 22) | (Max2871_MUX_MSB << 18) | (Max2871_ADCS << 6) | (Max2871_ADCM << 3) | 5; 
}

void Max2871DecodeRegs(void)
{
  Max2871_INT = (chanData[channel].reg[0] >> 31) & 0x01;
  Max2871_N = (chanData[channel].reg[0] >> 15) & 0xFFFF;
  Max2871_FRAC = (chanData[channel].reg[0] >> 3) & 0xFFF;

  Max2871_CPL = (chanData[channel].reg[1] >> 29) & 0x03;
  Max2871_CPT = (chanData[channel].reg[1] >> 27) & 0x03;
  Max2871_P = (chanData[channel].reg[1] >> 15) & 0x0FFF; 
  Max2871_M = (chanData[channel].reg[1] >> 3) & 0x0FFF;

  Max2871_LDS = (chanData[channel].reg[2] >> 31) & 0x01;
  Max2871_SDN = (chanData[channel].reg[2] >> 29) & 0x03;
  Max2871_MUX = (chanData[channel].reg[2] >> 26) & 0x0F;
  Max2871_DBR = (chanData[channel].reg[2] >> 25) & 0x01; 
  Max2871_RDIV2 = (chanData[channel].reg[2] >> 24) & 0x01; 
  Max2871_R = (chanData[channel].reg[2] >> 14) & 0x3FF; 
  Max2871_REG4DB = (chanData[channel].reg[2] >> 13) & 0x01;
  Max2871_CP = (chanData[channel].reg[2] >> 9) & 0x0F;
  Max2871_LDF = (chanData[channel].reg[2] >> 8) & 0x01;
  Max2871_LDP = (chanData[channel].reg[2] >> 7) & 0x01;
  Max2871_PDP = (chanData[channel].reg[2] >> 6) & 0x01;
  Max2871_SHDN = (chanData[channel].reg[2] >> 5) & 0x01; 
  Max2871_TRI = (chanData[channel].reg[2] >> 4) & 0x01;
  Max2871_RST = (chanData[channel].reg[2] >> 3) & 0x01;

  Max2871_VCO = (chanData[channel].reg[3] >> 26) & 0x3F;
  Max2871_VAS_SHDN = (chanData[channel].reg[3] >> 25) & 0x01;
  Max2871_VAS_TEMP = (chanData[channel].reg[3] >> 24) & 0x01;
  Max2871_CSM = (chanData[channel].reg[3] >> 18) & 0x01;
  Max2871_MUTEDEL = (chanData[channel].reg[3] >> 18) & 0x01;
  Max2871_CDM = (chanData[channel].reg[3] >> 15) & 0x03;
  Max2871_CDIV = (chanData[channel].reg[3] >> 3) & 0xFFF;

  Max2871_SDLDO = (chanData[channel].reg[4] >> 28) & 0x01;
  Max2871_SDDIV = (chanData[channel].reg[4] >> 27) & 0x01;
  Max2871_SDREF = (chanData[channel].reg[4] >> 26) & 0x01;
  Max2871_BS_MSBS = (chanData[channel].reg[4] >> 24) & 0x03;
  Max2871_FB = (chanData[channel].reg[4] >> 23) & 0x01;
  Max2871_DIVA = (chanData[channel].reg[4] >> 20) & 0x07;
  Max2871_BS = (chanData[channel].reg[4] >> 12) & 0xFF;
  Max2871_SDVCO = (chanData[channel].reg[4] >> 11) & 0x01;
  Max2871_MTLD = (chanData[channel].reg[4] >> 10) & 0x01;
  Max2871_BDIV = (chanData[channel].reg[4] >> 9) & 0x01;
  Max2871_RFB_EN = (chanData[channel].reg[4] >> 8) & 0x01;
  Max2871_BPWR = (chanData[channel].reg[4] >> 6) & 0x03;
  Max2871_RFA_EN = (chanData[channel].reg[4] >> 5) & 0x01; 
  Max2871_APWR = (chanData[channel].reg[4] >> 3) & 0x03;

  Max2871_VAS_DLY = (chanData[channel].reg[5] >> 29) & 0x03;
  Max2871_SDPLL = (chanData[channel].reg[5] >> 25) & 0x01;
  Max2871_F01 = (chanData[channel].reg[5] >> 24) & 0x01;
  Max2871_LD = (chanData[channel].reg[5] >> 22) & 0x03;
  Max2871_MUX_MSB = (chanData[channel].reg[5] >> 18) & 0x01;
  Max2871_ADCS = (chanData[channel].reg[5] >> 6) & 0x01;
  Max2871_ADCM = (chanData[channel].reg[5] >> 3) & 0x07;

}

void update(void) override
{
  Max2871Send(chanData[channel].reg[5]);
  Max2871Send(chanData[channel].reg[4]);
  Max2871Send(chanData[channel].reg[3]);
  Max2871Send(chanData[channel].reg[2]);
  Max2871Send(chanData[channel].reg[1]);
  Max2871Send(chanData[channel].reg[0]);
}


double calcPFD(double rpfd)
{
  double r = 0;
  bool dub = 0;
  bool div = 0;
  double setpfd = 0;
  uint16_t bs = 0;

  //first try a simple division...
  r = refOsc / rpfd;
if(fabs(((double) int(r)) - r) < 0.000001 )      {
      goto done;
    }

  //next try using the doubler

  dub = 1;
  r = (refOsc * 2.0) / rpfd;
if(fabs(((double) int(r)) - r) < 0.000001 )      {
      goto done;
    }


  Serial.print("Unable to acheive a PFD of ");
  Serial.print(rpfd, 6);
  Serial.print(" MHz With a Ref Oscillator of ");
  Serial.print(refOsc, 6);
  Serial.println(" MHz");
  Serial.println("PFD has not been changed");

  return getPfd();
  done:
  if(r < 1)  r = 1;
  Max2871_R = r;
  Max2871_DBR = dub;
  Max2871_RDIV2 = div;

  setpfd = ((refOsc * (1+dub)) / r);

  bs = setpfd/0.0500;              // band select clock should be fPFD/50Khz.
  if(bs <1) bs =1;
  if(bs > 1023) bs = 1023;
  Max2871_BS = bs & 0xFF;
  Max2871_BS_MSBS = (bs >> 8) & 0x03;

  if(setpfd > 32.0) 
   {
    Max2871_LDS = 1;
   }
  else
  {
   Max2871_LDS = 0;
  }
  Serial.print("PFD changed to ");
  Serial.print(setpfd , 6);
  Serial.println("MHz");
  return setpfd;
}
double getPfd(void)
{
  double pfd = refOsc;
  double r = (double) Max2871_R;
  if(Max2871_DBR == 1) pfd = pfd * 2.0;
  pfd = pfd / r;
  if (Max2871_RDIV2 == 1) pfd = pfd / 2.0;
  return pfd;
}

void Max2871SetFrequency(double direct)
{
  bool freqOK = false;

  double freq;
  double pfd;
  double n;
  double part;
  double err;
  int nom;
  int den;
  int bestnom;
  int bestden;
  char resp;

  pfd = getPfd();

  freqOK = false;
  if(direct ==0)
  {
   while(!freqOK)
    {
      if(chanData[channel].extMult > 1)
      {
      Serial.print("\nEnter Required Final Multiplied Frequency in MHz -->");
      freq = inputFloat() / (double) chanData[channel].extMult;
      }
      else
      {
      Serial.print("\nEnter Required Frequency in MHz -->");
      freq = inputFloat();        
      }
      if((freq > 23.500) && (freq <= 6000.000))
        {
          freqOK = true;
        }
      else
        {
          Serial.println("Synthesiser Frequency must be between 23.5 and 6000 MHz");
        }
    }
  }
  else
  {
    freq = direct;
  }
//Calculate the required output divider
  if(freq >= 3000.000)  Max2871_DIVA = 0;
  if((freq >= 1500.000) && (freq < 3000.000))  Max2871_DIVA = 1;
  if((freq >= 750.000) && (freq < 1500.000))  Max2871_DIVA = 2;
  if((freq >= 375.000) && (freq < 750.000))  Max2871_DIVA = 3; 
  if((freq >= 187.500) && (freq < 375.000))  Max2871_DIVA = 4;
  if((freq >= 93.750) && (freq < 187.500))  Max2871_DIVA = 5;
  if((freq >= 46.875) && (freq < 93.750))  Max2871_DIVA = 6;
  if((freq >= 23.500) && (freq < 46.875))  Max2871_DIVA = 7;

//adjust the frequency to allow for the output division
  freq = freq * (1 << Max2871_DIVA);

  n = freq / pfd;

  Max2871_N = (unsigned int) n;
  n = n - (unsigned int) n;

  //n now has the desired fractional part. Now we need to work put the best f/d to acheive this
   err = 1.0;
   bestnom = 0;
   bestden = 2;
   for(den = 2; den <= 4095 ; den++)
     {
      nom = int((den * n) + 0.0000000001 );
      if(nom < 1) continue;
      part = (double) nom / (double) den;
      if(abs(part-n) < 0.0000000001)
        {
          bestnom = nom;
          bestden = den;
          err = 0;
          goto done;
        }
      if(abs((part - n)) < err)
        {
            bestnom = nom;
            bestden = den;
            err = abs(part - n);
        }
     }

  done:
//program the fraction division
  Max2871_M = bestden;
  Max2871_FRAC = bestnom;

  encodeRegs();
}


void calcFreq(void) override
{
  double pfd;
  double vco;
  double n;
  double m;
  double f;
  double nf;

  uint8_t diva;

  diva = 1 << Max2871_DIVA;

  n = (double) Max2871_N;
  m = (double) Max2871_M;
  f = (double) Max2871_FRAC;

  Serial.println();
  Serial.print("Chip type is ");
  Serial.println(name);
  Serial.print("Reference Oscillator = ");
  Serial.print(refOsc,10);
  Serial.println(" MHz");


  pfd = getPfd();


  Serial.print("PFD = ");
  Serial.print(pfd , 10);
  Serial.println(" MHz");

  if(Max2871_INT == 0)
  {
     if(Max2871_FB == 1)
       {
         nf = n + (f/m);
       }
      else
       {
          nf = (n + (f / m)) * diva;
       }
  }
  else
  {
         if(Max2871_FB == 1)
       {
         nf =  n ;
       }
      else
       {
          nf = n * diva;
       }

  }

  vco = pfd * nf;

  Serial.print("N = ");
  Serial.print(nf , 10);
  Serial.print(" ( ");
  Serial.print(int(n));
  Serial.print(" + (");
  Serial.print(int(f));
  Serial.print("/");
  Serial.print(int(m));
  Serial.println(") )");

  Serial.print("VCO = ");
  Serial.print(vco , 10);
  Serial.println(" MHz");

  Serial.print("O/P Divider = /");
  Serial.println(diva);

  Serial.print("Output Frequency = ");
  Serial.print(vco / diva , 10);
  Serial.println(" MHz");

  if(chanData[channel].extMult > 1)
    {
      Serial.print("External Multipler = X");
      Serial.println(chanData[channel].extMult);
      Serial.print("Final Multiplied Frequency = ");
      Serial.print((vco / diva) * (double) chanData[channel].extMult, 10);
      Serial.println(" MHz"); 
    }
}

double getFrequency(void) override
{
  double pfd;
  double vco;
  double n;
  double m;
  double f;
  double nf;

  uint8_t diva;

  diva = 1 << Max2871_DIVA;

  n = (double) Max2871_N;
  m = (double) Max2871_M;
  f = (double) Max2871_FRAC;

  pfd = getPfd();

  if(Max2871_INT == 0)
  {
     if(Max2871_FB == 1)
       {
         nf = n + (f/m);
       }
      else
       {
          nf = (n + (f / m)) * diva;
       }
  }
  else
  {
         if(Max2871_FB == 1)
       {
         nf =  n ;
       }
      else
       {
          nf = n * diva;
       }

  }

  vco = pfd * nf;

  return vco / diva;
}

 void jtShift(uint8_t val)
{
  static uint8_t lastval;
  
  if(val == lastval) return;
  lastval = val;

   Max2871Send((chanData[channel].reg[1] & 0xFFFF8007) | (jtDen[val] << 3));
   Max2871Send((chanData[channel].reg[0] & 0x80000007) | (jtN[val] << 15) | (jtNum[val] <<3));

}

  void fskKey(bool key)
{
  static bool lastkey;
  
  if(key == lastkey) return;
  lastkey = key;

  if(key)
    {
      Max2871Send(chanData[channel].reg[1]);
      Max2871Send(chanData[channel].reg[0]);
    }
  else
    {
      Max2871Send((chanData[channel].reg[1] & 0xFFFF8007) | (cwidKeyUpDen << 3));
      Max2871Send((chanData[channel].reg[0] & 0x80000007) | (cwidKeyUpN << 15) | (cwidKeyUpNum <<3));
    }
}

  void extKey(bool key) override
{
  if(key)
    {
      Max2871Send(chanData[channel].reg[1]);
      Max2871Send(chanData[channel].reg[0]);
    }
  else
    {
      Max2871Send((chanData[channel].reg[1] & 0xFFFF8007) | (ExtKeyUpDen << 3));
      Max2871Send((chanData[channel].reg[0] & 0x80000007) | (ExtKeyUpN << 15) | (ExtKeyUpNum <<3));
    }
}

void saveFskShift(void) override
{
  cwidKeyUpN = Max2871_N;
  cwidKeyUpDen = Max2871_M;
  cwidKeyUpNum = Max2871_FRAC;
}

void saveKeyShift(void) override
{
  ExtKeyUpN = Max2871_N;
  ExtKeyUpDen = Max2871_M;
  ExtKeyUpNum = Max2871_FRAC;
}

void saveJt(uint8_t index) override
{
  jtN[index] = Max2871_N;
  jtDen[index] = Max2871_M;
  jtNum[index] = Max2871_FRAC;
}

//--- RF output power/enable control, used by the touchscreen UI ---
uint8_t getPower(void) override { return Max2870_APWR; }
void setPower(uint8_t p) override
{
  if(p>3) p=3;
  Max2870_APWR = p;
  encodeRegs();
  update();
}
bool getOutput(void) override { return Max2871_RFA_EN; }
void enableOutput(bool o) override
{
  Max2871_RFA_EN = o;
  encodeRegs();
  update();
}

};

Max2871Chip max2871Chip;             //the single instance of this chip driver
