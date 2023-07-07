#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

// Replace with your network credentials
const char* ssid = "SnoHome2020";
const char* password = "Thisis@Moniga2010@Ugraded";
WebServer server(80);

WiFiServer server2(81);
WiFiClient client;
String ClientRequest;
String myresultat;

String ReadIncomingRequest() {
  while (client.available()) {
    ClientRequest = (client.readStringUntil('\r'));
    if ((ClientRequest.indexOf("HTTP/1.1") > 0) && (ClientRequest.indexOf("/favicon.ico") < 0)) {
      myresultat = ClientRequest;
    }
  }
  return myresultat;
}

String webPage = "";

int LMP = 18;  //Left Motor Positive pole
int LMN = 19;  //Left Motor Negative pole
int RMP = 16;  //Right Motor Positive pole
int RMN = 17;  //Right Motor Negative pole

unsigned int interval = 3000;
unsigned int elapsedMillis;

void setup(void) {

  pinMode(LMP, OUTPUT);
  pinMode(LMN, OUTPUT);
  pinMode(RMP, OUTPUT);
  pinMode(RMN, OUTPUT);

  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println();

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", []() {
    server.send(200, "text/html", webPage);
  });

  // Goes forward
  server.on("/F", []() {
    server.send(200, "text/html", webPage);
    digitalWrite(LMP, HIGH);
    digitalWrite(LMN, LOW);
    digitalWrite(RMP, HIGH);
    digitalWrite(RMN, LOW);
    Serial.println("Moving forward");
    delay(1000);
  });

  // Goes back
  server.on("/B", []() {
    server.send(200, "text/html", webPage);
    digitalWrite(LMP, LOW);
    digitalWrite(LMN, HIGH);
    digitalWrite(RMP, LOW);
    digitalWrite(RMN, HIGH);
    Serial.println("Moving backward");
    delay(100);
  });

  // Turns Right
  server.on("/R", []() {
    server.send(200, "text/html", webPage);
    digitalWrite(LMP, HIGH);
    digitalWrite(LMN, LOW);
    digitalWrite(RMP, LOW);
    digitalWrite(RMN, HIGH);
    Serial.println("Turning right");
    delay(100);
  });

  // Turns  Left
  server.on("/L", []() {
    server.send(200, "text/html", webPage);
    digitalWrite(LMP, LOW);
    digitalWrite(LMN, HIGH);
    digitalWrite(RMP, HIGH);
    digitalWrite(RMN, LOW);
    Serial.println("Turning left");
    delay(100);
  });

  // Stops
  server.on("/S", []() {
    server.send(200, "text/html", webPage);
    digitalWrite(LMP, LOW);
    digitalWrite(LMN, LOW);
    digitalWrite(RMP, LOW);
    digitalWrite(RMN, LOW);
    Serial.println("Stopping");
    delay(100);
  });

  server.begin();

  ClientRequest = "";
  server2.begin();
  Serial.println("HTTP server started");

  elapsedMillis = millis();
}  //end setup()

void loop(void) {
  // Handles all the client connections
  server.handleClient();

  // if (millis() - elapsedMillis > interval) {
  int rnd = random(0, 1024);
  client = server2.available();
  if (!client) { return; }
  while (!client.available()) { delay(1); }
  ClientRequest = (ReadIncomingRequest());
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println((rnd));
  client.println("</html>");
  Serial.println(rnd);
  delay(150);
  client.flush();


  //   elapsedMillis = millis();
  // }
}  //end loop()
