#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <ESP8266mDNS.h>
#include "webPageCode.h"

// Set web server port number to 80
ESP8266WebServer server(80);
// Set WebSockets server on port 81 for real-time communication
WebSocketsServer webSocket = WebSocketsServer(81);

const char* ssid = "Firat IoT";
const char* password = "firatIoT";
const int redLED = 0; // D3
const int greenLED = 4; // D2
const int blueLED = 5; // D1

void setup() {
    pinMode(redLED, OUTPUT);
    pinMode(greenLED, OUTPUT);
    pinMode(blueLED, OUTPUT);
    analogWriteRange(255);
    Serial.begin(115200);

    // Connect to Wi-Fi network with SSID and password
    Serial.println("\n\nConnecting to ");
    Serial.print(ssid);
    WiFi.begin(ssid, password);
    Serial.println("");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    // Print local IP address
    Serial.print("\n\nWiFi connected to ");
    Serial.print(ssid);
    Serial.println(".\nIP address: ");
    Serial.println(WiFi.localIP());

    // Initialize mDNS : Local DNS
    if (!MDNS.begin("FiratIoT")) {
        Serial.println("Error setting up mDNS");
        return;
    }
    Serial.println("mDNS responder started");

    // Start the WebSockets server to begin listening for incoming connections
    webSocket.begin();
    // Callback function to handle WebSocket events
    webSocket.onEvent(webSocketEvent);

    server.on("/", webPage);
    // Start the web server to begin handle HTTP requests
    server.begin();
}

void loop() {
    MDNS.update();
    // Handle incoming WebSocket messages and events
    webSocket.loop();
    // Handle incoming HTTP client requests
    server.handleClient();
}

void webPage() {
    server.send(200, "text/html", webP  ageCode);
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t* payload, size_t length) {
    switch (type) {
        // Client disconnects
    case WStype_DISCONNECTED:
        Serial.printf("[%u] Disconnected!\n", num);
        break;
        // Client connects
    case WStype_CONNECTED:
    {
        // Client IP adress
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
    }
    break;
    // Client sends message
    case WStype_TEXT:
        Serial.printf("[%u] Received text: %s\n", num, payload);
        // Character array to hold the formatted payload
        char formattedPayload[50];

        // Format the payload
        sprintf(formattedPayload, "%s", (char*)payload);

        // If the LED is turned on
        // If the message starts with LED ON
        if (std::strncmp(formattedPayload, "LED ON", std::strlen("LED ON")) == 0) {
            char* commaPos = strchr(formattedPayload, ',');

            if (commaPos != NULL) {
                // Move to the next character after the comma to get the HEX RGB string
                char* rgbStr = commaPos + 1;

                // Convert the RGB hex string to integer values
                unsigned int r, g, b;
                sscanf(rgbStr, "#%2x%2x%2x", &r, &g, &b);

                // Print the extracted RGB values (Optional)
                Serial.printf("Received RGB: R=%u, G=%u, B=%u\n", r, g, b);

                // Set the RGB LED colors
                analogWrite(redLED, r);
                analogWrite(greenLED, g);
                analogWrite(blueLED, b);
            }
            // Sends a message to all the clients to update
            webSocket.broadcastTXT(formattedPayload, length);
            // If the LED is turned off
        }
        else if (strcmp(formattedPayload, "LED OFF") == 0) {
            analogWrite(redLED, 0);
            analogWrite(greenLED, 0);
            analogWrite(blueLED, 0);
            digitalWrite(BUILTIN_LED, HIGH);
            // Sends a message to all the clients to update  
            webSocket.broadcastTXT(formattedPayload, length);
        }

        break;
    default:
        break;
    }
}
