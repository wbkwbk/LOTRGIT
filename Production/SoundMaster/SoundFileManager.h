#ifndef SOUNDFILEMANAGER_H
#define SOUNDFILEMANAGER_H

#include <Arduino.h>

class SoundFileManager {
  private:
    static const int BALROGHIT_COUNT = 7;
    static const int BALROGOPENRAMPS_COUNT = 7;
    static const int BALROGCLOSEDRAMPS_COUNT = 34;
    static const int BALROGOPENLEFTORBIT_COUNT = 1;
    static const int BALROGCLOSEDLEFTORBIT_COUNT = 28;
    static const int BALROGCLOSED_COUNT = 1;

    // Arrays für Sounddateien
    const char* balrogHitSounds[BALROGHIT_COUNT] = {
      "ROAR1.mp3",	"GROWL.mp3",	"ROAR2.mp3",	"ROAR3.mp3",	"ROAR5.mp3", "ROAR7.mp3", "ROAR8.mp3"
    };
    const char* balrogOpenRampsSounds[BALROGOPENRAMPS_COUNT] = {
      "OTBF.mp3",	"YSNPWE.mp3","ABDOTO.mp3",	"TDFWNU.mp3",	"NLVOD.mp3",	"YCP.mp3", "DASIS.mp3"
    };
    const char* balrogClosedRampsSounds[BALROGCLOSEDRAMPS_COUNT] = {
      "AWINL.mp3",	"CWMML.mp3",	"FOAT.mp3",	"MIIJY.mp3",	"PFB.mp3",	"TINBOT.mp3",	"NTRHBHH.mp3",	"SHR.mp3",	"SHAF.mp3",	"TRIATE.mp3",	"WHITF.mp3",	"TRWBS.mp3",	"IBWFGR.mp3",	"IYATOR.mp3",	"WRMRF.mp3",	"BFTRF.mp3", "LYHP.mp3",	"IDNFT.mp3",	"AWS.mp3",	"IMWGMH.mp3",	"SOLFT.mp3",	"TWC.mp3",	"WGGPSH.mp3",	"AWDFE.mp3", "DCB.mp3",	"DASIS.mp3",	"FTESH.mp3",	"FWTRS.mp3",	"ITLMFC.mp3",	"IBFGR.mp3",	"MGLAB.mp3",	"OTFW.mp3",	"OBODTH.mp3",	"OBTFLME.mp3"
    };
    const char* balrogOpenLeftOrbitSounds[BALROGOPENLEFTORBIT_COUNT] = {
      "HOS.mp3"
    };
    const char* balrogClosedLeftOrbitSounds[BALROGCLOSEDLEFTORBIT_COUNT] = {
      "IWRHNC.mp3",	"SWTB.mp3",	"GNLY.mp3",	"GSLH.mp3",	"GSFH.mp3",	"MPR.mp3",	"MPRES2.mp3",	"ICAML.mp3",	"ORTRTA.mp3",	"WMYMRF.mp3",	"TSDNHS.mp3",	"IAHY.mp3",	"WFOWSE.mp3", "COFTF.mp3",	"EVENS.mp3",	"ROATH.mp3",	"HSFOA.mp3",	"NCIE.mp3", "Q4DJ.mp3",	"RGOSWD.mp3",	"SEFPME.mp3",	"SHAF.mp3",	"TPIAYC.mp3",	"TRBGULL.mp3",	"TRCGCH.mp3",	"TRPIDEF.mp3",	"TWGEIW.mp3",	"WMFLDM.mp3"
    };
    const char* balrogClosedSounds[BALROGCLOSED_COUNT] = {
      "GBTTS.mp3"
    };

    // Indizes zur Verfolgung der verwendeten Sounds
    bool balrogHitUsed[BALROGHIT_COUNT] = { false, false, false, false, false, false, false };
    bool balrogOpenRampsUsed[BALROGOPENRAMPS_COUNT] = { false, false, false, false, false, false, false};
    bool balrogClosedRampsUsed[BALROGCLOSEDRAMPS_COUNT] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
    bool balrogOpenLeftOrbitUsed[BALROGOPENLEFTORBIT_COUNT] = { false};
    bool balrogClosedLeftOrbitUsed[BALROGCLOSEDLEFTORBIT_COUNT] = { false, false, false, false, false , false , false , false , false , false , false , false , false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false  };
    bool balrogClosedUsed[BALROGCLOSED_COUNT] = { false};

  public:
    // Constructor
    SoundFileManager();

    // Methoden zum Abrufen eines zufälligen Effekts
    const char* getBalrogHitEffect();
    const char* getBalrogOpenRampsEffect();
    const char* getBalrogClosedRampsEffect();
    const char* getBalrogOpenLeftOrbitEffect();
    const char* getBalrogClosedLeftOrbitEffect();
    const char* getBalrogClosedEffect();
    
    // Helferfunktion zum zufälligen Auswählen eines Effekts
    const char* getRandomSound(const char* soundList[], bool usedList[], int listSize);
    
    // Helferfunktion zum Zurücksetzen der verwendeten Liste
    void resetUsedList(bool usedList[], int listSize);
};

#endif
