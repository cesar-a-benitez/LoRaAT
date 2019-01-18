# LoRa AT Library
Library created by: Cesar Augusto B. Barbosa e Thiago Piovesan  
Latin American Center for Open Technologies (CELTAB)    
Itaipu Technological Park (PTI)

  ***
## About Library (Sobre a Biblioteca):
  (en)
    This Library was designed to configure and use any LoRaWAN node
    that uses AT commands.

    Notes:
      - This Library was meant to configure LoRaWAN node to the AU915 Frequency Plan
      - The Library initiates Serial Communication with a baud rate of 9600, if you 
      initiate the communication again in the code there may be a crash.
      
    Known Bugs:
      - The testConfig Function doesn't work in Arduino Nano, it'll always reconfigure
      the node
          

  (pt-br)
    Esta Biblioteca foi desenvolvida para configurar e usar qualquer
    nó LoRaWAN que use comandos AT.
 
    Notas:
      - Esta Biblioteca foi idealizada para configurar nós no Plano de Frequência AU915
      - A Biblioteca inicia a Comunicação Serial com um baud rate de 9600, se você inicar
      a comunicação novamente no código pode vir a ocorrer travamentos.
      
    Bugs Conhecidos:
      - A Função testConfig não funciona no Arduino Nano, ele sempre irá reconfigurar o nó
          

***
## How to use (Como usar):
  1. (en) Download the library and import it into the Arduino IDE  
     (pt-br) Baixe a biblioteca e importe-a para o Arduino IDE
      
  2. (en) Add the library into your code  
     (pt-br) Adicione a biblioteca ao código fonte
      
   ```cpp
   #include <LoRaAT.h>
   ```
  3. (en) Create an object  
     (pt-br) Crie um objeto
     
   ```cpp
   LoRaAT lora(rx, tx);
   ```
    Notes (Notas):
      (en) At the creation of the object you will need to set the Rx and Tx ports that you want to use
      (pt-br) Na criação do objeto você precisará definir quais são as portas Rx e Tx que deseja usar
  
  4.  (en) In order to start the object you'll have to use the init function  
       (pt-br) Para que se possa iniciar o objeto você deverá usar a função init
       
   ```cpp
   {
      lora.init();
   }
   ```
   
  5. (en) You will have to create the Keys and IDs Strings, and then pass it to the object  
     (pt-br) Você terá de criar as Strings de Chaves e IDs, e então passa-las para o objeto
     
   ```cpp
   {
      String DevAddr = "XXXXXXXX";
      String DevEui  = "XXXXXXXXXXXXXXXX";
      String AppEui  = "XXXXXXXXXXXXXXXX";
    
       /**
        *    (en) 
        *       You can either pass it at once, using the function setIDs and/or setKeys
        *       As you can pass it individualy
        *
        *    (pt-br) 
        *       Você pode tanto passar todas de uma vez usando as funções setIDs e/ou setKeys
        *       Como você também pode passar individualmente
        */
    
      lora.setIDs(DevAddr, DevEui, AppEui) // Passing the IDs together - Passando os IDs juntos
     
      lora.setDevAddr(DevAddr); // Passing the DevAddr to the object - Passando o DevAddr para o objeto
      lora.setDevEui(DevEui);   // Passing the DevEui to the object - Passando o DevEui para o objeto
      lora.setAppEui(AppEui);   // Passing the AppEui to the object - Passando o AppEui para o objeto
   }
   ```
   6. (en) To configure the node you'll have to use the config function or the testConfig function  
      (pt-br) Para configurar o nó você deve usar a função config ou a função testConfig
   
   ```cpp
   {
      lora.config(); // Function to configure the node - Função para configurar o nó
      
      lora.testConfig); // Function to test the configuration and reconfigure if needed
                        // Função para testar as configurações e reconfigurar se necessário
   }
   ```
   
   ***
   ## Sending Messages (Enviando Mensagens):
   (en)  
   The Library supports 4 types of messages to send:  
   * String Message  
   * String Confirmed Message  
   * String HEX Message  
   * String Confirmed HEX Message  
   
   (pt-br)  
   A Biblioteca suporta 4 tipos de mensagens para enviar:  
   * Mensagem String  
   * Mensagem String Confirmada  
   * Mensagem String HEX  
   * Mensagem String HEX Confirmada
   
   ```cpp
   {
      lora.sendMsg(String msg);     // Send String Message - Envia Mensagem String
      lora.sendCMsg(String msg);    // Send String Confirmed Message - Envia Mensagem String Confirmada
      lora.sendMsgHEX(String msg);  // Send String Hex Message - Envia Mensagem String HEX
      lora.sendCMsgHEX(String msg); // Send String Confirmed HEX Message - Envia Mensagem String HEX Confirmada
  }
  ```
  
  ***
  ## Functions List (Lista de Funções):
  ```cpp
  {
      // Object Configuration Functions - Funções de Configuração do Objeto
      LoRaAT(int rx, int tx);   // Constructor - Construtor
      init();   // Initialization Function - Função de Inicialização
      
      // Parameter Definition Functions - Funções de Definição de Parâmetros
      setDevAddr(String DevAddr);   // Pass the DevAddr String to the object - Passa a String do DevAddr para o objeto
      setDevEui(String DevEui);     // Pass the DevEui String to the object - Passa a String do DevEui para o objeto
      setAppEui(String AppEui);     // Pass the AppEui String to the object - Passa a String do AppEui para o objeto
      setNwkSkey(String NwkSkey);   // Pass the NwkSkey String to the object - Passa a String do NwkSkey para o objeto
      setAppSkey(String AppSkey);   // Pass the AppSkey String to the object - Para a String do AppSkey para o objeto
      
      setIDs(String DevAddr, String DevEui, String AppEui); // Pass all the IDs together to the object - Passa todos IDs juntos para o objeto
      setKeys(String NwkSkey, String AppSkey); // Pass all the Keys together to the object - Passa todas as Keys juntas para o objeto
      
      // Node Configuration Functions - Funções de Configuração dos Nós
      config();       // Configure the node with the configurations passed - Configura o nó com as configurações passadas
      testConfig();   //  Test the configuration and reconfigure if needed - Testa as configurações e reconfigura se necessário
      
      // Generic Functions - Funções Genéricas
      sendCmd(String cmd);              // Send command via Serial to the node - Envia comandos para o nó via Serial
      compare(String cmd, String ans);  // Send a command and compare the received answer - Envia um comando e compara a resposta recebida
      loop();   // Function to test the Serial Communication via Serial Console - Função para testar a comunicação Serial usando o Console Serial
      setTimeDelay(int timeDelay);      // Pass a new timeDelay to the functions - Passa um novo timeDelay para as funções
      
      // Send Message Functions - Funções de Envio de Mensagens
      sendMsg(String msg);     // Send String Message - Envia Mensagem String
      sendCMsg(String msg);    // Send Confirmed String Message - Envia Mensagem String Confirmada
      sendMsgHEX(String msg);  // Send HEX String Message - Envia Mensagem String HEX
      sendCMsgHEX(String msg); // Send Confirmed HEX String Message - Envia Mensagem String HEX Confirmada
      
      // Wait Message Function - Função de Espera de Mensagem
      waitMsg();    // Wait the answer and print in via Serial - Espera a mensagem e imprime via Serial
      waitAnsMsg(); // Wait and return the answer - Espera e retorna a mensagem - (delay = timedelay*2)
}
```
