#include <WiFi.h>
#include <WebServer.h>


const char* ssid = "WebBased-MoistureSensor";
const char* password = "TestPass12"; // Min 8 characters

// Moisture Sensor Pin
const int sensor_pin = x;  //set x to your pin here 


WebServer server(80);


void handleRoot() {
  int sensor_analog = analogRead(sensor_pin);
  int moisture = 100 - ((sensor_analog / 4095.00) * 100);

  String moistureStatus = (moisture > 60) ? "<span class='green'>GOOD/span>" : "<span class='red'>BAD</span>";

  String html = "<!DOCTYPE html><html><head>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<style>body { font-family: Arial; text-align: center; background: #f4f4f4; padding: 20px; }";
  html += ".card { background: white; padding: 20px; border-radius: 10px; box-shadow: 0px 0px 10px rgba(0,0,0,0.1); }";
  html += ".green { color: green; font-size: 50px; } .red { color: red; font-size: 50px; }";
  html += "</style>";
  html += "<script>setTimeout(function(){ location.reload(); }, 30000);</script>";
  html += "</head><body>";

  html += "<div class='card'><h1>Soil Moisture Sensor</h1>";
  html += "<h2>Moisture Level: " + String(moisture) + "%</h2>";
  html += "<h2>" + moistureStatus + "</h2>";
  html += "<p>Updating every 30 seconds...</p></div>";

  html += "</body></html>";

  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);


  WiFi.softAP(ssid, password);
  Serial.print("Access Point Created. Connect to: ");
  Serial.println(ssid);


  server.on("/", handleRoot);
  server.begin();
  Serial.println("Web Server Started.");
  Serial.print("192.168.4.1");
}

void loop() {
  server.handleClient(); 
}