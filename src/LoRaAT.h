/**
 *  Library created by: Cesar Augusto B. Barbosa e Thiago Piovesan
 *      Latin American Center for Open Technologies (CELTAB) 
 *          Itaipu Technological Park (PTI)
 * 
 *  Manual: https://cesar-a-benitez.github.io/LoRaAT/
 *  
 *  (en)
 *      This Library was designed to configure and use any LoRaWAN node
 *      that uses AT commands.
 * 
 *      Notes:
 *          - This Library was meant to configure LoRaWAN node to the AU915 Frequency Plan
 * 
 *  (pt-br)
 *      Esta Biblioteca foi desenvolvida para configurar e usar qualquer
 *      nó LoRaWAN que use comandos AT.
 * 
 *      Notas:
 *          - Esta Biblioteca foi idealizada para configurar nós no Plano de Frequência AU915 // na frequencia AU915
 */

#ifndef LoRaAT_h
#define LoRaAT_h
#define SerialDebug Serial

//#define DebugMode     // Uncomment to activate the Serial Debug
#define VerboseMode     // Uncomment to activate Verbose Mode
#define Watchdog        // Uncomment to activate Watchdog

#include <SoftwareSerial.h>
#include "Arduino.h"
#include "string.h"

class LoRaAT {
    public:
        LoRaAT(int rx, int tx);
        void init();
        void setDevAddr(String DevAddr);
        void setDevEui(String DevEui);
        void setAppEui(String AppEui);
	void setNwkSkey(String NwkSkey);
	void setAppSkey(String AppSkey);
        void setIDs(String DevAddr, String DevEui, String AppEui);
	void setKeys(String NwkSkey, String AppSkey);
        void config();
        void DRConfig();
        void CHConfig();
        void sendCmd(String cmd);
        void waitMsg();
        void sendMsg(String msg);
        void sendCMsg(String msg);
        void sendMsgHex(String msg);
        void sendCMsgHex(String msg);
        void setTimeDelay(int timeDelay);
        String waitAnsMsg();
        void loop();
        bool testConfig();
        bool compare(String cmd, String ans);
        bool waitACK();
        void watchdogRst();
    private:
        String _DevAddr;
        String _DevEui;
        String _AppEui;
	String _NwkSkey;
	String _AppSkey;
        int _rx, _tx;
        int _timeDelay;
        int configCount;
        int MaxConfigTry;
        SoftwareSerial *LoRaNode;
};

#endif
