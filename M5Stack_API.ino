#include <M5Stack.h>
#include <WiFi.h>
#include <HTTPClient.h>
 
const char* ssid  = "dlink-261E";
const char* senha = "fmqzd20809";
String serverName = "URL-SERVIDOR";
 
void setup() { 
  M5.begin();
  M5.Lcd.fillScreen(GREEN);
  M5.Lcd.setTextColor(PINK);
  M5.Lcd.setTextSize(2);
  
  Serial.begin(115200);
  delay(4000);
  WiFi.begin(ssid, senha); 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    M5.Lcd.fillScreen(GREEN);
    M5.Lcd.setCursor(10, 10);
    M5.Lcd.println("Conectando...");
    WiFi.begin(ssid, senha);
  } 
  M5.Lcd.fillScreen(GREEN);  
  M5.Lcd.setCursor(10, 10);
  M5.Lcd.println("Conectado!");
}
 
void loop() {   
  M5.update(); 
  if ((WiFi.status() == WL_CONNECTED)) {
    HTTPClient http;
    if (M5.BtnA.wasReleasefor(700)) {
      M5.Lcd.fillScreen(GREEN);  
      M5.Lcd.setCursor(10, 10);
      M5.Lcd.println("Carregando...");
      http.begin(serverName+"cadastraValores");
      http.addHeader("Content-Type", "application/json");
      int httpCode = http.POST("{\"nome\":\"Sileide Campos\",\"email\":\"sileidecampos@gmail.com\",\"login\":\"sil\",\"senha\":\"123\",\"cidade\":\"ssa\",\"bairro\":\"bairro\"}");
      
      if (httpCode > 0) {
        String payload = http.getString();
        M5.Lcd.fillScreen(GREEN);  
        M5.Lcd.setCursor(10, 40);
        M5.Lcd.println(payload); 
      }
    } else{
      http.begin(serverName+"retornaValores");
      int httpCode = http.GET();
      if (httpCode > 0) {
        String payload = http.getString();
        M5.Lcd.fillScreen(GREEN);
        M5.Lcd.setCursor(10, 40);
        M5.Lcd.println(httpCode);
        M5.Lcd.println(payload);        
      }else{
        M5.Lcd.fillScreen(GREEN);  
        M5.Lcd.setCursor(10, 40);
        M5.Lcd.println("Erro na requisição");
        M5.Lcd.println(httpCode);
      }
    }
    http.end();
  }
  delay(10000);
}
