// LMX2820 code - G8KMH g8kmh@mm-wave.com
// Extended from G4ELM LMX2595 code
//Chip specific functions for LMX2820 device

#define LMX2820CEPin 3   //GPO 3 Connect to LMX2820  CE Pin
#define LMX2820MUXPin 4  //GPO 4 Connect to LMX2820  MUXout Pin
#define LMX2820CSBPin 5  //GPO 5 Connect to LMX2820  CSB Pin
#define LMX2820SCKPin 6  //GPO 6 Connect to LMX2820  SCK Pin
#define LMX2820SDIPin 7  //GPO 7 Connect to LMX2820  SDI Pin
#define LMX2820MUTEPin 2 //GPO 2 Connect to LMX2820 Mute pin 
#include "SynthChip.h"

class LMX2820Chip : public SynthChip
{
public:

LMX2820Chip() { name = "LMX2820"; }

// R0-R79 use their hardware addresses as channel slots. V2 has 80 slots;
// the unused/read-only R71 slot stores the complete R80 write word instead.
// This preserves the existing V2 EEPROM/channel layout. R80 is sent separately
// before descending R79-R0 writes. Raw-register slot 71 therefore represents R80.
static constexpr byte OUTB_POWER_SLOT = 71;

//LMX2820 Register Parameters.



//Reg 0
bool LMX2820_INSTCAL_SKIP_ACAL;
byte LMX2820_FCAL_HPFD_ADJ;
byte LMX2820_FCAL_LPFD_ADJ;
bool LMX2820_DBLR_CAL_EN;
bool LMX2820_FCAL_EN;
bool LMX2820_RESET;
bool LMX2820_POWERDOWN;
//Reg 1
bool LMX2820_PHASE_SYNC_EN;
bool LMX2820_LD_VTUNE_EN;
bool LMX2820_INSTCAL_DBLR_EN;
bool LMX2820_INSTCAL_EN;
// Reg 2
byte LMX2820_CAL_CLK_DIV;
unsigned int LMX2820_INSTCAL_DLY;
bool LMX2820_QUICKRECAL_EN;
//Reg 6
byte LMX2820_ACAL_CMP_DLY;
//Reg 10
bool LMX2820_PFD_DLY_MANUAL;
bool LMX2820_VCO_DACISET_FORCE;
bool LMX2820_VCO_CAPCTRL_FORCE;
//Reg 11
bool LMX2820_OSC_2X;
//Reg 12
byte LMX2820_MULT;
//Reg 13
byte LMX2820_PLL_R;
//Reg 14
unsigned int LMX2820_PLL_R_PRE;
//Reg 15
bool LMX2820_PFD_POL;
byte LMX2820_PFD_SINGLE;
//Reg 16
byte LMX2820_CPG;

//unsigned int LMX2820_VCO_DACISET;
//Reg 17
bool LMX2820_LD_TYPE;
//Reg 18
uint32_t LMX2820_LD_DLY;

//unsigned int LMX2820_VCO_DACISET_STRT;
//Reg 19
byte LMX2820_TEMPSENSE_EN;
//Reg 20
unsigned int LMX2820_VCO_DACISET;
//Reg 22
byte LMX2820_VCO_SEL;
byte LMX2820_VCO_CAPCTRL;
//Reg 23
bool LMX2820_VCO_SEL_FORCE;
//Reg 32
byte LMX2820_CHDIVB;
byte LMX2820_CHDIVA;
//Reg34
bool LMX2820_LOOPBACK_EN;
bool LMX2820_EXTVCO_DIV;
bool LMX2820_EXTVCO_EN;
//Reg 35
bool LMX2820_MASH_RESET_N;
byte LMX2820_MASH_ORDER;
bool LMX2820_MASHSEED_EN;
//Reg 36
uint32_t LMX2820_PLL_N;
//Reg 37
byte LMX2820_PFD_DLY;
//Reg 38
unsigned int LMX2820_PLL_DENH;  //High 16 bits
//Reg 39
unsigned int LMX2820_PLL_DENL;  //Low 16 bits
//combined 32 bit variable for convenience
uint32_t LMX2820_PLL_DEN;
//Reg 40
unsigned int LMX2820_MASH_SEEDH;  //High 16 bits
//Reg 41
unsigned int LMX2820_MASH_SEEDL;  //Low 16 bits
//combined 32 bit variable for convenience
uint32_t LMX2820_MASH_SEED;
//Reg 42
unsigned int LMX2820_PLL_NUMH;  //High 16 bits
//Reg 43
unsigned int LMX2820_PLL_NUML;  //Low 16 bits
//combined 32 bit variable for convenience
uint32_t LMX2820_PLL_NUM;
//Reg 44
unsigned int LMX2820_INSTCAL_PLL_NUMH;  //High 16 bits
//Reg 45
unsigned int LMX2820_INSTCAL_PLL_NUML;  //Low 16 bits
//combined 32 bit variable for convenience
uint32_t LMX2820_INSTCAL_PLL_NUM;
//Reg 56
unsigned int LMX2820_EXTPFD_DIV;
//Reg 57
bool LMX2820_PFD_SEL;
//Reg 62
uint32_t LMX2820_MASH_RST_COUNTH;
//Reg 63
uint32_t LMX2820_MASH_RST_COUNTL;
//combined 32 bit variable for convenience
uint32_t LMX2820_MASH_RST_COUNT;
//Reg 64
byte LMX2820_SYSREF_INP_FMT;
byte LMX2820_SYSREF_DIV_PRE;
bool LMX2820_SYSREF_REPEAT_NS;
bool LMX2820_SYSREF_PULSE;
bool LMX2820_SYSREF_EN;
bool LMX2820_SYSREF_REPEAT;
//Reg 65
uint32_t LMX2820_SYSREF_DIV;
//Reg 66
byte LMX2820_JESD_DAC2_CTRL;
byte LMX2820_JESD_DAC1_CTRL;
//Reg67
byte LMX2820_SYSREF_PULSE_CNT;
byte LMX2820_JESD_DAC4_CTRL;
byte LMX2820_JESD_DAC3_CTRL;
//Reg 68
bool LMX2820_INPIN_IGNORE;
bool LMX2820_PSYNC_INP_FMT;
//Reg 69
bool LMX2820_SROUT_PD;
//Reg 70
bool LMX2820_DBLBUF_OUTMUX_EN;
bool LMX2820_DBLBUF_OUTBUF_EN;
bool LMX2820_DBLBUF_CHDIV_EN;
bool LMX2820_DBLBUF_PLL_EN;
//Reg 77
bool LMX2820_PINMUTE_POL;
//Reg 78
bool LMX2820_OUTA_PD;
byte LMX2820_OUTA_MUX;
//Reg 79
bool LMX2820_OUTB_PD;
byte LMX2820_OUTB_MUX;
byte LMX2820_OUTA_PWR;
//Reg 80
byte LMX2820_OUTB_PWR;
//Ramping and readback Registers R81 - R122 not used so not included.




void setDefault(void) override
// Sets to 10368.1 as default startup
{
  //Reg 0 0x6470
  LMX2820_INSTCAL_SKIP_ACAL = 1;
  LMX2820_FCAL_HPFD_ADJ = 2;
  LMX2820_FCAL_LPFD_ADJ = 0;
  LMX2820_DBLR_CAL_EN = 0;
  LMX2820_FCAL_EN = 0; // Set later on chip update
  LMX2820_RESET = 0;
  LMX2820_POWERDOWN = 0;
  //Reg 1 47A0
  LMX2820_PHASE_SYNC_EN = 0;
  //0x15E
  LMX2820_LD_VTUNE_EN = 1;
  LMX2820_INSTCAL_EN = 0;
  LMX2820_INSTCAL_DBLR_EN = 0;
  //Reg 2 81F4
  LMX2820_CAL_CLK_DIV = 0; // OSCIN <= 200 MHz
  LMX2820_INSTCAL_DLY = 0xFA;
  LMX2820_QUICKRECAL_EN = 0;

  //Reg 6
  LMX2820_ACAL_CMP_DLY = 0x0A;  //0x0A on reset
  //Reg 7 0x00
  //Reg 8 0xC802
  //Reg 9 0x5
  //Reg 10
  //LMX2820_OUT_FORCE = 1;
  //Reg 8
  LMX2820_PFD_DLY_MANUAL = 0;
  LMX2820_VCO_DACISET_FORCE = 0;
  LMX2820_VCO_CAPCTRL_FORCE = 0;
  //Reg 11
  LMX2820_OSC_2X = 1;  // !00MHz doubled to 200MHz 10GHz output
  //Reg 12
  LMX2820_MULT = 1;
  //Reg 13
  LMX2820_PLL_R = 1;
  //Reg 14
  LMX2820_PLL_R_PRE = 1;
  //Reg 15
  LMX2820_PFD_SINGLE = 0;
  LMX2820_PFD_POL = 0;
  //Reg 16
  LMX2820_CPG = 0x0D;  //14mA
  //Reg 17
  LMX2820_LD_TYPE = 1;  // check lock continously (LD maybe used for TX inhibit someplace)
  //Reg 18
  LMX2820_LD_DLY = 0x3E8;  //As default but may need changing
  //Reg 19
  LMX2820_TEMPSENSE_EN = 0;
  //Reg 20
  LMX2820_VCO_DACISET = 0x12C;
  //Reg 22
  LMX2820_VCO_SEL = 7;  // For 12024.050
  LMX2820_VCO_CAPCTRL = 0xBF;
  //Reg 32
  LMX2820_CHDIVB = 0;
  LMX2820_CHDIVA = 0;
  //Reg 34
  LMX2820_LOOPBACK_EN = 0;
  LMX2820_EXTVCO_DIV = 1;
  LMX2820_EXTVCO_EN = 0;

  //Reg 35
  LMX2820_MASH_RESET_N = 1;
  LMX2820_MASH_ORDER = 0x0;
  LMX2820_MASHSEED_EN = 0;
  //Reg 36
  LMX2820_PLL_N = 0x001E;
 
  // Reg 37
  LMX2820_PFD_DLY = 2;
  //Reg 38
  LMX2820_PLL_DENH = 0x00;  //High 16 bits
  //Reg 39
  LMX2820_PLL_DENL = 0x01;  //Low 16 bits
  //combined 32 bit variable for convenience
  LMX2820_PLL_DEN = 0x0001;  //0x0001
  //Reg 40
  LMX2820_MASH_SEEDH = 0;  //High 16 bits
  //Reg 41
  LMX2820_MASH_SEEDL = 0;  //Low 16 bits
  //combined 32 bit variable for convenience
  LMX2820_MASH_SEED = 0;
  //Reg 42
  LMX2820_PLL_NUMH = 0;  //High 16 bits
  //Reg 43
  LMX2820_PLL_NUML = 0;  //Low 16 bits
  //combined 32 bit variable for convenience
  LMX2820_PLL_NUM = 0;
  //Reg 44
  LMX2820_INSTCAL_PLL_NUMH = 0;  //High 16 bits
  //Reg 45
  LMX2820_INSTCAL_PLL_NUML = 0;  //Low 16 bits
  //combined 32 bit variable for convenience
  LMX2820_INSTCAL_PLL_NUM = 0;
  // Reg 56
  LMX2820_EXTPFD_DIV = 1;
  //Reg 57
  LMX2820_PFD_SEL = 1;
  //Reg 62
  LMX2820_MASH_RST_COUNTH = 0;  //High 16 bits
  //Reg 63
  LMX2820_MASH_RST_COUNTL = 0x3E8;  //Low 16 bits
  //combined 32 bit variable for convenience
  LMX2820_MASH_RST_COUNT = 0x03E8;
  //Reg 64
  LMX2820_SYSREF_INP_FMT = 0;
  LMX2820_SYSREF_DIV_PRE = 4;
  LMX2820_SYSREF_PULSE = 0;
  LMX2820_SYSREF_REPEAT_NS = 0;
  LMX2820_SYSREF_EN = 0;
  LMX2820_SYSREF_REPEAT = 0;
  //Reg 65
  LMX2820_SYSREF_DIV = 0;
  //Reg 66
  LMX2820_JESD_DAC2_CTRL = 0;
  LMX2820_JESD_DAC1_CTRL = 0x3F;
  //Reg 67
  LMX2820_SYSREF_PULSE_CNT = 0;
  LMX2820_JESD_DAC4_CTRL = 0;
  LMX2820_JESD_DAC3_CTRL = 0;
  //Reg 68
  LMX2820_INPIN_IGNORE = 0;
  LMX2820_PSYNC_INP_FMT = 0;
  //Reg 69
  LMX2820_SROUT_PD = 1;
  //Reg 70
  LMX2820_DBLBUF_OUTMUX_EN = 0;
  LMX2820_DBLBUF_OUTBUF_EN = 0;
  LMX2820_DBLBUF_CHDIV_EN = 0;
  LMX2820_DBLBUF_PLL_EN = 0;
  //Reg 77
  LMX2820_PINMUTE_POL = 0;
  //Reg 78
  LMX2820_OUTA_PD = 0;
  LMX2820_OUTA_MUX = 1;
  //Reg 79
  LMX2820_OUTB_PD = 1;
  LMX2820_OUTB_MUX = 1;
  LMX2820_OUTA_PWR = 7;
  //Reg 80
  LMX2820_OUTB_PWR = 0;

  chanData[channel].extMult = 1;
  chanData[channel].fskMode = 0;
  chanData[channel].jtMode = 0;
  setFrequency(0);
  encodeRegs();
  update();
}

// Driver-local helpers: the V2 shared menu has no reserved-value helper.
bool LMX2820ParamByteReserved(String param, String name, byte* var, String value,
                             byte minimum, byte maximum, byte reserved[], byte count)
{
  if (param != name) return false;
  if (value.length()) {
    char* end = nullptr;
    unsigned long parsed = strtoul(value.c_str(), &end, 10);
    bool valid = value[0] >= '0' && value[0] <= '9' && *end == 0 && parsed >= minimum && parsed <= maximum;
    for (byte i = 0; i < count; ++i) if (parsed == reserved[i]) valid = false;
    if (valid) *var = (byte)parsed;
    else Serial.println("Invalid or reserved value; unchanged.");
  }
  Serial.print(param); Serial.print(" = "); Serial.println(*var);
  return true;
}

bool LMX2820ParamUint32(String param, String name, uint32_t* var, String value,
                      uint32_t minimum, uint32_t maximum)
{
  if (param != name) return false;
  if (value.length()) {
    char* end = nullptr;
    unsigned long long parsed = strtoull(value.c_str(), &end, 10);
    if (value[0] >= '0' && value[0] <= '9' && *end == 0 && parsed >= minimum && parsed <= maximum) *var = (uint32_t)parsed;
    else Serial.println("Invalid value; unchanged.");
  }
  Serial.print(param); Serial.print(" = "); Serial.println(*var);
  return true;
}

void setParameters(void) override {
  String resp;
  String param;
  String value;
  bool done = false;
  int equals;
  byte rsrvd12[] = { 1, 2 };
  byte rsrvd3[] = { 3 };
  byte rsrvd2[] = { 2 };
  byte rsrvdCpg[] = { 2, 3, 10, 11 };
  while (!done) {
    Serial.print("\nEnter Parameter or ? for help--> ");
    resp = inputString(true);
    if (resp.length() == 0) done = true;
    if (resp.indexOf("?") != -1) {
      Serial.println();
      Serial.println("Enter 'Name' to view current Parameter value.");
      Serial.println("Enter 'Name = Value' to set Parameter value.");
      Serial.println("Enter blank line to exit");
      Serial.println("Valid Parameter Names (See LMX2820 Data Sheet for details) are:-");
      Serial.println("Reg 0 = INSTCAL_SKIP_ACAL FCAL_HPFD_ADJ FCAL_LPFD_ADJ DBLR_CAL_EN FCAL_EN RESET POWERDOWN");
      Serial.println("Reg 1 = PHASE_SYNC_EN LD_VTUNE_EN INSTCAL_DBLR_EN INSTCAL_EN");
      Serial.println("Reg 2 = CAL_CLK_DIV INSTCAL_DLY QUICKRECAL_EN");
      Serial.println("Reg 6 = ACAL_CMP_DELAY");
      Serial.println("Reg 10 = OUT_PFD_DLY_MANUAL VCO_DACISET_FORCE VCO_CAPCTRL_FORCE");
      Serial.println("Reg 11 = OSC_2X");
      Serial.println("Reg 12 = MULT");
      Serial.println("Reg 13 = PLL_R");
      Serial.println("Reg 14 = PLL_R_PRE");
      Serial.println("Reg 15 = PFD_POL PFD_SINGLE");
      Serial.println("Reg 16 = CPG");
      Serial.println("Reg 18 = LD_DLY");
      Serial.println("Reg 19 = TEMPSENSE_EN");
      Serial.println("Reg 20 = VCO_DACISET");
      Serial.println("Reg 22 = VCO_SEL VCO_CAPCTRL");
      Serial.println("Reg 23 = VCO_SEL_FORCE");
      Serial.println("Reg 32 = CHDIVA CHDIVB");
      Serial.println("R34 LOOPBACK_EN EXTVCO_DIV EXTVCO_EN; R35 MASH_RESET_N MASH_ORDER MASHSEED_EN");
      Serial.println("R36 PLL_N; R37 PFD_DLY; R38/39 PLL_DEN; R40/41 MASH_SEED; R42/43 PLL_NUM");
      Serial.println("R44/45 INSTCAL_PLL_NUM (instant calibration initialization not implemented)");
      Serial.println("R62/63 MASH_RST_COUNT; R64 SYSREF_INP_FMT SYSREF_DIV_PRE SYSREF_REPEAT_NS SYSREF_PULSE SYSREF_EN SYSREF_REPEAT");
      Serial.println("R65 SYSREF_DIV; R66 JESD_DAC2_CTRL JESD_DAC1_CTRL; R67 SYSREF_PULSE_CNT JESD_DAC4_CTRL JESD_DAC3_CTRL");
      Serial.println("R68 INPIN_IGNORE PSYNC_INP_FMT; R69 PSYNC_SROUT_PD; R70 DBLBUF_OUTMUX_EN DBLBUF_OUTBUF_EN DBLBUF_CHDIV_EN DBLBUF_PLL_EN");
      Serial.println("Raw-register slot 71 stores hardware R80 (OUTB_PWR) to retain the V2 settings layout.");
      Serial.println("R77 PINMUTE_POL; R78 OUTA_PD OUTA_MUX; R79 OUTB_PD OUTB_MUX OUTA_PWR; R80 OUTB_PWR");
      Serial.println();
    }

    equals = resp.indexOf("=");

    if (equals > -1)  // Trying to assigng value
    {
      param = resp.substring(0, equals);
      param.trim();
      value = resp.substring(equals + 1);
      value.trim();
    } else {
      param = resp;
      param.trim();
      value = "";
    }

    uint32_t before[80];
    memcpy(before, chanData[channel].reg, sizeof(before));
    // Check each possible Parameter name and process it.

    //Reg 0
    if (paramBool(param, "INSTCAL_SKIP_ACAL", &LMX2820_INSTCAL_SKIP_ACAL, value)) goto handled;
    if (paramByte(param, "FCAL_HPFD_ADJ", &LMX2820_FCAL_HPFD_ADJ, value, 0, 3)) goto handled;
    if (paramByte(param, "FCAL_LPFD_ADJ", &LMX2820_FCAL_LPFD_ADJ, value, 0, 3)) goto handled;
    if (paramBool(param, "DBLR_CAL_EN", &LMX2820_DBLR_CAL_EN, value)) goto handled;
    if (paramBool(param, "FCAL_EN", &LMX2820_FCAL_EN, value)) goto handled;
    if (paramBool(param, "RESET", &LMX2820_RESET, value)) goto handled;
    if (paramBool(param, "POWERDOWN", &LMX2820_POWERDOWN, value)) goto handled;
    //Reg 1
    if (paramBool(param, "PHASE_SYNC_EN", &LMX2820_PHASE_SYNC_EN, value)) goto handled;
    if (paramBool(param, "LD_VTUNE_EN", &LMX2820_LD_VTUNE_EN, value)) goto handled;
    if (paramBool(param, "INSTCAL_DBLR_EN", &LMX2820_INSTCAL_DBLR_EN, value)) goto handled;
    if (param == "INSTCAL_EN" && value.length() && value != "0") { Serial.println("Instant calibration initialization is not implemented."); continue; }
    if (paramBool(param, "INSTCAL_EN", &LMX2820_INSTCAL_EN, value)) goto handled;
    //Reg 2
    if (paramByte(param, "CAL_CLK_DIV", &LMX2820_CAL_CLK_DIV, value, 0, 3)) goto handled;
    if (paramUint(param, "INSTCAL_DLY", &LMX2820_INSTCAL_DLY, value, 0, 2047)) goto handled;
    if (paramBool(param, "QUICKRECAL_EN", &LMX2820_QUICKRECAL_EN, value)) goto handled;
    //Reg 6
    if (paramByte(param, "ACAL_CMP_DELAY", &LMX2820_ACAL_CMP_DLY, value, 0, 255)) goto handled;
    //Reg 10
    if (paramBool(param, "OUT_PFD_DLY_MANUAL", &LMX2820_PFD_DLY_MANUAL, value)) goto handled;
    if (paramBool(param, "VCO_DACISET_FORCE", &LMX2820_VCO_DACISET_FORCE, value)) goto handled;
    if (paramBool(param, "VCO_CAPCTRL_FORCE", &LMX2820_VCO_CAPCTRL_FORCE, value)) goto handled;
    //Reg 11
    if (paramBool(param, "OSC_2X", &LMX2820_OSC_2X, value)) goto handled;
    //Reg 12
    if (LMX2820ParamByteReserved(param, "MULT", &LMX2820_MULT, value, 1, 7, rsrvd2, 1)) goto handled;
    //Reg 13
    if (paramByte(param, "PLL_R", &LMX2820_PLL_R, value, 1, 255)) goto handled;
    //Reg 14
    if (paramUint(param, "PLL_R_PRE", &LMX2820_PLL_R_PRE, value, 1, 4095)) goto handled;
    //Reg 15
    if (paramBool(param, "PFD_POL", &LMX2820_PFD_POL, value)) goto handled;
    if (LMX2820ParamByteReserved(param, "PFD_SINGLE", &LMX2820_PFD_SINGLE, value, 0, 3, rsrvd12, 2)) goto handled;
    //Reg 16
    if (LMX2820ParamByteReserved(param, "CPG", &LMX2820_CPG, value, 1, 15, rsrvdCpg, 4)) goto handled;
    //Reg 17
    if (paramBool(param, "LD_TYPE", &LMX2820_LD_TYPE, value)) goto handled;
    //Reg 18
    if (LMX2820ParamUint32(param, "LD_DLY", &LMX2820_LD_DLY, value, 0, 0xFFFF)) goto handled;
    //Reg 19
    if (LMX2820ParamByteReserved(param, "TEMPSENSE_EN", &LMX2820_TEMPSENSE_EN, value, 0, 3, rsrvd12, 2)) goto handled;
    //Reg 20
    if (paramUint(param, "VCO_DACISET", &LMX2820_VCO_DACISET, value, 0, 511)) goto handled;
    //Reg 22
    if (paramByte(param, "VCO_SEL", &LMX2820_VCO_SEL, value, 1, 7)) goto handled;
    if (paramByte(param, "VCO_CAPCTRL", &LMX2820_VCO_CAPCTRL, value, 0, 191)) goto handled;
    //Reg 23
    if (paramBool(param, "VCO_SEL_FORCE", &LMX2820_VCO_SEL_FORCE, value)) goto handled;
    //Reg 32
    if (paramByte(param, "CHDIVB", &LMX2820_CHDIVB, value, 0, 6)) goto handled;
    if (paramByte(param, "CHDIVA", &LMX2820_CHDIVA, value, 0, 6)) goto handled;
    //Reg 34
    if (paramBool(param, "LOOPBACK_EN", &LMX2820_LOOPBACK_EN, value)) goto handled;
    if (paramBool(param, "EXTVCO_DIV", &LMX2820_EXTVCO_DIV, value)) goto handled;
    if (paramBool(param, "EXTVCO_EN", &LMX2820_EXTVCO_EN, value)) goto handled;

    //Reg 35
    if (paramBool(param, "MASHSEED_EN", &LMX2820_MASHSEED_EN, value)) goto handled;
    if (paramBool(param, "MASH_RESET_N", &LMX2820_MASH_RESET_N, value)) goto handled;
    if (paramByte(param, "MASH_ORDER", &LMX2820_MASH_ORDER, value, 0, 3)) goto handled;

    //Reg 36
    //combined 19 bit variable for convenience
    if (LMX2820ParamUint32(param, "PLL_N", &LMX2820_PLL_N, value, 0, 32767)) goto handled;
    //Reg 37
    if (paramByte(param, "PFD_DLY", &LMX2820_PFD_DLY, value, 1, 63)) goto handled;
    //Reg 38
    //Reg 39
    //combined 32 bit variable for convenience
    if (LMX2820ParamUint32(param, "PLL_DEN", &LMX2820_PLL_DEN, value, 1, 0xFFFFFFFF)) goto handled;
    //Reg 40
    //Reg 41
    //combined 32 bit variable for convenience
    if (LMX2820ParamUint32(param, "MASH_SEED", &LMX2820_MASH_SEED, value, 0, 0xFFFFFFFF)) goto handled;
    //Reg 42
    //Reg 43
    //combined 32 bit variable for convenience
    if (LMX2820ParamUint32(param, "PLL_NUM", &LMX2820_PLL_NUM, value, 0, 0xFFFFFFFF)) goto handled;
    //Reg 44
    //Reg 45
    //combined 32 bit variable for convenience
    if (LMX2820ParamUint32(param, "INSTCAL_PLL_NUM", &LMX2820_INSTCAL_PLL_NUM, value, 0, 0xFFFFFFFF)) goto handled;
    //Reg 62
    //Reg 63
    //combined 32 bit variable for convenience
    if (LMX2820ParamUint32(param, "MASH_RST_COUNT", &LMX2820_MASH_RST_COUNT, value, 0, 0xFFFFFFFF)) goto handled;
    //Reg 64
    if (paramByte(param, "SYSREF_INP_FMT", &LMX2820_SYSREF_INP_FMT, value, 0, 3)) goto handled;
    if (LMX2820ParamByteReserved(param, "SYSREF_DIV_PRE", &LMX2820_SYSREF_DIV_PRE, value, 1, 4, rsrvd3, 1)) goto handled;
    if (paramBool(param, "SYSREF_REPEAT_NS", &LMX2820_SYSREF_REPEAT_NS, value)) goto handled;
    if (paramBool(param, "SYSREF_PULSE", &LMX2820_SYSREF_PULSE, value)) goto handled;
    if (paramBool(param, "SYSREF_EN", &LMX2820_SYSREF_EN, value)) goto handled;
    if (paramBool(param, "SYSREF_REPEAT", &LMX2820_SYSREF_REPEAT, value)) goto handled;
    //Reg 65
    if (LMX2820ParamUint32(param, "SYSREF_DIV", &LMX2820_SYSREF_DIV, value, 0, 2047)) goto handled;
    //Reg 66
    if (paramByte(param, "JESD_DAC2_CTRL", &LMX2820_JESD_DAC2_CTRL, value, 0, 63)) goto handled;
    if (paramByte(param, "JESD_DAC1_CTRL", &LMX2820_JESD_DAC1_CTRL, value, 0, 63)) goto handled;
    //Reg 67
    if (paramByte(param, "SYSREF_PULSE_CNT", &LMX2820_SYSREF_PULSE_CNT, value, 0, 15)) goto handled;
    if (paramByte(param, "JESD_DAC4_CTRL", &LMX2820_JESD_DAC4_CTRL, value, 0, 63)) goto handled;
    if (paramByte(param, "JESD_DAC3_CTRL", &LMX2820_JESD_DAC3_CTRL, value, 0, 63)) goto handled;
    //Reg 68
    if (paramBool(param, "INPIN_IGNORE", &LMX2820_INPIN_IGNORE, value)) goto handled;
    if (paramBool(param, "PSYNC_INP_FMT", &LMX2820_PSYNC_INP_FMT, value)) goto handled;
    //Reg 69
    if (paramBool(param, "PSYNC_SROUT_PD", &LMX2820_SROUT_PD, value)) goto handled;
    //Reg70
    if (paramBool(param, "DBLBUF_OUTMUX_EN", &LMX2820_DBLBUF_OUTMUX_EN, value)) goto handled;
    if (paramBool(param, "DBLBUF_OUTBUF_EN", &LMX2820_DBLBUF_OUTBUF_EN, value)) goto handled;
    if (paramBool(param, "DBLBUF_CHDIV_EN", &LMX2820_DBLBUF_CHDIV_EN, value)) goto handled;
    if (paramBool(param, "DBLBUF_PLL_EN", &LMX2820_DBLBUF_PLL_EN, value)) goto handled;
    //Reg 77
    if (paramBool(param, "PINMUTE_POL", &LMX2820_PINMUTE_POL, value)) goto handled;
    //Reg 78
    if (paramBool(param, "OUTA_PD", &LMX2820_OUTA_PD, value)) goto handled;
    if (paramByte(param, "OUTA_MUX", &LMX2820_OUTA_MUX, value, 0, 2)) goto handled;
    //Reg 79
    if (paramByte(param, "OUTA_PWR", &LMX2820_OUTA_PWR, value, 0, 7)) goto handled;
    if (paramByte(param, "OUTB_MUX", &LMX2820_OUTB_MUX, value, 0, 2)) goto handled;
    if (paramBool(param, "OUTB_PD", &LMX2820_OUTB_PD, value)) goto handled;
    //Reg 80
    if (paramByte(param, "OUTB_PWR", &LMX2820_OUTB_PWR, value, 0, 7)) goto handled;

handled:
    if (value.length() > 0) {
      encodeRegs();
      if (memcmp(before, chanData[channel].reg, sizeof(before)) != 0) update();
    }
  }
}

void init(void) override {
  numberOfRegs = 80;  // R80 stored in unused channel slot 71; see OUTB_POWER_SLOT.
  numberOfBits = 24;  //number of bits in each register. Top 8 bits are register address low 16 bits are data.
  maxOsc = 1400;
  maxPfd = 300.0;
  minPfd = 5.0;
  minOsc = 5.0;
  jt4Only = false;
  jtDisable = false;
  pinMode(LMX2820MUTEPin, OUTPUT);
  digitalWrite(LMX2820MUTEPin, LOW); // Enable output
  pinMode(LMX2820CEPin, OUTPUT);
  digitalWrite(LMX2820CEPin, HIGH);
  pinMode(LMX2820CSBPin, OUTPUT);
  digitalWrite(LMX2820CSBPin, HIGH);
  SPI.setRX(LMX2820MUXPin);
  SPI.setTX(LMX2820SDIPin);
  SPI.setSCK(LMX2820SCKPin);
  SPI.begin();
}

void LMX2820Send(int32_t val) {
  int a = (val >> 16) & 0xFF;
  int b = (val >> 8) & 0xFF;
  int c = val & 0xFF;

  SPI.beginTransaction(SPISettings(400000, MSBFIRST, SPI_MODE0));
  digitalWrite(LMX2820CSBPin, LOW);
  delayMicroseconds(10);
  SPI.transfer((byte)a);
  SPI.transfer((byte)b);
  SPI.transfer((byte)c);
  delayMicroseconds(10);
  digitalWrite(LMX2820CSBPin, HIGH);
  SPI.endTransaction();
  delayMicroseconds(10);
}


void encodeRegs(void) override {
  byte regnum = 0;
  // first we initialise the address field of all the registers.
  for (int r = 0; r < numberOfRegs; r++) {
    chanData[channel].reg[r] = r << 16;
//    Serial.print("Encode_init ");
//    printHex(chanData[channel].reg[r],8);
//    Serial.println();
  }

  //next we map the parameters into the registers. Most registera also have additionla fixed bit patterns defined in the datasheet.
  chanData[channel].reg[0] = (chanData[channel].reg[0]) | (0b01 << 14) | (LMX2820_INSTCAL_SKIP_ACAL << 13) | (0b00 << 11) | (LMX2820_FCAL_HPFD_ADJ << 9) | (LMX2820_FCAL_LPFD_ADJ << 7) | (LMX2820_DBLR_CAL_EN << 6) | (1 << 5) | (LMX2820_FCAL_EN << 4) | (LMX2820_RESET << 1) | (LMX2820_POWERDOWN);
  chanData[channel].reg[1] = (chanData[channel].reg[1]) | (LMX2820_PHASE_SYNC_EN << 15) | (0b101011110 << 6) | (LMX2820_LD_VTUNE_EN << 5) | (LMX2820_INSTCAL_DBLR_EN << 1) | (LMX2820_INSTCAL_EN);
  chanData[channel].reg[2] = (chanData[channel].reg[2]) | (0b1 << 15) | ((LMX2820_CAL_CLK_DIV & 0x3U) << 12) | ((LMX2820_INSTCAL_DLY & 0x7FFU) << 1) | (LMX2820_QUICKRECAL_EN);
  chanData[channel].reg[3] = (chanData[channel].reg[3]) | (0b1000001);
  chanData[channel].reg[4] = (chanData[channel].reg[4]) | (0b0100001000000100);
  chanData[channel].reg[5] = (chanData[channel].reg[5]) | (0b0000000000110010);
  chanData[channel].reg[6] = (chanData[channel].reg[6]) | (LMX2820_ACAL_CMP_DLY << 8) | (0b01000011);
  chanData[channel].reg[7] = (chanData[channel].reg[7]);                         //0x0
  chanData[channel].reg[8] = (chanData[channel].reg[8]) | (0b1100100000000010);  // 0xC802
  chanData[channel].reg[9] = (chanData[channel].reg[9]) | (0b101);               //0x5
  chanData[channel].reg[10] = (chanData[channel].reg[10]) | (LMX2820_PFD_DLY_MANUAL << 12) | (LMX2820_VCO_DACISET_FORCE << 11) | (LMX2820_VCO_CAPCTRL_FORCE << 7);
  chanData[channel].reg[11] = (chanData[channel].reg[11]) | (0b110000 << 5) | (LMX2820_OSC_2X << 4) | (0b10); 
  chanData[channel].reg[12] = (chanData[channel].reg[12]) | ((LMX2820_MULT & 0x7U) << 10) | (0b1000);
  chanData[channel].reg[13] = (chanData[channel].reg[13]) | ((LMX2820_PLL_R & 0xFFU) << 5) | (0b11000);
  chanData[channel].reg[14] = (chanData[channel].reg[14]) | (0b11 << 12) | ((LMX2820_PLL_R_PRE & 0xFFFU));
  chanData[channel].reg[15] = (chanData[channel].reg[15]) | (0b10 << 12) | (LMX2820_PFD_POL << 11) | ((LMX2820_PFD_SINGLE & 0x3U) << 9) | (0b1);
  chanData[channel].reg[16] = (chanData[channel].reg[16]) | (0b10111000 << 5) | ((LMX2820_CPG & 0xFU) << 1);
  chanData[channel].reg[17] = (chanData[channel].reg[17]) | (0b00101011 << 7) | (LMX2820_LD_TYPE << 6);
  chanData[channel].reg[18] = (chanData[channel].reg[18]) | ((LMX2820_LD_DLY & 0xFFFFU));
  chanData[channel].reg[19] = (chanData[channel].reg[19]) | (0b100001001 << 5) | ((LMX2820_TEMPSENSE_EN & 0x3U) << 3);
  chanData[channel].reg[20] = (chanData[channel].reg[20]) | (0b0010011 << 9) | ((LMX2820_VCO_DACISET & 0x1FFU));
  chanData[channel].reg[21] = (chanData[channel].reg[21]) | (0b0001110001100100);
  chanData[channel].reg[22] = (chanData[channel].reg[22]) | ((LMX2820_VCO_SEL & 0x7U) << 13) | (0b10 << 8) | ((LMX2820_VCO_CAPCTRL & 0xFFU));
  chanData[channel].reg[23] = (chanData[channel].reg[23]) | (0b00100010000001 << 1) | (LMX2820_VCO_SEL_FORCE);
  chanData[channel].reg[24] = (chanData[channel].reg[24]) | (0b111000110100);
  chanData[channel].reg[25] = (chanData[channel].reg[25]) | (0b11000100100);
  chanData[channel].reg[26] = (chanData[channel].reg[26]) | (0b110110110000);
  chanData[channel].reg[27] = (chanData[channel].reg[27]) | (0b1000000000000001);
  chanData[channel].reg[28] = (chanData[channel].reg[28]) | (0b11000111001);
  chanData[channel].reg[29] = (chanData[channel].reg[29]) | (0b11000110001100);
  chanData[channel].reg[30] = (chanData[channel].reg[30]) | (0b1011000110001100);
  chanData[channel].reg[31] = (chanData[channel].reg[31]) | (0x401);
  chanData[channel].reg[32] = (chanData[channel].reg[32]) | (1 << 12) | ((LMX2820_CHDIVB & 0x7U) << 9) | ((LMX2820_CHDIVA & 0x7U) << 6) | (0b1);
  chanData[channel].reg[33] = (chanData[channel].reg[33]) | 0x0;
  chanData[channel].reg[34] = (chanData[channel].reg[34]) | (LMX2820_LOOPBACK_EN << 11) | (LMX2820_EXTVCO_DIV << 4) | (LMX2820_EXTVCO_EN);
  chanData[channel].reg[35] = (chanData[channel].reg[35]) | (0b1 << 13) | (LMX2820_MASH_RESET_N << 12) | ((LMX2820_MASH_ORDER & 0x3U) << 7) | (LMX2820_MASHSEED_EN << 6);
  chanData[channel].reg[36] = (chanData[channel].reg[36]) | ((LMX2820_PLL_N & 0x7FFFU));
  chanData[channel].reg[37] = (chanData[channel].reg[37]) | ((LMX2820_PFD_DLY & 0x3FU) << 9) | (0b100000000);
  LMX2820_PLL_DENH = (LMX2820_PLL_DEN >> 16) & 0xFFFF;
  LMX2820_PLL_DENL = LMX2820_PLL_DEN & 0xFFFF;
  chanData[channel].reg[38] = (chanData[channel].reg[38]) | (LMX2820_PLL_DENH);
  chanData[channel].reg[39] = (chanData[channel].reg[39]) | (LMX2820_PLL_DENL);
  //split 32 bit variable into two parts
  LMX2820_MASH_SEEDH = (LMX2820_MASH_SEED >> 16) & 0xFFFF;
  LMX2820_MASH_SEEDL = LMX2820_MASH_SEED & 0xFFFF;
  chanData[channel].reg[40] = (chanData[channel].reg[40]) | (LMX2820_MASH_SEEDH);
  chanData[channel].reg[41] = (chanData[channel].reg[41]) | (LMX2820_MASH_SEEDL);
  //split 32 bit variable into two parts
  LMX2820_PLL_NUMH = (LMX2820_PLL_NUM >> 16) & 0xFFFF;
  LMX2820_PLL_NUML = LMX2820_PLL_NUM & 0xFFFF;
  chanData[channel].reg[42] = (chanData[channel].reg[42]) | (LMX2820_PLL_NUMH);
  chanData[channel].reg[43] = (chanData[channel].reg[43]) | (LMX2820_PLL_NUML);
  LMX2820_INSTCAL_PLL_NUMH = (LMX2820_INSTCAL_PLL_NUM >> 16) & 0xFFFF;
  LMX2820_INSTCAL_PLL_NUML = LMX2820_INSTCAL_PLL_NUM & 0xFFFF;
  chanData[channel].reg[44] = (chanData[channel].reg[44]) | (LMX2820_INSTCAL_PLL_NUMH);
  chanData[channel].reg[45] = (chanData[channel].reg[45]) | (LMX2820_INSTCAL_PLL_NUML);
  chanData[channel].reg[46] = (chanData[channel].reg[46]) | (0b1100000000);
  chanData[channel].reg[47] = (chanData[channel].reg[47]) | (0b1100000000);
  chanData[channel].reg[48] = (chanData[channel].reg[48]) | (0b100000110000000);
  chanData[channel].reg[49] = (chanData[channel].reg[49]) | (0b0);
  chanData[channel].reg[50] = (chanData[channel].reg[50]) | (0b10000000);
  chanData[channel].reg[51] = (chanData[channel].reg[51]) | (0b10000000111111);
  chanData[channel].reg[52] = (chanData[channel].reg[52]) | (0b0);
  chanData[channel].reg[53] = (chanData[channel].reg[53]) | (0b0);
  chanData[channel].reg[54] = (chanData[channel].reg[54]) | (0b0);
  chanData[channel].reg[55] = (chanData[channel].reg[55]) | (0b10);
  chanData[channel].reg[56] = (chanData[channel].reg[56]) | (LMX2820_EXTPFD_DIV);
  chanData[channel].reg[57] = (chanData[channel].reg[57]) | (LMX2820_PFD_SEL);
  chanData[channel].reg[58] = (chanData[channel].reg[58]);
  chanData[channel].reg[59] = (chanData[channel].reg[59]) | (0b1001110001000);
  chanData[channel].reg[60] = (chanData[channel].reg[60]) | (0b111110100);
  chanData[channel].reg[61] = (chanData[channel].reg[61]) | (0b1111101000);
  LMX2820_MASH_RST_COUNTH = (LMX2820_MASH_RST_COUNT >> 16) & 0xFFFF;
  LMX2820_MASH_RST_COUNTL = LMX2820_MASH_RST_COUNT & 0xFFFF;
  chanData[channel].reg[62] = (chanData[channel].reg[62]) | (LMX2820_MASH_RST_COUNTH);
  chanData[channel].reg[63] = (chanData[channel].reg[63]) | (LMX2820_MASH_RST_COUNTL);
  chanData[channel].reg[64] = (chanData[channel].reg[64]) | (0b10 << 13) | ((LMX2820_SYSREF_INP_FMT & 0x3U) << 8) | ((LMX2820_SYSREF_DIV_PRE & 0x7U) << 5) | (LMX2820_SYSREF_REPEAT_NS << 4) | (LMX2820_SYSREF_PULSE << 3) | (LMX2820_SYSREF_EN << 2) | (LMX2820_SYSREF_REPEAT << 1);
  chanData[channel].reg[65] = (chanData[channel].reg[65]) | ((LMX2820_SYSREF_DIV & 0x7FFU));
  chanData[channel].reg[66] = (chanData[channel].reg[66]) | (LMX2820_JESD_DAC2_CTRL << 6) | (LMX2820_JESD_DAC1_CTRL);
  chanData[channel].reg[67] = (chanData[channel].reg[67]) | (LMX2820_SYSREF_PULSE_CNT << 12) | (LMX2820_JESD_DAC4_CTRL << 6) | (LMX2820_JESD_DAC3_CTRL);
  ;
  chanData[channel].reg[68] = (chanData[channel].reg[68]) | (LMX2820_INPIN_IGNORE << 5) | (LMX2820_PSYNC_INP_FMT);
  chanData[channel].reg[69] = (chanData[channel].reg[69]) | (LMX2820_SROUT_PD << 4) | 0b1;
  chanData[channel].reg[70] = (chanData[channel].reg[70]) | (LMX2820_DBLBUF_OUTMUX_EN << 7) | (LMX2820_DBLBUF_OUTBUF_EN << 6) | (LMX2820_DBLBUF_CHDIV_EN << 5) | (LMX2820_DBLBUF_PLL_EN << 4) | (0b1110);
  // 71 to 76 (inc) not used
  regnum = 77;
  chanData[channel].reg[77] = (chanData[channel].reg[77]) | (0b11 << 9) | (LMX2820_PINMUTE_POL << 8) | (0b1000);
  chanData[channel].reg[78] = (chanData[channel].reg[78]) | (LMX2820_OUTA_PD << 4) | ((LMX2820_OUTA_MUX & 0x3U));
  chanData[channel].reg[79] = (chanData[channel].reg[79]) | (LMX2820_OUTB_PD << 8) | ((LMX2820_OUTB_MUX & 0x3U) << 4) | ((LMX2820_OUTA_PWR & 0x7U) << 1);
  chanData[channel].reg[OUTB_POWER_SLOT] = (80U << 16) | ((LMX2820_OUTB_PWR & 0x7U) << 6);
  }

void decodeRegs(void) override {
  byte regnum = 0;
  //Reg 0
  LMX2820_INSTCAL_SKIP_ACAL = (chanData[channel].reg[regnum] >> 13) & 0x01;
  LMX2820_FCAL_HPFD_ADJ = (chanData[channel].reg[regnum] >> 9) & 0x03;
  LMX2820_FCAL_LPFD_ADJ = (chanData[channel].reg[regnum] >> 7) & 0x03;
  LMX2820_DBLR_CAL_EN = (chanData[channel].reg[regnum] >> 6) & 0x01;
  LMX2820_FCAL_EN = (chanData[channel].reg[regnum] >> 4) & 0x01;
  LMX2820_RESET = (chanData[channel].reg[regnum] >> 1) & 0x01;
  LMX2820_POWERDOWN = (chanData[channel].reg[regnum]) & 0x01;
  //
  regnum = 1;
  LMX2820_PHASE_SYNC_EN = (chanData[channel].reg[regnum] >> 15) & 0x01;
  LMX2820_LD_VTUNE_EN = (chanData[channel].reg[regnum] >> 5) & 0x01;
  LMX2820_INSTCAL_DBLR_EN = (chanData[channel].reg[regnum] >> 1) & 0x01;
  LMX2820_INSTCAL_EN = (chanData[channel].reg[regnum]) & 0x01;
  //
  regnum = 2;
  LMX2820_CAL_CLK_DIV = (chanData[channel].reg[regnum] >> 12) & 0x07;
  LMX2820_INSTCAL_DLY = (chanData[channel].reg[regnum] >> 1) & 0x07FF;
  LMX2820_QUICKRECAL_EN = (chanData[channel].reg[regnum]) & 0x01;
  //
  regnum = 6;
  LMX2820_ACAL_CMP_DLY = (chanData[channel].reg[regnum] >> 8) & 0xFF;
  //
  regnum = 10;
  LMX2820_PFD_DLY_MANUAL = (chanData[channel].reg[regnum] >> 12) & 0x01;
  LMX2820_VCO_DACISET_FORCE = (chanData[channel].reg[regnum] >> 11) & 0x01;
  LMX2820_VCO_CAPCTRL_FORCE = (chanData[channel].reg[regnum] >> 7) & 0x01;
  //
  regnum = 11;
  LMX2820_OSC_2X = (chanData[channel].reg[regnum] >> 4) & 0x01;
  //
  regnum = 12;
  LMX2820_MULT = (chanData[channel].reg[regnum] >> 10) & 0x07;
  //
  regnum = 13;
  LMX2820_PLL_R = (chanData[channel].reg[regnum] >> 5) & 0xff;
  //
  regnum = 14;
  LMX2820_PLL_R_PRE = (chanData[channel].reg[regnum]) & 0x0fff;
  //
  regnum = 15;
  LMX2820_PFD_POL = (chanData[channel].reg[regnum] >> 11) & 0x01;
  LMX2820_PFD_SINGLE = (chanData[channel].reg[regnum] >> 9) & 0x03;
  //
  regnum = 16;
  LMX2820_CPG = (chanData[channel].reg[regnum] >> 1) & 0x0f;
  //
  regnum = 17;
  LMX2820_LD_TYPE = (chanData[channel].reg[regnum] >> 6) & 0x01;
  //
  regnum = 18;
  LMX2820_LD_DLY = (chanData[channel].reg[regnum]) & 0xFFFF;
  //
  regnum = 19;
  LMX2820_TEMPSENSE_EN = (chanData[channel].reg[regnum] >> 3) & 0x03;
  //
  regnum = 20;
  LMX2820_VCO_DACISET = (chanData[channel].reg[regnum]) & 0x1FF;
  //
  regnum = 22;
  LMX2820_VCO_SEL = (chanData[channel].reg[regnum] >> 13) & 0x07;
  LMX2820_VCO_CAPCTRL = (chanData[channel].reg[regnum]) & 0xFF;
  //
  regnum = 23;
  LMX2820_VCO_SEL_FORCE = (chanData[channel].reg[regnum]) & 0x01;
  //
  regnum = 32;
  LMX2820_CHDIVB = (chanData[channel].reg[regnum] >> 9) & 0x07;
  LMX2820_CHDIVA = (chanData[channel].reg[regnum] >> 6) & 0x07;
  
  regnum = 34;
  LMX2820_LOOPBACK_EN = (chanData[channel].reg[regnum] >> 11) & 0x01;
  LMX2820_EXTVCO_DIV = (chanData[channel].reg[regnum] >> 4) & 0x01;
  LMX2820_EXTVCO_EN = (chanData[channel].reg[regnum]) & 0x01;
  //
  regnum = 35;
  LMX2820_MASH_RESET_N = (chanData[channel].reg[regnum] >> 12) & 0x01;
  LMX2820_MASH_ORDER = (chanData[channel].reg[regnum] >> 7) & 0x03;
  LMX2820_MASHSEED_EN = (chanData[channel].reg[regnum] >> 6) & 0x01;
  //
  regnum = 36;
  LMX2820_PLL_N = (chanData[channel].reg[regnum]) & 0x7FFF;
  //
  regnum = 37;
  LMX2820_PFD_DLY = (chanData[channel].reg[regnum] >> 9) & 0x3f;
  //
  regnum = 38;
  LMX2820_PLL_DENH = (chanData[channel].reg[regnum]) & 0xFFFF;      //High 16 bits
  LMX2820_PLL_DENL = (chanData[channel].reg[regnum + 1]) & 0xFFFF;  //Low 16 bits
  //combined 32 bit variable for convenience
  LMX2820_PLL_DEN = (LMX2820_PLL_DENH << 16) | LMX2820_PLL_DENL;
  //
  regnum = 40;
  LMX2820_MASH_SEEDH = (chanData[channel].reg[regnum]) & 0xFFFF;      //High 16 bits
  LMX2820_MASH_SEEDL = (chanData[channel].reg[regnum + 1]) & 0xFFFF;  //Low 16 bits
  //combined 32 bit variable for convenience
  LMX2820_MASH_SEED = (LMX2820_MASH_SEEDH << 16) | LMX2820_MASH_SEEDL;
  //
  regnum = 42;
  LMX2820_PLL_NUMH = (chanData[channel].reg[regnum]) & 0xFFFF;      //High 16 bits
  LMX2820_PLL_NUML = (chanData[channel].reg[regnum + 1]) & 0xFFFF;  //Low 16 bits
/***************** DEBUG PRINT
    Serial.print("42 (L796)");
  Serial.print((chanData[channel].reg[42]));
  Serial.print(" set-> ");
  Serial.println(LMX2820_PLL_NUMH );  
  Serial.print("43 (L800)");
  Serial.print((chanData[channel].reg[43]));
  Serial.print(" set-> ");
  Serial.println(LMX2820_PLL_NUML );
*********************************/
  //combined 32 bit variable for convenience
  LMX2820_PLL_NUM = (LMX2820_PLL_NUMH << 16) | LMX2820_PLL_NUML;
  //
  regnum = 44;
  LMX2820_INSTCAL_PLL_NUMH = (chanData[channel].reg[regnum]) & 0xFFFF;      //High 16 bits
  LMX2820_INSTCAL_PLL_NUML = (chanData[channel].reg[regnum + 1]) & 0xFFFF;  //Low 16 bits
  //combined 32 bit variable for convenience
  LMX2820_INSTCAL_PLL_NUM = (LMX2820_INSTCAL_PLL_NUMH << 16) | LMX2820_INSTCAL_PLL_NUML;
  //
  regnum = 56;
  LMX2820_EXTPFD_DIV = (chanData[channel].reg[regnum]) & 0x3F;
  //
  regnum = 57;
  LMX2820_PFD_SEL = (chanData[channel].reg[regnum]) & 0x01;
  //

  regnum = 62;
  LMX2820_MASH_RST_COUNTH = (chanData[channel].reg[regnum]) & 0xFFFF;      //High 16 bits
  LMX2820_MASH_RST_COUNTL = (chanData[channel].reg[regnum + 1]) & 0xFFFF;  //Low 16 bits
  //combined 32 bit variable for convenience
  LMX2820_MASH_RST_COUNT = (LMX2820_MASH_RST_COUNTH << 16) | LMX2820_MASH_RST_COUNTL;
  //
  regnum = 64;
  LMX2820_SYSREF_INP_FMT = (chanData[channel].reg[regnum] >> 8) & 0x03;
  LMX2820_SYSREF_DIV_PRE = (chanData[channel].reg[regnum] >> 5) & 0x07;
  LMX2820_SYSREF_REPEAT_NS = (chanData[channel].reg[regnum] >> 4) & 0x01;
  LMX2820_SYSREF_PULSE = (chanData[channel].reg[64] >> 3) & 0x01;
  LMX2820_SYSREF_EN = (chanData[channel].reg[64] >> 2) & 0x01;
  LMX2820_SYSREF_REPEAT = (chanData[channel].reg[regnum] >> 1) & 0x01;
  //
  regnum = 65;
  LMX2820_SYSREF_DIV = (chanData[channel].reg[regnum]) & 0x7FF;
  //
  regnum = 66;
  LMX2820_JESD_DAC2_CTRL = (chanData[channel].reg[regnum] >> 6) & 0x3F;
  LMX2820_JESD_DAC1_CTRL = (chanData[channel].reg[regnum]) & 0x3F;
  regnum = 67;
  LMX2820_SYSREF_PULSE_CNT = (chanData[channel].reg[regnum] >> 12) & 0x0F;
  LMX2820_JESD_DAC4_CTRL = (chanData[channel].reg[regnum] >> 6) & 0x3F;
  LMX2820_JESD_DAC3_CTRL = (chanData[channel].reg[regnum]) & 0x3F;
  //
  regnum = 68;
  LMX2820_INPIN_IGNORE = (chanData[channel].reg[regnum] >> 5) & 0x01;
  LMX2820_PSYNC_INP_FMT = (chanData[channel].reg[regnum]) & 0x01;
  //
  regnum = 69;
  LMX2820_SROUT_PD = (chanData[channel].reg[regnum] >> 4) & 0x01;
  //
  regnum = 70;
  LMX2820_DBLBUF_OUTMUX_EN = (chanData[channel].reg[regnum] >> 7) & 0x01;
  LMX2820_DBLBUF_OUTBUF_EN = (chanData[channel].reg[regnum] >> 6) & 0x01;
  LMX2820_DBLBUF_CHDIV_EN = (chanData[channel].reg[regnum] >> 5) & 0x01;
  LMX2820_DBLBUF_PLL_EN = (chanData[channel].reg[regnum] >> 4) & 0x01;
  //
  regnum = 77;
  LMX2820_PINMUTE_POL = (chanData[channel].reg[regnum] >> 8) & 0x01;
  //
  regnum = 78;
  LMX2820_OUTA_PD = (chanData[channel].reg[regnum] >> 4) & 0x01;
  LMX2820_OUTA_MUX = (chanData[channel].reg[regnum]) & 0x03;
  //
  regnum = 79;
  LMX2820_OUTB_PD = (chanData[channel].reg[regnum] >> 8) & 0x01;
  LMX2820_OUTB_MUX = (chanData[channel].reg[regnum] >> 4) & 0x03;
  LMX2820_OUTA_PWR = (chanData[channel].reg[regnum] >> 1) & 0x07;
  //
  regnum = OUTB_POWER_SLOT;
  LMX2820_OUTB_PWR = (chanData[channel].reg[regnum] >> 6) & 0x07;
}

void update(void) override {
  // Ordinary calibration only: instant calibration needs a separate initialization sequence.
  digitalWrite(LMX2820MUTEPin, LMX2820_PINMUTE_POL ? LOW : HIGH);
  LMX2820Send(0x4022); // Required fixed R0 bits plus RESET.
  LMX2820Send(0x4020);
  LMX2820Send(chanData[channel].reg[OUTB_POWER_SLOT]); // Hardware R80 first.
  for (int r = numberOfRegs - 1; r > 0; --r) {
    if (r >= 71 && r <= 76) continue; // Read-only status registers.
    LMX2820Send(r == 1 ? chanData[channel].reg[r] & ~1U : chanData[channel].reg[r]);
  }
  uint32_t r0 = chanData[channel].reg[0] & ~0x12U;
  LMX2820Send(r0);
  delay(10);
  LMX2820Send(r0 | 0x10U); // Trigger calibration after LDO stabilization.
  delay(10); // Conservative delay; lock must still be verified on real hardware.
  digitalWrite(LMX2820MUTEPin, LMX2820_PINMUTE_POL ? HIGH : LOW);
}

double calcPfd(double requested) override {
  if (!isfinite(requested) || requested < 5.0 || requested > 300.0 ||
      !isfinite(refOsc) || refOsc < 5.0 || refOsc > 1400.0) return getPfd();
  // Prefer bypass, then the reference doubler, then the noisier multiplier.
  for (int mode = 0; mode < 3; ++mode) {
    if (mode == 1 && refOsc > 250.0) continue;
    for (int pre = 1; pre <= 4095; ++pre) {
      double input = refOsc * (mode == 1 ? 2.0 : 1.0) / pre;
      for (int mult = (mode == 2 ? 3 : 1); mult <= (mode == 2 ? 7 : 1); ++mult) {
        double output = input * mult;
        if (mode == 2 && (input < 30.0 || input > 70.0 || output < 180.0 || output > 250.0)) continue;
        double ratio = output / requested;
        int r = (int)round(ratio);
        if (r < 1 || r > 255 || fabs(ratio-r) > 1e-8) continue;
        if ((r == 2 && output > 500.0) || (r > 2 && output > 250.0)) continue;
        LMX2820_PLL_R_PRE = pre;
        LMX2820_PLL_R = r;
        LMX2820_MULT = mult;
        LMX2820_OSC_2X = (mode == 1);
        double actual = getPfd();
        LMX2820SetCalibrationClock(actual);
        Serial.print("PFD changed to "); Serial.println(actual, 9);
        return actual;
      }
    }
  }
  Serial.println("No valid reference-path configuration for requested PFD.");
  return getPfd();
}

void LMX2820SetCalibrationClock(double pfd) {
  LMX2820_CAL_CLK_DIV = refOsc <= 200 ? 0 : refOsc <= 400 ? 1 : refOsc <= 800 ? 2 : 3;
  LMX2820_FCAL_HPFD_ADJ = pfd <= 100 ? 0 : pfd <= 150 ? 1 : pfd <= 200 ? 2 : 3;
  LMX2820_FCAL_LPFD_ADJ = pfd >= 10 ? 0 : pfd >= 5 ? 1 : pfd >= 2.5 ? 2 : 3;
}

double getPfd(void) override {
  if (!LMX2820_PLL_R || !LMX2820_PLL_R_PRE) return 0;
  double pfd = refOsc;
  Serial.print("a pfd ");
  Serial.println(pfd);
  double r = (double)LMX2820_PLL_R * LMX2820_PLL_R_PRE;
  Serial.print("r ");
  Serial.println(r);
  if (LMX2820_OSC_2X == 1) pfd = pfd * 2.0;
  pfd = (pfd * LMX2820_MULT) / r;
  Serial.print("b pfd ");
  Serial.println(pfd);
  return pfd;
}

void setFrequency(double direct) override {
  byte oldMux = LMX2820_OUTA_MUX, oldDiv = LMX2820_CHDIVA, oldCore = LMX2820_VCO_SEL;
  bool oldDblr = LMX2820_DBLR_CAL_EN, oldInstDblr = LMX2820_INSTCAL_DBLR_EN;
  bool freqOK = false;
  double pfd;
  double freq;
  double vcofreq;
  double n;
  double part;
  double err;
  uint32_t num;
  uint32_t den;
  int chd = 0;
  int divide[] = { 1, 2, 4, 8, 16, 32, 64, 128 };
  bool dub = 0;
  bool maxDivisor;
  bool n_is_int;
  char resp;
  int n_mash_mins[7][4] ={
  {12,18,19,24},
  {14,21,22,26},
  {16,23,24,26},
  {16,26,27,29},
  {18,28,29,31},
  {18,30,31,33},
  {20,33,34,36}
};

  if ((chanData[channel].fskMode & (CWIDBIT | EXTKEYBIT)) || (chanData[channel].jtMode))  //if we are using any FSK keying then we must keep the divisor to the same value to avoid glitches
  {
    maxDivisor = true;
  } else {
    maxDivisor = false;
  }

  pfd = getPfd();

  freqOK = false;
  if (direct == 0) {
    while (!freqOK) {
      if (chanData[channel].extMult > 1) {
        Serial.print("External Multiplier is ");
        Serial.println(chanData[channel].extMult);
        Serial.print("\nEnter Required Final Multiplied Frequency in MHz -->");
        freq = inputFloat() / (double)chanData[channel].extMult;
      } else {
        Serial.print("\nEnter Required Frequency in MHz -->");
        freq = inputFloat();
      }
      if (freq == 0){
        Serial.println("Aborted");
        return;
      }
      if ((freq >= 45.0) && (freq <= 22600.000)) {
        freqOK = true;
      } else {
        Serial.println("Synthesiser Frequency must be between 45 and 22600 MHz (subject to PCB)");
      }
    }
  } else {
    Serial.print("External Multiplier is ");
    Serial.println(chanData[channel].extMult);
    Serial.print(" direct freq reqd x");
    Serial.println(direct, 10);
    freq = direct;
  }

  if (!isfinite(freq) || freq < 45.0 || freq > 22600.0 || !isfinite(pfd) || pfd < 5 || pfd > 300) {
    Serial.println("Invalid frequency or PFD; settings unchanged."); return;
  }
  LMX2820SetCalibrationClock(pfd);
  if (freq > 11300.0)  //use the chip vco doubler between 11.3 and 22.6 GHz
  {
    freq = freq / 2.0;  //freq is now vco freq reqd
    dub = 1;
  }
  //Calculate the required output divider
  if ((freq >= 5650.000) && (freq < 11300.000)) chd = 0; // Direct - no divide
  if ((freq >= 2825.000) && (freq < 5650.000)) chd = 1; // Divide by 2 CHDIVA = 0
  if ((freq >= 1412.500) && (freq < 2825.000)) chd = 2; // Divide by 4 CHDIVA = 1
  if ((freq >= 706.250) && (freq < 1412.500)) chd = 3; // Divide by 8 CHDIVA = 2
  if ((freq >= 353.125) && (freq < 706.250)) chd = 4; // Divide by 16 CHDIVA = 3
  if ((freq >= 176.5625) && (freq < 353.125)) chd = 5;
  if ((freq >= 88.28125) && (freq < 176.5625)) chd = 6;
  if ((freq >= 45.0) && (freq < 88.28125)) chd = 7; //Divide by 128 CHDIVA = 7


  if (chd == 0) 
  {
    LMX2820_OUTA_MUX = 1; // VCO
    LMX2820_DBLR_CAL_EN = 0;
    LMX2820_INSTCAL_DBLR_EN = 0;

  } else   //Dvider
  {
    LMX2820_OUTA_MUX = 0;
    LMX2820_INSTCAL_DBLR_EN = 0;
    LMX2820_DBLR_CAL_EN = 0;
    LMX2820_CHDIVA = chd - 1;  //CHDIVA - B channel not used
  }
   if(dub == 1)
    {
      LMX2820_OUTA_MUX = 2;
      LMX2820_DBLR_CAL_EN = 1;
      LMX2820_INSTCAL_DBLR_EN = 1;
    }
Serial.print(" 1046 chd ");
Serial.println(chd);
Serial.print("DIVA ");
Serial.println(LMX2820_CHDIVA);

  //adjust the vco frequency to allow for the output division
vcofreq = freq * (double)divide[chd];
Serial.print("vco freq ");
Serial.println(vcofreq);
// Calcualte VCO core for assist
if ((vcofreq >= 5650) && (vcofreq < 6350)) LMX2820_VCO_SEL = 1;
if ((vcofreq >= 6350) && (vcofreq < 7300)) LMX2820_VCO_SEL = 2;
if ((vcofreq >= 7300) && (vcofreq < 8100)) LMX2820_VCO_SEL = 3;
if ((vcofreq >= 8100) && (vcofreq < 9000)) LMX2820_VCO_SEL = 4;
if ((vcofreq >= 9000) && (vcofreq < 9800)) LMX2820_VCO_SEL = 5;
if ((vcofreq >= 9800) && (vcofreq < 10600)) LMX2820_VCO_SEL = 6;
if ((vcofreq >= 10600) && (vcofreq < 11301)) LMX2820_VCO_SEL = 7;

  n = vcofreq / pfd;
Serial.print("n calc");
Serial.println(n);

  uint32_t integerN = (uint32_t)floor(n);
  double fraction = n - integerN;
  uint32_t denominator = 0xFFFFFFFFU;
  uint32_t numerator = (uint32_t)round(fraction * denominator);
  if (numerator == denominator) { ++integerN; numerator = 0; }
  if (!maxDivisor) {
    if (!numerator) denominator = 1;
    else {
      // Prefer a small exact fraction if its RF error is below 0.01 Hz.
      for (uint32_t d = 2; d <= 65535; ++d) {
        uint32_t v = (uint32_t)round(fraction*d);
        if (v < d && fabs((double)v/d - fraction)*pfd*1e6 < 0.01) {
          numerator=v; denominator=d; break;
        }
      }
    }
  }
  byte order = !numerator && !maxDivisor ? 0 : maxDivisor ? 1 :
               (denominator > 9 && denominator % 3 != 0 && pfd <= 225 ? 3 : 2);
  int core = LMX2820_VCO_SEL - 1;
  while (core >= 0 && core < 7 && order > 1 && integerN < (uint32_t)n_mash_mins[core][order]) --order;
  if (core < 0 || core >= 7 || integerN > 32767 || integerN < (uint32_t)n_mash_mins[core][order]) {
    LMX2820_OUTA_MUX=oldMux; LMX2820_CHDIVA=oldDiv; LMX2820_VCO_SEL=oldCore;
    LMX2820_DBLR_CAL_EN=oldDblr; LMX2820_INSTCAL_DBLR_EN=oldInstDblr;
    Serial.println("N divider below the allowed limit; reduce PFD. Settings unchanged."); return;
  }
  LMX2820_PLL_N=integerN; LMX2820_PLL_NUM=numerator; LMX2820_PLL_DEN=denominator;
  LMX2820_MASH_ORDER=order;
  // Instant calibration is not initialized by this driver.
  LMX2820_INSTCAL_EN=0;
  encodeRegs();
}

void calcFreq(void) override {
  if (!LMX2820_PLL_DEN || (LMX2820_OUTA_MUX == 0 && LMX2820_CHDIVA > 6)) { Serial.println("Invalid raw register settings."); return; }
  double pfd;
  double vco;
  double n;
  double nf;
  double fr;

  uint16_t diva;
  int divide[] = { 2, 4, 8, 16, 32, 64, 128 };

  if (LMX2820_OUTA_MUX == 0) {
    diva = divide[LMX2820_CHDIVA];
  } else {
    diva = 1;
  }


  Serial.print("DIVA ");
  Serial.println(LMX2820_CHDIVA);
  Serial.print("/");
  Serial.println(diva);

  n = (double)LMX2820_PLL_N;
  Serial.println();
  Serial.print("Reference Oscillator = ");
  Serial.print(refOsc, 10);
  Serial.println(" MHz");

  pfd = getPfd();

  Serial.print("PFD = ");
  Serial.print(pfd, 10);
  Serial.println(" MHz");

  fr = (double)LMX2820_PLL_NUM / (double)LMX2820_PLL_DEN;
  nf = (n + fr);

  vco = pfd * nf;
  Serial.print("N = ");
  Serial.print(nf, 10);
  Serial.print(" ( ");
  Serial.print(LMX2820_PLL_N);
  Serial.print(" + (");
  Serial.print(LMX2820_PLL_NUM);
  Serial.print("/");
  Serial.print(LMX2820_PLL_DEN);
  Serial.println(") )");
  Serial.print("MASH ORDER = ");
  Serial.println(LMX2820_MASH_ORDER);
  Serial.print("VCO = ");
  Serial.print(vco, 10);
  Serial.println(" MHz");

  Serial.print("O/P Divider = /");
  Serial.println(diva);

  Serial.print("O/P Doubler = ");
  if (LMX2820_OUTA_MUX == 2) {
    Serial.println("On");
    vco = vco * 2.0;
  } else {
    Serial.println("Off");
  }


  Serial.print("Output Frequency = ");
  Serial.print(vco / diva, 10);
  Serial.println(" MHz");

  if (chanData[channel].extMult > 1) {
    Serial.print("Final Multiplied Frequency = ");
    Serial.print((vco / diva) * (double)chanData[channel].extMult, 10);
    Serial.println(" MHz");
  }
  Serial.print("JT = ");
  Serial.println(chanData[channel].jtMode);
  Serial.print("CW = ");
  Serial.println(chanData[channel].fskMode);

}

double getFrequency(void) override {
  if (!LMX2820_PLL_DEN || (LMX2820_OUTA_MUX == 0 && LMX2820_CHDIVA > 6)) return 0;
  double pfd;
  double vco;
  double n;
  double nf;
  double fr;

  uint16_t diva;
  int divide[] = { 2, 4, 8, 16, 32, 64, 128 };

  if (LMX2820_OUTA_MUX == 0) {
    diva = divide[LMX2820_CHDIVA];
  } else {
    diva = 1;
  }

  n = (double)LMX2820_PLL_N;

  pfd = getPfd();

  fr = (double)LMX2820_PLL_NUM / (double)LMX2820_PLL_DEN;

  nf = (n + fr);

  vco = pfd * nf;

  if (LMX2820_OUTA_MUX == 2) {
    vco = vco * 2.0; // vco doubler
  }

  return vco / diva;
}

void jtShift(uint8_t val) override {
  if (val >= 66) return;
//  LMX2820Send((34 << 16) | ((jtN[val] >> 16) & 0xFFFF));
  LMX2820Send((36 << 16) | (jtN[val] & 0xFFFF));

  LMX2820Send((38 << 16) | ((jtDen[val] >> 16) & 0xFFFF));
  LMX2820Send((39 << 16) | (jtDen[val] & 0xFFFF));

  LMX2820Send((42 << 16) | ((jtNum[val] >> 16) & 0xFFFF));
  LMX2820Send((43 << 16) | (jtNum[val] & 0xFFFF));
  if (LMX2820_DBLBUF_PLL_EN) LMX2820Send(chanData[channel].reg[0] & ~0x12U);
}

void LMX2820Mute(bool muting) {
  digitalWrite(LMX2820MUTEPin, (muting != LMX2820_PINMUTE_POL) ? HIGH : LOW);
}

void fskKey(bool key) override {


  if (key) {

//    LMX2820Send(chanData[channel].reg[34]);
    LMX2820Send(chanData[channel].reg[36]);

    LMX2820Send(chanData[channel].reg[38]);
    LMX2820Send(chanData[channel].reg[39]);

    LMX2820Send(chanData[channel].reg[42]);
    LMX2820Send(chanData[channel].reg[43]);
    if (LMX2820_DBLBUF_PLL_EN) LMX2820Send(chanData[channel].reg[0] & ~0x12U);

  } else {

//    LMX2820Send((34 << 16) | ((cwidKeyUpN >> 16) & 0xFFFF));
    LMX2820Send((36 << 16) | (cwidKeyUpN & 0xFFFF));

    LMX2820Send((38 << 16) | ((cwidKeyUpDen >> 16) & 0xFFFF));
    LMX2820Send((39 << 16) | (cwidKeyUpDen & 0xFFFF));

    LMX2820Send((42 << 16) | ((cwidKeyUpNum >> 16) & 0xFFFF));
    LMX2820Send((43 << 16) | (cwidKeyUpNum & 0xFFFF));
  if (LMX2820_DBLBUF_PLL_EN) LMX2820Send(chanData[channel].reg[0] & ~0x12U);
  }
}

void extKey(bool key) override {
  if (key) {

//    LMX2820Send(chanData[channel].reg[34]);
    LMX2820Send(chanData[channel].reg[36]);

    LMX2820Send(chanData[channel].reg[38]);
    LMX2820Send(chanData[channel].reg[39]);

    LMX2820Send(chanData[channel].reg[42]);
    LMX2820Send(chanData[channel].reg[43]);
    if (LMX2820_DBLBUF_PLL_EN) LMX2820Send(chanData[channel].reg[0] & ~0x12U);

  } else {

  //  LMX2820Send((34 << 16) | ((ExtKeyUpN >> 16) & 0xFFFF));
    LMX2820Send((36 << 16) | (ExtKeyUpN & 0xFFFF));

    LMX2820Send((38 << 16) | ((ExtKeyUpDen >> 16) & 0xFFFF));
    LMX2820Send((39 << 16) | (ExtKeyUpDen & 0xFFFF));

    LMX2820Send((42 << 16) | ((ExtKeyUpNum >> 16) & 0xFFFF));
    LMX2820Send((43 << 16) | (ExtKeyUpNum & 0xFFFF));
  if (LMX2820_DBLBUF_PLL_EN) LMX2820Send(chanData[channel].reg[0] & ~0x12U);
  }
}

void saveFskShift(void) override {
  cwidKeyUpN = LMX2820_PLL_N;
  cwidKeyUpDen = LMX2820_PLL_DEN;
  cwidKeyUpNum = LMX2820_PLL_NUM;
}

void saveKeyShift(void) override {
  ExtKeyUpN = LMX2820_PLL_N;
  ExtKeyUpDen = LMX2820_PLL_DEN;
  ExtKeyUpNum = LMX2820_PLL_NUM;
}

void saveJt(uint8_t index) override {
  jtN[index] = LMX2820_PLL_N;
  jtDen[index] = LMX2820_PLL_DEN;
  jtNum[index] = LMX2820_PLL_NUM;
}

//--- RF output power/enable control, used by the touchscreen UI ---
uint8_t getPower(void) override { return LMX2820_OUTA_PWR; }
void setPower(uint8_t p) override
{
  if (p > 7) p = 7;
  LMX2820_OUTA_PWR = p;
  encodeRegs();
  update();
}
bool getOutput(void) override { return !LMX2820_OUTA_PD; }
void enableOutput(bool o) override
{
  LMX2820_OUTA_PD = !o;
  encodeRegs();
  update();
}

};

LMX2820Chip lmx2820Chip;             //the single instance of this chip driver
