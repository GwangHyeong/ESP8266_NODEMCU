#include <ESP8266WiFi.h>

 

const char* ssid = "SMART324_3"; // 네트워크 이름

const char* password = "76543210"; // 네트워크 비밀번호

 

WiFiServer server(80);

 

// 변수 지정

int LED_pin_R = 5; // D1

int LED_pin_G = 4; // D2

int LED_pin_B = 0; // D3

 

// Anode

int turn_on = 1;

int turn_off = 0;

 

// Cathode

// int turn_on = 1;

// int turn_off = 0;

 

void setup() {

  Serial.begin(115200);

  delay(10);

 

  pinMode(LED_pin_R, OUTPUT);

  pinMode(LED_pin_G, OUTPUT);

  pinMode(LED_pin_B, OUTPUT);

  digitalWrite(LED_pin_R, turn_off);

  digitalWrite(LED_pin_G, turn_off);

  digitalWrite(LED_pin_B, turn_off);

 

  // Connect to WiFi network

  Serial.println();

  Serial.println();

  Serial.print("Connecting to ");

  Serial.println(ssid);

 

  WiFi.begin(ssid, password);

 

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");

  }

  Serial.println("");

  Serial.println("WiFi connected");

 

  // Start the server

  server.begin();

  Serial.println("Server started");

 

  // Print the IP address

  Serial.print("Use this URL to connect: ");

  Serial.print("http://");

  Serial.print(WiFi.localIP());

  Serial.println("/");

 

}

 

void loop() {

  // Check if a client has connected

  WiFiClient client = server.available();

  if (!client) {

    return;

  }

 

  // Wait until the client sends some data

  Serial.println("new client");

  while(!client.available()){

    delay(1);

  }

 

  // Read the first line of the request

  String request = client.readStringUntil('\r');

  Serial.println(request);

  client.flush();

 

  // Match the request

 

  int value_R = turn_off;

  int value_G = turn_off;

  int value_B = turn_off;

 

  if (request.indexOf("/LED_R=ON") != -1)  {

    digitalWrite(LED_pin_R, turn_on);

    value_R = turn_on;

  }

  if (request.indexOf("/LED_R=OFF") != -1)  {

    digitalWrite(LED_pin_R, turn_off);

    value_R = turn_off;

  }

 

  if (request.indexOf("/LED_G=ON") != -1)  {

    digitalWrite(LED_pin_G, turn_on);

    value_G = turn_on;

  }

  if (request.indexOf("/LED_G=OFF") != -1)  {

    digitalWrite(LED_pin_G, turn_off);

    value_G = turn_off;

  }

 

  if (request.indexOf("/LED_B=ON") != -1)  {

    digitalWrite(LED_pin_B, turn_on);

    value_B = turn_on;

  }

  if (request.indexOf("/LED_B=OFF") != -1)  {

    digitalWrite(LED_pin_B, turn_off);

    value_B = turn_off;

  }

 

  // Return the response

  client.println("HTTP/1.1 200 OK");

  client.println("Content-Type: text/html");

  client.println(""); //  do not forget this one

  client.println("<!DOCTYPE HTML>");

  client.println("<html>");

 

  client.println("<meta http-equiv='Content-Type' content='text/html' charset='utf-8'/>");

 

  client.println("<br><br>");

  client.println("<a href=\"/LED_R=ON\"\"><button> 빨간색 ON </button></a>");

  client.println("<a href=\"/LED_R=OFF\"\"><button> 빨간색 OFF </button></a><br/>");

  client.println("<a href=\"/LED_G=ON\"\"><button> 녹색 ON </button></a>");

  client.println("<a href=\"/LED_G=OFF\"\"><button> 녹색  OFF </button></a><br/>");

  client.println("<a href=\"/LED_B=ON\"\"><button> 파랑색 ON </button></a>");

  client.println("<a href=\"/LED_B=OFF\"\"><button> 파랑색 OFF </button></a><br/>");

  client.println("</html>");

 

  delay(1);

  Serial.println("Client disonnected");

  Serial.println("");

 

}

