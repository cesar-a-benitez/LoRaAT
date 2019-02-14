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

//#define DebugMode // Uncomment to activate the Serial Debug
#define VerboseMode // Uncomment to activate Verbose Mode
#include "LoRaAT.h"


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
    SerialDebug.begin(9600);
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

    #ifdef VerboseMode
        SerialDebug.println("DevAddr: " + _DevAddr);
    #endif
}

void LoRaAT::setDevEui(String DevEui) {
    // Set DevEui individually
    _DevEui = DevEui;
    _DevEui.toUpperCase();
    
    #ifdef VerboseMode
        SerialDebug.println("DevEui: " + _DevEui);
    #endif
}

void LoRaAT::setAppEui(String AppEui) {
    // setAppEui individually
    _AppEui = AppEui;   
    _AppEui.toUpperCase();

    #ifdef VerboseMode
        SerialDebug.println("AppEui: " + _AppEui);
    #endif
}

void LoRaAT::setNwkSkey(String NwkSkey) {
    // Set NwkSkey individually
    _NwkSkey = NwkSkey;
    _NwkSkey.toUpperCase();

    #ifdef VerboseMode
        SerialDebug.println("NwkSkey: " + _NwkSkey);
    #endif
}

void LoRaAT::setAppSkey(String AppSkey) {
    // Set AppSkey individually
    _AppSkey = AppSkey;
    _AppSkey.toUpperCase();

    #ifdef VerboseMode
        SerialDebug.println("AppSkey: " + _AppSkey);
    #endif
}

void LoRaAT::setKeys(String NwkSkey, String AppSkey) {
    // Set NwkSkey and AppSkey keys
    _NwkSkey = NwkSkey;
    _NwkSkey.toUpperCase();

    #ifdef VerboseMode
        SerialDebug.println("NwkSkey: " + _NwkSkey);
    #endif

    _AppSkey = AppSkey;
    _AppSkey.toUpperCase();

    #ifdef VerboseMode
        SerialDebug.println("AppSkey: " + _AppSkey);
    #endif
}

void LoRaAT::setIDs(String DevAddr, String DevEui, String AppEui) {
    // Set DevAddr, DevEui and AppEui keys
    _DevAddr = DevAddr;
    _DevAddr.toUpperCase();

    #ifdef VerboseMode
        SerialDebug.println("DevAddr: " + _DevAddr);
    #endif

    _DevEui = DevEui;
    _DevEui.toUpperCase();

    #ifdef VerboseMode
        SerialDebug.println("DevEui: " + _DevEui);
    #endif

    _AppEui = AppEui;
    _AppEui.toUpperCase();

    #ifdef VerboseMode
        SerialDebug.println("AppEui: " + _AppEui);
    #endif
}

void LoRaAT::setTimeDelay(int timeDelay) {
    // Set the delay in each interaction on waitMsg function
    // If not changed it will stay in its default value of 600ms
    if (timeDelay >= 400) {
        _timeDelay = timeDelay;
    }else {
        SerialDebug.println("\nError: timeDelay < 400, using default configuration (600ms).");
    }    
}

void LoRaAT::sendCmd(String cmd) {
    // Function responsable to send the command received to the node
    #ifdef DebugMode
        SerialDebug.println(cmd);
    #endif
    LoRaNode->flush();
    LoRaNode->print(cmd); 
    
    waitMsg();
}

void LoRaAT::waitMsg() {
    // Function responsable for waiting a response to the sented message
    delay(_timeDelay);

    
    while (LoRaNode->available()) {
        #ifdef DebugMode
            SerialDebug.write(LoRaNode->read());
        #endif
    }

    #ifdef DebugMode
        SerialDebug.println("");
    #endif

    delay(300);

    LoRaNode->flush();
} // end waitMsg

