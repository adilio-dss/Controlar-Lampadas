/*
|--------------------------------------
| BOT TELEGRAM COM O MODULO ESP8266
|--------------------------------------
*/

#include "CTBot.h"

CTBot myBot;

/*
|--------------------------------------
| CONFIGURACOES DA REDE WIFI
|--------------------------------------
*/

// SSID (NOME DA REDE WIFI)
String ssid = "Mi Phone";
// PASS (SENHA DA REDE WIFI)
String pass = "1020304050";
// TOKEN (BOT TELEGRAM)
String token = "1003616730:AAEG577qGW_Wtx3p9WzanQOjeWpDcIqWKuw";

/*
|--------------------------------------
| PINOS DAS LAMPADAS
|--------------------------------------
*/
uint8_t lamp1 = 5;
uint8_t lamp2 = 4;

/*
|--------------------------------------
| VARIAVEIS
|--------------------------------------
*/
boolean auth = false;
boolean validate = true;

void setup() {
  Serial.begin(115200);
  Serial.println("Inicializando bot Telegram...");

  // CONEXAO COM REDE A WIFI
  myBot.wifiConnect(ssid, pass);

  // SETAR O TOKEN DO TELEGRAM
  myBot.setTelegramToken(token);

  // TESTAR A CONEXAO COM A REDE WIFI
  if (myBot.testConnection())
    Serial.println("nConexao estabelecida com sucesso!");
  else
    Serial.println("nFalha na conexao!");

  // DEFINICAO DOS PINOS COMO SAIDA
  pinMode(lamp1, OUTPUT);
  pinMode(lamp2, OUTPUT);

  // APAGAR AS LAMPADAS
  digitalWrite(lamp1, HIGH);
  digitalWrite(lamp2, HIGH);
}

void loop() {
  // VARIAVEL QUE ARMAZENA OS COMANDOS RECEBIDOS DO TELEGRAM
  TBMessage command;

  // VERIFICA SE HA COMANDOS PARA SEREM EXECUTADOS
  if (myBot.getNewMessage(command)) {

    if (auth == false) {
      if (command.text.equalsIgnoreCase("123")) {
        auth = true;
        myBot.sendMessage(command.sender.id, "Autenticado!");
      } else {
        if (!validate) {
          myBot.sendMessage(command.sender.id, "Senha invalida");
        }
        myBot.sendMessage(command.sender.id, "Digite a senha");
        validate = false;
      }

    } else {
      // COMANDO "LIGAR 1"
      if (command.text.equalsIgnoreCase("LIGAR 1")) {
        // LIGAR A LAMPADA 1
        digitalWrite(lamp1, LOW);

        // MENSAGEM
        myBot.sendMessage(command.sender.id, "LAMPADA 1 ACESA!");
      }

      // COMANDO "DESLIGAR 1"
      else if (command.text.equalsIgnoreCase("DESLIGAR 1")) {
        // DESLIGAR A LAMPADA 1
        digitalWrite(lamp1, HIGH);

        // MENSAGEM
        myBot.sendMessage(command.sender.id, "LAMPADA 1 APAGADA!");
      }

      // COMANDO "STATUS 1"
      else if (command.text.equalsIgnoreCase("STATUS 1")) {
        String status;
        if (digitalRead(lamp1) == LOW) {
          status = "ACESA!";
        } else {
          status = "APAGADA!";
        }
        myBot.sendMessage(command.sender.id, "LAMPADA 1 " + status + "!");
      }

      // COMANDO "LIGAR 2"
      else if (command.text.equalsIgnoreCase("LIGAR 2")) {
        // LIGAR A LAMPADA 2
        digitalWrite(lamp2, LOW);

        // MENSAGEM
        myBot.sendMessage(command.sender.id, "LAMPADA 2 ACESA!");
      }

      // COMANDO "DESLIGAR 2"
      else if (command.text.equalsIgnoreCase("DESLIGAR 2")) {
        // DESLIGAR A LAMPADA 2
        digitalWrite(lamp2, HIGH);

        // MENSAGEM
        myBot.sendMessage(command.sender.id, "LAMPADA 2 APAGADA!");
      }

      // COMANDO "STATUS 2"
      else if (command.text.equalsIgnoreCase("STATUS 2")) {
        String status;
        if (digitalRead(lamp2) == LOW) {
          status = "ACESA!";
        } else {
          status = "APAGADA!";
        }
        myBot.sendMessage(command.sender.id, "LAMPADA 2 " + status + "!");
      }

      // COMANDO "LIGAR TODAS"
      else if (command.text.equalsIgnoreCase("LIGAR TODAS")) {
        // LIGAR A LAMPADA 1 E 2
        digitalWrite(lamp1, LOW);
        digitalWrite(lamp2, LOW);

        // MENSAGEM
        myBot.sendMessage(command.sender.id, "LAMPADAS ACESAS!");
      }

      // COMANDO "DESLIGAR TODAS"
      else if (command.text.equalsIgnoreCase("DESLIGAR TODAS")) {
        // DESLIGAR A LAMPADA 1 E 1
        digitalWrite(lamp1, HIGH);
        digitalWrite(lamp2, HIGH);

        // MENSAGEM
        myBot.sendMessage(command.sender.id, "LAMPADAS APAGADAS!");
      }

      // COMANDO "STATUS"
      else if (command.text.equalsIgnoreCase("STATUS")) {
        String status;

        // LAMPADAS ACESAS
        if (digitalRead(lamp1) == LOW && digitalRead(lamp2) == LOW) {
          status = "LAMPADAS ACESAS";
        }

        // LAMPADAS APAGADAS
        else if (digitalRead(lamp1) == HIGH && digitalRead(lamp2) == HIGH) {
          status = "LAMPADAS APAGADAS";
        }

        // DEMAIS STATUS
        else {
          status = "LAMPADAS";
          if (digitalRead(lamp1) == LOW) {
            status += " 1 - ACESA |";
          } else {
            status += " 1 - APAGADA |";
          }

          if (digitalRead(lamp2) == LOW) {
            status += " 2 - ACESA";
          } else {
            status += " 2 - APAGADA";
          }
        }
        myBot.sendMessage(command.sender.id, status);
      }

      // COMANDO "MANUAL"
      else if (command.text.equalsIgnoreCase("MANUAL")) {
        String manual = "## MANUAL ##";
        manual += "\nLIGAR 1 => ACENDE A LAMPADA 1";
        manual += "\nLIGAR 2 => ACENDE A LAMPADA 2";
        manual += "\nLIGAR TODAS => ACENDE AS LAMPADAS";
        manual += "\nSTATUS 1 => STATUS DA LAMPADA 1";
        manual += "\nSTATUS 2 => STATUS DA LAMPADA 2";
        manual += "\nSTATUS => STATUS DAS LAMPADAS";
        manual += "\nDESLIGAR 1 => APAGA A LAMPADA 1";
        manual += "\nDESLIGAR 2 => APAGA A LAMPADA 2";
        manual += "\nDESLIGAR TODAS => APAGA AS LAMPADAS";

        // MENSAGEM
        myBot.sendMessage(command.sender.id, manual);
      }

      // COMANDO INVALIDO
      else {
        String reply = "COMANDO INVALIDO";
        reply += "\nDIGITE O COMANDO 'MANUAL'";
        reply += "\n(LISTAR TODOS OS COMANDOS VALIDOS)";

        // MENSAGEM
        myBot.sendMessage(command.sender.id, reply);
      }
    }
  }
  delay(500);
}
