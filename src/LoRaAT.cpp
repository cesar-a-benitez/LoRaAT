/**
 *  Library created by: Cesar Augusto B. Barbosa e Thiago Piovesan
 *      Latin American Center for Open Technologies (CELTAB) 
 * 
 *          Itaipu Technological Park (PTI)
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
 * 
 */

//#define DebugMode // Uncomment to activate the Serial Debug
#include "LoRaAT.h"


LoRaAT::LoRaAT(int rx, int tx) {
    // Set Rx and Tx ports
    _rx = rx;
    _tx = tx;
}

void LoRaAT::init() {
    // Starts the Serial connections
    LoRaNode = new SoftwareSerial(_rx, _tx);
    LoRaNode->begin(9600);
    SerialDebug.begin(9600);
    _timeDelay = 600;
}

void LoRaAT::setDevAddr(String DevAddr) {
    // Set DevAddr individually
    _DevAddr = DevAddr;
    _DevAddr.toUpperCase();
    SerialDebug.println("DevAddr: " + _DevAddr);
}

/**
 *  Attention:
 *      The set functions of IDs or Keys do not set it right away to the node
 *      it only set it up to the Library, the node configuration part is done
 *      in the config or testConfig functions.
 */

void LoRaAT::setDevEui(String DevEui) {
    // Set DevEui individually
    _DevEui = DevEui;
    _DevEui.toUpperCase();
    SerialDebug.println("DevEui: " + _DevEui);
}

void LoRaAT::setAppEui(String AppEui) {
    // setAppEui individually
    _AppEui = AppEui;   
    _AppEui.toUpperCase();
    SerialDebug.println("AppEui: " + _AppEui);
}

void LoRaAT::setNwkSkey(String NwkSkey) {
    // Set NwkSkey individually
    _NwkSkey = NwkSkey;
    _NwkSkey.toUpperCase();
    SerialDebug.println("NwkSkey: " + _NwkSkey);
}

void LoRaAT::setAppSkey(String AppSkey) {
    // Set AppSkey individually
    _AppSkey = AppSkey;
    _AppSkey.toUpperCase();
    SerialDebug.println("AppSkey: " + _AppSkey);
}

void LoRaAT::setKeys(String NwkSkey, String AppSkey) {
    // Set NwkSkey and AppSkey keys
    _NwkSkey = NwkSkey;
    _NwkSkey.toUpperCase();
    SerialDebug.println("NwkSkey: " + _NwkSkey);
    _AppSkey = AppSkey;
    _AppSkey.toUpperCase();
    SerialDebug.println("AppSkey: " + _AppSkey);
}

void LoRaAT::setIDs(String DevAddr, String DevEui, String AppEui) {
    // Set DevAddr, DevEui and AppEui keys
    _DevAddr = DevAddr;
    _DevAddr.toUpperCase();
    SerialDebug.println("DevAddr: " + _DevAddr);
    _DevEui = DevEui;
    _DevEui.toUpperCase();
    SerialDebug.println("DevEui: " + _DevEui);
    _AppEui = AppEui;
    _AppEui.toUpperCase();
    SerialDebug.println("AppEui: " + _AppEui);
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

    #ifdef DebugMode
        while (LoRaNode->available())
            SerialDebug.write(LoRaNode->read());
        SerialDebug.println("");
        delay(300);
    #endif

    LoRaNode->flush();
} // end waitMsg

void LoRaAT::config() {
    // Configuration function
    SerialDebug.println("\nConfig Started...\n\nConfiguring ID Keys...");

    /**
     * Config ID Keys
     */
    
    sendCmd("AT");
    sendCmd("AT+ID=DevAddr, " + _DevAddr);
    sendCmd("AT+ID=DevEui, " + _DevEui);
    sendCmd("AT+ID=AppEui, " + _AppEui);

    /**
     * Calling the functions responsables to configure DR (DataRate) and CH (Channels)
     */
    DRConfig();
    CHConfig();

    
} // end config

