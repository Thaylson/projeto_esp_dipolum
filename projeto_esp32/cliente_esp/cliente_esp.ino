#include <WiFi.h>

const char *ssid = "nomededarede";
const char *password = "senha";
const char *serverIP = "ip_servidor";

const int buttonPin = 2;

WiFiClient client;

void connectToWiFi();
void sendButtonState();
void handleButtonPress();

void setup() {
    Serial.begin(9600);
    connectToWiFi();

    pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
    sendButtonState();
    delay(1000); // Aguarde 1 segundo entre as leituras
}

void connectToWiFi() {
    Serial.println("Conectando ao WiFi");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Conectando ao WiFi...");
    }
    Serial.println("Conectado ao WiFi");
}

void sendButtonState() {
    int buttonState = digitalRead(buttonPin);

    if (client.connect(serverIP, 80)) {
        Serial.println("Enviando estado do botão: " + String(buttonState));
        client.print("GET /");

        if (buttonState == LOW) {
            client.print("ledOn");
        } else {
            client.print("ledOff");
        }

        client.println(" HTTP/1.1");
        client.println("Host: esp-server");
        client.println("Connection: close");
        client.println();
        delay(2000);
    } else {
        Serial.println("Falha na conexão com o servidor");
    }

    if (buttonState == LOW) {
        handleButtonPress();
    }
}

void handleButtonPress() {
    Serial.println("Botão pressionado no cliente");
}
