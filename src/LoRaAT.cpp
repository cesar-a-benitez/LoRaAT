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
 *          - Esta Biblioteca foi idealizada para configurar nós no Plano de Frequência AU915
 */

#include "LoRaAT.h"

#ifdef Watchdog
    #include <ESP8266WiFi.h>
#endif


LoRaAT::LoRaAT(int rx, int tx) {
    // Set Rx and Tx ports
    _rx = rx;
    _tx = tx;

    _DevAddr = "";
    _DevEui = "";
    _AppEui = "";
    _NwkSkey = "";
    _AppSkey = "";
    MaxConfigTry = 4;
    configCount = 0;
}

void LoRaAT::init() {
    // Starts the Serial connections
    LoRaNode = new SoftwareSerial(_rx, _tx);
    LoRaNode->begin(9600);
    _timeDelay = 600;
}


/**
 *  Attention:
 *      The set functions of IDs or Keys do not set it right away to the node
 *      it only set it up to the Library, the node configuration part is done
 *      in the config or testConfig functions.
 */

void LoRaAT::setDevAddr(String DevAddr) {
    // Set DevAddr individually
    _DevAddr = DevAddr;
    _DevAddr.toUpperCase();

    #if LogLevel > 0
        std::cout << "\nDevAddr: " << _DevAddr;
    #endif
}

void LoRaAT::setDevEui(String DevEui) {
    // Set DevEui individually
    _DevEui = DevEui;
    _DevEui.toUpperCase();
    
    #if LogLevel > 0
        std::cout << "\nDevEui: " << _DevEui;
    #endif
}

void LoRaAT::setAppEui(String AppEui) {
    // setAppEui individually
    _AppEui = AppEui;   
    _AppEui.toUpperCase();

    #if LogLevel > 0
        std::cout << "\nAppEui: " << _AppEui;
    #endif
}

void LoRaAT::setNwkSkey(String NwkSkey) {
    // Set NwkSkey individually
    _NwkSkey = NwkSkey;
    _NwkSkey.toUpperCase();

    #if LogLevel > 0
        std::cout << "\nNwkSkey: " << _NwkSkey;
    #endif
}

void LoRaAT::setAppSkey(String AppSkey) {
    // Set AppSkey individually
    _AppSkey = AppSkey;
    _AppSkey.toUpperCase();

    #if LogLevel > 0
        std::cout << "\nAppSkey: " << _AppSkey;
    #endif
}

void LoRaAT::setKeys(String NwkSkey, String AppSkey) {
    // Set NwkSkey and AppSkey keys
    _NwkSkey = NwkSkey;
    _NwkSkey.toUpperCase();

    #if LogLevel > 0
        std::cout << "\nNwkSkey: " << _NwkSkey.c_str();
    #endif

    _AppSkey = AppSkey;
    _AppSkey.toUpperCase();

    #if LogLevel > 0
        std::cout << "\nAppSkey: " << _AppSkey.c_str() << "\n";
    #endif
}

void LoRaAT::setIDs(String DevAddr, String DevEui, String AppEui) {
    // Set DevAddr, DevEui and AppEui keys
    _DevAddr = DevAddr;
    _DevAddr.toUpperCase();

    #if LogLevel > 0
        std::cout << "\nDevAddr: " << _DevAddr.c_str();
    #endif

    _DevEui = DevEui;
    _DevEui.toUpperCase();

    #if LogLevel > 0
        std::cout << "\nDevEui: " << _DevEui.c_str();
    #endif

    _AppEui = AppEui;
    _AppEui.toUpperCase();

    #if LogLevel > 0
        std::cout << "\nAppEui: " << _AppEui.c_str() << "\n";
    #endif
}

void LoRaAT::setTimeDelay(int timeDelay) {
    // Set the delay in each interaction on waitMsg function
    // If not changed it will stay in its default value of 600ms
    if (timeDelay >= 400) {
        _timeDelay = timeDelay;
    }else {
        std::cout << "\nError: timeDelay < 400, using default configuration (600ms).";
    }    
}