void LoRaAT::DRConfig() {
    // Data Rate Configuration function
    SerialDebug.println("Configuring ports and channels...");
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
    SerialDebug.println("Setting up channels....");
    sendCmd("AT");
    sendCmd("AT+CH=0, 916.8");
    delay(50);
    sendCmd("AT+CH=1, 917.2");
    delay(50);
    sendCmd("AT+CH=2, 917.4");
    delay(50);
    sendCmd("AT+CH=3, 917.6");
    delay(50);
    sendCmd("AT+CH=4, 917.8");
    delay(50);
    sendCmd("AT+CH=5, 918");
    delay(50);
    sendCmd("AT+CH=6, 918.2");
    delay(50);
    sendCmd("AT+CH=7, 918.5");
    delay(50);

    // Deleting the unused channels that the DR US915 has set up
    for(int cont=8; cont < 73; cont++) {
        sendCmd("AT+CH=" + String(cont) + ",0");
        delay(50);
    }
    SerialDebug.println("Channels settup finished....");
    
    SerialDebug.println("\nConfig Finished...\n");
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
    sendCmd("AT+MSG=" + msg);
}

void LoRaAT::sendCMsg(String msg) {
    // Send Confirmed Message Function
    sendCmd("AT+CMSG=" + msg);
}

void LoRaAT::sendMsgHex(String msg) {
    // Send HEX Message Function
    sendCmd("AT+MSGHEX=" + msg);
}

void LoRaAT::sendCMsgHex(String msg) {
    // Send Confirmed HEX Message Function
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
        loraread:
        #ifdef DebugMode
            SerialDebug.write(LoRaNode->read());
        #endif
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
                return true;
            }else {
                x++;
            }
        }
    }

    #ifdef DebugMode
        SerialDebug.println("\n\nx: " + String(x) + "  -  ans: " + ans.length() + "\n----------------------------------------\n");
    #endif

    return false;
} // end compare

void LoRaAT::testConfig() {
    // Function responsable to test if the node is configured
    // If is not configured the Function will configure it
    int ok = 0, ntest = 0, fail = 0;

    SerialDebug.println("\n----------------------------------------\n        Starting Config Test:\n");

    SerialDebug.print("DevAddr: ");
    if (compare("at+id=devaddr", "+ID: DevAddr, " + _DevAddr)) {
        SerialDebug.print("pass");
        ok++;
        ntest++;
    }else {
        SerialDebug.print("fail\nReconfiguring DevAddr....");
        sendCmd("at+id=devaddr, " + _DevAddr);
        ntest++;
    }

    SerialDebug.print("\nDevEui: ");
    if (compare("at+id=deveui", "+ID: DevEui, " + _DevEui)) {
        SerialDebug.print("pass");
        ok++;
        ntest++;
    }else {
        SerialDebug.print("fail\nReconfiguring DevEui....");
        sendCmd("at+id=deveui, " + _DevEui);
        ntest++;
    }

    SerialDebug.print("\nAppEui: ");
    if (compare("at+id=appeui", "+ID: AppEui, " + _AppEui)) {
        SerialDebug.print("pass");
        ok++;
        ntest++;
    }else {
        SerialDebug.print("fail\nReconfiguring AppEui....");
        sendCmd("at+id=appeui, " + _AppEui);
        ntest++;
    }

    SerialDebug.print("\nDR: ");
    if (compare("at+dr", "+DR: DR0\n+DR: AU915 DR0  SF12 BW125K")){
        SerialDebug.print("pass");
        ok++;
        ntest++;
    }else {
        SerialDebug.print("fail\nReconfiguring DR....");
        DRConfig();
        ntest++;
    }

    delay(300);
    SerialDebug.print("\nCH: ");
    if (compare("at+ch", "+CH: 8; 0,916800000")) {
        SerialDebug.print("pass");
        ok++;
        ntest++;
    }else {
        SerialDebug.print("fail\nReconfiguring CH....\n");
        CHConfig();
        ntest++;
    }

    fail = ntest - ok;
    SerialDebug.println("\n----------------------------------------\n | Tests: " + String(ntest) + " | Passed: " + String(ok) + " | Failed: " + String(fail) + " |\n----------------------------------------\n");

    if(fail > 2){
        SerialDebug.println("More than 2 errors found, restarting Config Test....");
        testConfig();
    }
} // end testConfig