void LoRaAT::config() {
    // Configuration function
    #ifdef VerboseMode
        SerialDebug.println("\nConfig Started...\n\nConfiguring ID Keys...");
    #endif

    /**
     * Config ID Keys
     */
    
    sendCmd("AT");
    if(_DevAddr != ""){
        sendCmd("AT+ID=DevAddr, " + _DevAddr);
    }
    
    if(_DevEui != "") {
        sendCmd("AT+ID=DevEui, " + _DevEui);
    }

    if(_AppEui != "") {
        sendCmd("AT+ID=AppEui, " + _AppEui);
    }

    if(_NwkSkey != ""){
        sendCmd("AT+KEY=NWKSKEY, " + _NwkSkey);
    }

    if(_AppSkey != ""){
        sendCmd("AT+KEY=APPSKEY, " + _AppSkey);
    }

    /**
     * Calling the functions responsables to configure DR (DataRate) and CH (Channels)
     */
    DRConfig();
    CHConfig();

    
} // end config

void LoRaAT::DRConfig() {
    // Data Rate Configuration function
    #ifdef VerboseMode
        SerialDebug.print("\nConfiguring ports and channels...");
    #endif

    // Set port = 1
    sendCmd("AT+PORT=1");

    // Turn ADR (Adaptive Data Rate) On
    sendCmd("AT+ADR=ON");
    sendCmd("AT");

    // Set the AU915 DR Scheme
    sendCmd("AT+DR=AU915");
    
    delay(200);
}

void LoRaAT::CHConfig() {
    // Set up the 8 channels of AU915 Frequency Plan
    #ifdef VerboseMode
        SerialDebug.print("\nSetting up channels....");
    #endif

    sendCmd("AT");
    sendCmd("AT+CH=0, 916.8");
    delay(100);
    sendCmd("AT+CH=1, 917.2");
    delay(100);
    sendCmd("AT+CH=2, 917.4");
    delay(100);
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

    // Deleting the unused channels that the DR US915 has set up
    for(int cont=8; cont < 73; cont++) {
        sendCmd("AT+CH=" + String(cont) + ",0");
        delay(100);
    }
    #ifdef VerboseMode
        SerialDebug.println("Channels settup finished....");
        
        SerialDebug.println("\nConfig Finished...\n");
    #endif
} // end CHConfig

