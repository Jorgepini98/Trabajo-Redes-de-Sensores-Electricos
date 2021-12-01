#include "NTP.h";

// Credentials
const char* ssid       = "SURFACEJORGE2228";
const char* password   = "p0@926G8";//


const char* ntpServer = "europe.pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;


String getLocalTime(){  
  struct tm timeinfo;
  String tiempo_actual = "";
  
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return "";
  }
  tiempo_actual = String(timeinfo.tm_hour) + ":" +
                  String(timeinfo.tm_min) + ":" +
                  String(timeinfo.tm_sec) + "\n";

                  //(&timeinfo, "%A, %B %d %Y %H:%M:%S");
                  
  return tiempo_actual;
}

void NTP_Setup(){

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println(" CONNECTED");
  
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  getLocalTime();

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  
}