void LoRaAT::watchdogRst() {
    #ifdef Watchdog
        ESP.wdtDisable();
    #endif
}

void LoRaAT::sendCmd(String cmd) {
    // Function responsable to send the command received to the node
    #if LogLevel > 1
        std::cout << cmd;
    #endif
    LoRaNode->flush();
    LoRaNode->print(cmd); 
    
    waitMsg();
}

void LoRaAT::sendATCmd(String cmd) {
    // Function responsable to send the command received to the node
    #if LogLevel > 1
        std::cout << cmd;
    #endif
    LoRaNode->flush();
    LoRaNode->print(cmd); 
}

void LoRaAT::waitMsg() {
    // Function responsable for waiting a response to the sented message
    delay(_timeDelay);
    String received = "";
    char rcv;

    while (LoRaNode->available()) {
        rcv = LoRaNode->read();
        received += rcv;
    }

    #if LogLevel > 1
        if (received != "") {
            std::cout << received.c_str() << "\n";
        }
    #endif
    
    received = "";

    delay(300);

    LoRaNode->flush();
} // end waitMsg

void LoRaAT::config() {
    // Configuration function
    #if LogLevel > 0
        std::cout << "\nConfig Started...\n\nConfiguring ID Keys...";
    #endif

    /**
     * Config ID Keys
     */
    
    watchdogRst();
    sendCmd("AT");
    if(_DevAddr != ""){
        sendCmd("AT+ID=DevAddr, " + _DevAddr);
    }
    
    watchdogRst();
    if(_DevEui != "") {
        sendCmd("AT+ID=DevEui, " + _DevEui);
    }

    watchdogRst();
    if(_AppEui != "") {
        sendCmd("AT+ID=AppEui, " + _AppEui);
    }

    watchdogRst();
    if(_NwkSkey != ""){
        sendCmd("AT+KEY=NWKSKEY, " + _NwkSkey);
    }

    watchdogRst();
    if(_AppSkey != ""){
        sendCmd("AT+KEY=APPSKEY, " + _AppSkey);
    }

    /**
     * Calling the functions responsables to configure DR (DataRate) and CH (Channels)
     */
    watchdogRst();
    DRConfig();
    watchdogRst();
    CHConfig();
    watchdogRst(); 

    #if LogLevel > 0
        std::cout << "\nConfig Finished....";
    #endif   
} // end config

void LoRaAT::DRConfig() {
    // Data Rate Configuration function
    #if LogLevel > 0
        std::cout << "\nConfiguring ports and DR...";
    #endif

    watchdogRst();
    // Set port = 1
    sendCmd("AT+PORT=1");

    // Turn ADR (Adaptive Data Rate) On
    watchdogRst();
    sendCmd("AT+ADR=ON");
    sendCmd("AT");

    // Set the AU915 DR Scheme
    watchdogRst();
    sendCmd("AT+DR=AU915");
    
    delay(200);
}

void LoRaAT::CHConfig() {
    // Set up the 8 channels of AU915 Frequency Plan
    #if LogLevel > 0
        std::cout << "\nSetting up channels....";
    #endif

    watchdogRst();
    sendCmd("AT");
    sendCmd("AT+CH=0, 916.8");
    delay(100);
    sendCmd("AT+CH=1, 917.2");
    delay(100);
    sendCmd("AT+CH=2, 917.4");
    delay(100);
    watchdogRst();
    sendCmd("AT+CH=3, 917.6");
    delay(100);
    sendCmd("AT+CH=4, 917.8");
    delay(100);
    sendCmd("AT+CH=5, 918");
    delay(100);
    sendCmd("AT+CH=6, 918.2");
    delay(100);
    sendCmd("AT+CH=7, 918.5");
    delay(100);
    watchdogRst();

    #if LogLevel > 0
        std::cout << "\n8 primary channels configured...\nCleaning unused channels...";
    #endif

    // Deleting the unused channels that the DR US915 has set up
    for(int cont=8; cont < 73; cont++) {
        sendCmd("AT+CH=" + String(cont) + ",0");
        delay(100);
        if(cont%4 == 0) {
            watchdogRst();
            if (cont != 8 && cont%8 == 0) {
                std::cout << "\n" << cont << " channels configured...";
            }
        }
    }
    #if LogLevel > 0
        std::cout << "\nChannels settup finished....\n";
    #endif
} // end CHConfig

