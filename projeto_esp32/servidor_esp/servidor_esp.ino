#include <WiFi.h>

const char *ssid = "nomedarede";
const char *password = "senha";
WiFiServer server(80);
WiFiClient client;

const int ledPin = 13;

void connectToWiFi();
void processClientRequest();

void setup() {
  Serial.begin(9600);
  connectToWiFi();
  server.begin();
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (client.connected()) {
    if (client.available()) {
      processClientRequest();
    }
  } else {
    client = server.available();
  }
}

void connectToWiFi() {
  Serial.println("Conectando ao WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }
  Serial.println("Conectado ao WiFi");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

void processClientRequest() {
  String request = client.readStringUntil('\r');
  Serial.println("Recebido: " + request);

  if (request.indexOf("/ledOn") != -1) {
    digitalWrite(ledPin, HIGH);
    Serial.println("LED ligado");
  } else if (request.indexOf("/ledOff") != -1) {
    digitalWrite(ledPin, LOW);
    Serial.println("LED desligado");
  }

  client.flush();
}
