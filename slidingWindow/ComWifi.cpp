#include "ComWifi.h";

//const char* ssid       = "";
//const char* password   = "";
//
////ipconfig servidor
//const IPAddress serverIP(192,168,137,1); // La dirección que desea visitar
//uint16_t serverPort = 21;         // Número de puerto del servidor
//
//WiFiClient client;
//
//void wifiSetup(){
//  //connect to WiFi
//  Serial.printf("Connecting to %s ", ssid);
//  WiFi.begin(ssid, password);
//  while (WiFi.status() != WL_CONNECTED) {
//      delay(500);
//      Serial.print(".");
//  }
//  Serial.println(" CONNECTED");
//
//  Serial.print("IP Address:");
//  Serial.println(WiFi.localIP());
//}
//
//void sendData(int dat){
//
//Serial.println("Intenta acceder al servidor");
//    if (client.connect(serverIP, serverPort)) // Intenta acceder a la dirección de destino
//    {
//      while (client.connected()) // Si está conectado o se han recibido datos no leídos
//        {
//              client.print(dat);
//              client.print("\n");         
//        }
//    }
//    
//    else
//    {
//        Serial.println("Acceso fallido");
//        //client.stop(); // Cerrar el cliente
//    }
//  
//}