void LoRaAT::sendMsg(String msg) {
    // Send Message Function
    msg = '"' + msg + '"';
    sendCmd("AT+MSG=" + msg);
}

void LoRaAT::sendCMsg(String msg) {
    // Send Confirmed Message Function
    msg = '"' + msg + '"';
    sendCmd("AT+CMSG=" + msg);
}

void LoRaAT::sendMsgHex(String msg) {
    // Send HEX Message Function
    msg = '"' + msg + '"';
    sendCmd("AT+MSGHEX=" + msg);
}

void LoRaAT::sendCMsgHex(String msg) {
    // Send Confirmed HEX Message Function
    msg = '"' + msg + '"';
    sendCmd("AT+CMSGHEX=" + msg);
}

String LoRaAT::waitAnsMsg() {
    // Function responsable to wait for the node answer and return it
    LoRaNode->flush();
    
    watchdogRst();
    delay(_timeDelay*2);

    String response = "";
    char rcv;

    while (LoRaNode->available()) {   
        while (LoRaNode->available()) {
            rcv = LoRaNode->read();
            response += rcv;
        }

        delay(_timeDelay);
    }

    #if LogLevel > 1
            std::cout << response.c_str();
    #endif

    return response;
}

bool LoRaAT::waitACK() {
    // Function that returns true if an ACK has been received or false if not received
    LoRaNode->flush();

    delay(_timeDelay*2);

    String response = "", done = "+CMSG: Done", ans = "+CMSG: ACK Received";
    char temp;
    int x = 0, y = 0;

    while (true) {
        watchdogRst();
        while (LoRaNode->available()) {
            temp = LoRaNode->read();
            response += temp;
        }

        for (int i = 0; i < response.length(); i++) {
            if(response.charAt(i) == ans.charAt(x)){
                if (x == ans.length()-1) {
                    #if LogLevel > 1
                        std::cout << response.c_str();
                    #endif

                    return true;
                }else {
                    x++;
                }
            }

            watchdogRst();
            if(response.charAt(i) == done.charAt(y)) {
                if (y == done.length()-1) {
                    #if LogLevel > 1
                        std::cout << response.c_str();
                    #endif

                    return false;
                }else {
                    y++;
                }
            }
        }

        delay(500);
    }
} // end waitACK

bool LoRaAT::compare(String cmd, String ans) {
    // Function responsable to do the comparison between the actual configuration
    // and the desired one
    #if LogLevel > 1
        std::cout << cmd;
    #endif
    LoRaNode->flush();
    LoRaNode->print(cmd); 

    delay(_timeDelay*2);
    
    String response = "";
    char temp;

    while (LoRaNode->available()) {
        temp = LoRaNode->read();
        response += temp;
    }

    int x = 0;

    #if LogLevel > 1
        std::cout << "\n----------------------------------------\nDebug: \nReceived: " << response.c_str() << "\nTo Compare: " << ans.c_str();
    #endif

    for (int i = 0; i < response.length(); i++) {
        if(response.charAt(i) == ans.charAt(x)){
            if (x == ans.length()-1) {
                LoRaNode->flush();
                #if LogLevel > 1
                    std::cout << "\n\nResult: ";
                #endif
                return true;
            }else {
                x++;
            }
        }
    }

    LoRaNode->flush();
    waitMsg();
    return false;
} // end compare

