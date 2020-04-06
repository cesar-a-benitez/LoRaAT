# LoRaAT Library

[![Version](https://img.shields.io/github/release/cesar-a-benitez/LoRaAT.svg?style=plastic)](https://github.com/cesar-a-benitez/LoRaAT/releases/tag/v2.0)
[![LatestReleaseDate](https://img.shields.io/github/release-date/cesar-a-benitez/LoRaAT.svg?style=plastic)]((https://github.com/cesar-a-benitez/LoRaAT/releases/tag/v2.0))
![Issues](https://img.shields.io/github/issues/cesar-a-benitez/LoRaAT.svg?style=plastic)
[![License](https://img.shields.io/github/license/desktop/desktop.svg?style=plastic)](https://github.com/desktop/desktop/blob/development/LICENSE)
![Repo Size](https://img.shields.io/github/repo-size/cesar-a-benitez/LoRaAT.svg?style=plastic)
[![Contact](https://img.shields.io/badge/Contact-E--mail-informational.svg?style=plastic)](mailto:cesar.augusto@ecomp.ufsm.br?subject=Contact%20LoRaAT%20Library)
![Follow](https://img.shields.io/github/followers/cesar-a-benitez.svg?label=Follow&style=social)

Library created by: Cesar Augusto B. Barbosa e Thiago Piovesan  
Latin American Center for Open Technologies (CELTAB)  
Itaipu Technological Park (PTI)

***

## Sumary (Sumário)

  - [Sumary (Sumário)](#sumary-sum%c3%a1rio)
  - [About Library (Sobre a Biblioteca)](#about-library-sobre-a-biblioteca)
  - [How to Use (Como Usar)](#how-to-use-como-usar)
  - [Sending Messages (Enviando Mensagens)](#sending-messages-enviando-mensagens)
  - [Enable Watchdog (Habilitar Watchdog)](#enable-watchdog-habilitar-watchdog)
  - [Log Level](#log-level)
  - [Functions List (Lista de Funções)](#functions-list-lista-de-fun%c3%a7%c3%b5es)

## About Library (Sobre a Biblioteca)

  (en)
    This Library was designed to configure and use any LoRaWAN node
    that uses AT commands.

    Notes:
      - This Library was meant to configure LoRaWAN node to the AU915 Frequency Plan
      - The Library initiates Serial Communication with a baud rate of 9600, if you 
      initiate the communication again in the code there may be a crash.
      
    Known Bugs:
      - The testConfig Function doesn't work in Arduino Nano, it'll always reconfigure the node

  (pt-br)
    Esta Biblioteca foi desenvolvida para configurar e usar qualquer
    nó LoRaWAN que use comandos AT.

    Notas:
      - Esta Biblioteca foi idealizada para configurar nós no Plano de Frequência AU915
      - A Biblioteca inicia a Comunicação Serial com um baud rate de 9600, se você inicar
      a comunicação novamente no código pode vir a ocorrer travamentos.
      
    Bugs Conhecidos:
      - A Função testConfig não funciona no Arduino Nano, ele sempre irá reconfigurar o nó

## How to Use (Como Usar)

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
   {
      LoRaAT lora(rx, tx);
   }
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
      lora.config();    // Function to configure the node - Função para configurar o nó
      lora.testConfig); // Function to test the configuration and reconfigure if needed
                        // Função para testar as configurações e reconfigurar se necessário
   }
   ```

## Sending Messages (Enviando Mensagens)

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

Function <br> Função | Description <br> Descrição
----------------|-----------------------
lora.sendMsg(String msg) | Send String Message <br> Envia Mensagem String
lora.sendCMsg(String msg) | Send String Confirmed Message <br> Envia Mensagem String Confirmada
lora.sendMsgHex(String msg) | Send String Hex Message <br> Envia Mensagem String HEX
lora.sendCMsgHex(String msg) | Send String Confirmed HEX Message <br> Envia Mensagem String HEX Confirmada

## Enable Watchdog (Habilitar Watchdog)

(en) To enable Watchdog, just uncomment the definition below, this function uses the ESP8266WiFi.h library  
(pt-br) Para habilitar o Watchdog é apenas descomentar a definição abaixo, esta função usa a biblioteca ESP8266WiFi.h

``` cpp
   #define Watchdog
```

## Log Level

(en) The LogLevel definition is used to determine whether data/debug will be sent by serial  
(pt-br) A definição LogLevel é usada para determinar se os dados/debug serão enviados por serial

Valor | Description <br> Descrição
----|----
0 | No data sent by serial <br> Nenhum dado enviado por serial
1 | Only status sent by serial <br> Apenas status enviado por serial
2 | Debug data sent by serial <br> Dados de debug enviado por serial

## Functions List (Lista de Funções)

(en) Table of Object Configuration Functions  
(pt-br) Tabela de Funções de Configuração de Objeto  

Function <br> Função | Description <br> Descrição
----------------|-----------------------  
LoRaAT(int rx, int tx) | Constructor <br> Construtor
init()                | Initialization Function <br> Função de Inicialização  
  
(en) Table of Parameter Definition Functions   
(pt-br) Funções de Definição de Parâmetros  

Function <br> Função | Description <br> Descrição
----------------|-----------------------
setDevAddr(String DevAddr)   | Pass the DevAddr String to the object <br> Passa a String do DevAddr para o objeto
setDevEui(String DevEui)     | Pass the DevEui String to the object <br> Passa a String do DevEui para o objeto
setAppEui(String AppEui)     | Pass the AppEui String to the object <br> Passa a String do AppEui para o objeto
setNwkSkey(String NwkSkey)   | Pass the NwkSkey String to the object <br> Passa a String do NwkSkey para o objeto
setAppSkey(String AppSkey)   | Pass the AppSkey String to the object <br> Para a String do AppSkey para o objeto
setIDs(String DevAddr, String DevEui, String AppEui) | Pass all the IDs together to the object <br> Passa todos IDs juntos para o objeto
setKeys(String NwkSkey, String AppSkey) | Pass all the Keys together to the object <br> Passa todas as Keys juntas para o objeto

(en) Table of Node Configuration Functions  
(pt-br) Tabela de Funções de Configuração dos Nós  

Function <br> Função | Description <br> Descrição
----------------|-----------------------
config() | Configure the node with the configurations passed <br> Configura o nó com as configurações passadas
testConfig() | Test the configuration and reconfigure if needed, returns true if succeeded and false if not <br> Testa as configurações e reconfigura se necessário, retorna verdadeiro se sucesso ou falso se falhou

(en) Table of Generic Functions  
(pt-br) Tabela de Funções Genéricas  

Function <br> Função | Description <br> Descrição
----------------|-----------------------
sendCmd(String cmd) | Send command via Serial to the node (calls waitMsg() at the end)<br> Envia comandos para o nó via Serial (chama waitMsg() no final)
sendATCmd(String cmd) | Send command via serial to the node <br> Envia comandos para o nó via Serial
compare(String cmd, String ans) | Send a command and compare the received answer <br> Envia um comando e compara a resposta recebida
setTimeDelay(int timeDelay) | Pass a new timeDelay to the functions  <br>  Passa um novo timeDelay para as funções
watchdogRst() | Reset the watchdog of ESP8266 boards <br> Reseta o watchdog de placas ESP8266

(en) Table of Send Message Functions  
(pt-br) Funções de Envio de Mensagens  

Function <br> Função | Description <br> Descrição
----------------|-----------------------
sendMsg(String msg) | Send String Message <br> Envia Mensagem String
sendCMsg(String msg) | Send Confirmed String Message <br> Envia Mensagem String Confirmada
sendMsgHex(String msg) | Send HEX String Message <br> Envia Mensagem String Hex
sendCMsgHex(String msg) | Send Confirmed HEX String Message <br> Envia Mensagem String HEX Confirmada

(en) Table of Wait Message Function  
(pt-br) Função de Espera de Mensagem  

Function <br> Função | Description <br> Descrição
----------------|-----------------------
waitMsg() | Wait the answer and print in via Serial <br> Espera a mensagem e imprime via Serial
waitAnsMsg() | Wait and return the answer <br> Espera e retorna a mensagem <br> (delay = timedelay*2)
waitACK() | Function that waits the receive of an ACK returns true if an ACK has been received or false if not received <br> Função que espera recebimento de um ACK retorna verdadeiro se um ACK foi recebido e falso caso não tenha recebido