void LoRaAT::loop() {
    // Function to send and receive messages via Serial Console
    while(SerialDebug.available())
    { 
        LoRaNode->write(Serial.read());
    }
    while(LoRaNode->available())
    {
        SerialDebug.write(LoRaNode->read());
    }
} // end loop

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

    delay(_timeDelay*2);

    String response = "";
    char temp;

    while (LoRaNode->available()) {
        loraread:
        #ifdef DebugMode
            SerialDebug.write(LoRaNode->read());
        #endif
        temp = LoRaNode->read();
        response += temp;
    }

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
        while (LoRaNode->available()) {
            temp = LoRaNode->read();
            response += temp;
        }

        for (int i = 0; i < response.length(); i++) {
            if(response.charAt(i) == ans.charAt(x)){
                if (x == ans.length()-1) {
                    #ifdef DebugMode
                        SerialDebug.println(response);
                    #endif

                    return true;
                }else {
                    x++;
                }
            }

            if(response.charAt(i) == done.charAt(y)) {
                if (y == done.length()-1) {
                    #ifdef DebugMode
                        SerialDebug.println(response);
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
    #ifdef DebugMode
        SerialDebug.println(cmd);
    #endif
    LoRaNode->flush();
    LoRaNode->print(cmd); 

    delay(900);
    
    String response = "";
    char temp;

    while (LoRaNode->available()) {
        temp = LoRaNode->read();
        response += temp;
    }

    int x = 0;

    #ifdef DebugMode
        SerialDebug.println("\n----------------------------------------\n");
        SerialDebug.println("Debug: \nReceived: " + response + "\nTo Compare: " + ans);
    #endif

    for (int i = 0; i < response.length(); i++) {
        if(response.charAt(i) == ans.charAt(x)){
            if (x == ans.length()-1) {
                LoRaNode->flush();
                return true;
            }else {
                x++;
            }
        }
    }

    #ifdef DebugMode
        SerialDebug.println("\n\nx: " + String(x) + "  -  ans: " + ans.length() + "\n----------------------------------------\n");
    #endif

    LoRaNode->flush();
    waitMsg();
    return false;
} // end compare

bool LoRaAT::testConfig() {
    // Function responsable to test if the node is configured
    // If is not configured the Function will configure it
    int ok = 0, ntest = 0, fail = 0;

    #ifdef VerboseMode
        SerialDebug.println("\n----------------------------------------\n        Starting Config Test:\n");
    #endif

    if(_DevAddr != "") {
        #ifdef VerboseMode
            SerialDebug.print("DevAddr: ");
        #endif

        if (compare("at+id=devaddr", "+ID: DevAddr, " + _DevAddr)) {
            #ifdef VerboseMode
                SerialDebug.print("pass");
            #endif

            ok++;
            ntest++;
        }else {
            #ifdef VerboseMode
                SerialDebug.print("fail\nReconfiguring DevAddr....");
            #endif

            sendCmd("at+id=devaddr, " + _DevAddr);
            ntest++;
        }
    }

    if(_DevEui != "") {
        #ifdef VerboseMode
            SerialDebug.print("\nDevEui: ");
        #endif

        if (compare("at+id=deveui", "+ID: DevEui, " + _DevEui)) {
            #ifdef VerboseMode
                SerialDebug.print("pass");
            #endif

            ok++;
            ntest++;
        }else {
            #ifdef VerboseMode
                SerialDebug.print("fail\nReconfiguring DevEui....");
            #endif

            sendCmd("at+id=deveui, " + _DevEui);
            ntest++;
        }
    }

    if(_AppEui != "") {
        #ifdef VerboseMode
            SerialDebug.print("\nAppEui: ");
        #endif

        if (compare("at+id=appeui", "+ID: AppEui, " + _AppEui)) {
            #ifdef VerboseMode
                SerialDebug.print("pass");
            #endif

            ok++;
            ntest++;
        }else {
            #ifdef VerboseMode
                SerialDebug.print("fail\nReconfiguring AppEui....");
            #endif

            sendCmd("at+id=appeui, " + _AppEui);
            ntest++;
        }
    }

    if(_NwkSkey != ""){
        #ifdef VerboseMode
            SerialDebug.print("\nNwkSKey: pass");
        #endif

        sendCmd("AT+KEY=NWKSKEY, " + _NwkSkey);
        ok++;
        ntest++;
        delay(100);
    }

    if(_AppSkey != ""){
        #ifdef VerboseMode
            SerialDebug.print("\nAppSKey: pass");
        #endif

        sendCmd("AT+KEY=APPSKEY, " + _AppSkey);
        ok++;
        ntest++;
        delay(100);
    }

    #ifdef VerboseMode
        SerialDebug.print("\nDR: ");
    #endif
    if (compare("at+dr", "+DR: DR0\n+DR: AU915 DR0  SF12 BW125K")){
        #ifdef VerboseMode
            SerialDebug.print("pass");
        #endif

        ok++;
        ntest++;
    }else {
        #ifdef VerboseMode
            SerialDebug.print("fail\nReconfiguring DR....");
        #endif
        
        DRConfig();
        ntest++;
    }

    delay(300);
    #ifdef VerboseMode
        SerialDebug.print("\nCH: ");
    #endif
    if (compare("at+ch", "+CH: 8; 0,916800000")) {
        #ifdef VerboseMode
            SerialDebug.print("pass");
        #endif

        ok++;
        ntest++;
    }else {
        #ifdef VerboseMode
            SerialDebug.print("fail\nReconfiguring CH....");
        #endif

        CHConfig();
        ntest++;
    }

    fail = ntest - ok;
    #ifdef VerboseMode
        SerialDebug.println("\n----------------------------------------\n | Tests: " + String(ntest) + " | Passed: " + String(ok) + " | Failed: " + String(fail) + " |\n----------------------------------------\n");
    #endif

    if(fail > 0){
        #ifdef VerboseMode
            SerialDebug.println("Errors found, restarting Config Test....");
        #endif

        if (configCount < MaxConfigTry) {
            configCount++;
        }else {
            #ifdef VerboseMode
                SerialDebug.println("ERROR: Problems found during config test, please check the node and the communication.");
            #endif
            return false;
        }
        testConfig();
    }else {
        return true;
    }
} // end testConfig