bool LoRaAT::testConfig() {
    // Function responsable to test if the node is configured
    // If is not configured the Function will configure it
    int ok = 0, ntest = 0, fail = 0;

    #if LogLevel > 0
        std::cout << "\n----------------------------------------\n        Starting Config Test:\n\n";
    #endif

    watchdogRst();
    if(_DevAddr != "") {
        #if LogLevel > 0
            std::cout << "DevAddr: ";
        #endif

        if (compare("at+id=devaddr", "+ID: DevAddr, " + _DevAddr)) {
            #if LogLevel > 0
                std::cout << "pass";
            #endif

            ok++;
            ntest++;
        }else {
            #if LogLevel > 0
                std::cout << "fail\nReconfiguring DevAddr....";
            #endif

            sendCmd("at+id=devaddr, " + _DevAddr);
            ntest++;
        }
    }

    watchdogRst();
    if(_DevEui != "") {
        #if LogLevel > 0
            std::cout << "\nDevEui: ";
        #endif

        if (compare("at+id=deveui", "+ID: DevEui, " + _DevEui)) {
            #if LogLevel > 0
                std::cout << "pass";
            #endif

            ok++;
            ntest++;
        }else {
            #if LogLevel > 0
                std::cout << "fail\nReconfiguring DevEui....";
            #endif

            sendCmd("at+id=deveui, " + _DevEui);
            ntest++;
        }
        #if LogLevel > 1
            std::cout << "\n----------------------------------------\n";
        #endif
    }

    watchdogRst();
    if(_AppEui != "") {
        #if LogLevel > 0
            std::cout << "\nAppEui: ";
        #endif

        if (compare("at+id=appeui", "+ID: AppEui, " + _AppEui)) {
            #if LogLevel > 0
                std::cout << "pass";
            #endif

            ok++;
            ntest++;
        }else {
            #if LogLevel > 0
                std::cout << "fail\nReconfiguring AppEui....";
            #endif

            sendCmd("at+id=appeui, " + _AppEui);
            ntest++;
        }
        #if LogLevel > 1
            std::cout << "\n----------------------------------------\n";
        #endif
    }

    watchdogRst();
    if(_NwkSkey != ""){
        #if LogLevel > 0
            std::cout << "\nNwkSKey: pass";
        #endif

        sendCmd("AT+KEY=NWKSKEY, " + _NwkSkey);
        ok++;
        ntest++;
        delay(100);
    }

    watchdogRst();
    if(_AppSkey != ""){
        #if LogLevel > 0
            std::cout << "\nAppSKey: pass";
        #endif
        
        sendCmd("AT+KEY=APPSKEY, " + _AppSkey);
        ok++;
        ntest++;
        delay(100);
    }

    watchdogRst();
    #if LogLevel > 0
        std::cout << "\nDR: ";
    #endif
    if (compare("at+dr", "+DR: DR0\n+DR: AU915 DR0  SF12 BW125K")){
        #if LogLevel > 0
            std::cout << "pass";
        #endif

        ok++;
        ntest++;
    }else {
        #if LogLevel > 0
            std::cout << "fail\nReconfiguring DR....";
        #endif
        
        DRConfig();
        ntest++;
    }

    #if LogLevel > 1
        std::cout << "\n----------------------------------------\n";
    #endif

    watchdogRst();
    delay(300);
    #if LogLevel > 0
        std::cout << "\nCH: ";
    #endif
    if (compare("at+ch", "+CH: 8; 0,916800000")) {
        #if LogLevel > 0
            std::cout << "pass";
        #endif

        ok++;
        ntest++;
    }else {
        #if LogLevel > 0
            std::cout << "fail\nReconfiguring CH....";
        #endif

        CHConfig();
        ntest++;
    }

    fail = ntest - ok;
    #if LogLevel > 0
        std::cout << "\n----------------------------------------\n | Tests: " << ntest << " | Passed: " << ok << " | Failed: " << fail << " |\n----------------------------------------\n";
    #endif

    watchdogRst();
    if(fail > 0){
        #if LogLevel > 0
            std::cout << "Errors found, restarting Config Test....\n----------------------------------------\n\n";
        #endif

        if (configCount < MaxConfigTry) {
            configCount++;
        }else {
            #if LogLevel > 0
                std::cout << "ERROR: Problems found during config test, please check the node and the communication.";
            #endif
            return false;
        }
        testConfig();
    }else {
        return true;
    }
} // end testConfig