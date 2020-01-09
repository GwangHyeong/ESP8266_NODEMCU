#include <ESP8266WiFi.h>


//
const char* ssid = "SMART324_3";
const char* password = "76543210";


WiFiServer server(80);


// 변수 지정
int LED_pin = 16;
int turn_on = 0;
int turn_off = 1;


IPAddress ip;
void setup() {

  Serial.begin(115200);
  delay(10);

  pinMode(LED_pin, OUTPUT);
  digitalWrite(LED_pin, turn_off);


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
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  String test3 = client.readString();
  int test1 = client.write('\r');
  int test2 = client.read();
  int test5 = uint16_t();
  Serial.println(request);
  Serial.println("++++++++++++++++++");
  Serial.println(test2);
  Serial.println("++++++++++++++++++");
  Serial.println(test3);

  client.flush(); //문자가 모두 받아질때까지 대기.

  // Match the request
  int value = turn_off;


  //////////////////////////////
  //여기가 문제인듯!
  if (test3.indexOf("ON") != -1)  {
    digitalWrite(LED_pin, turn_on);
    value = turn_on;
  }

  if (test3.indexOf("OFF") != -1)  {
    digitalWrite(LED_pin, turn_off);
    value = turn_off;
  }
  ////////////////////////////////////

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  client.print("Led pin is now: ");

  if (value == turn_on) {
    client.print("On");

  } else {
    client.print("Off");
  }

  client.println("<br><br>");
  ///////
  //포스트 방식 으로 보내기.
  client.println("<form action='\r' method='post'>");
  client.println("  <input type='submit' name='/LED=ON\' value='ON'> ");
  client.println("  <input type='submit' name='/LED=OFF\' value='OFF'> ");

  client.println("</form>");
  //////
  // client.println("<a href=\" /LED=ON\"\"><button>Turn On </button></a>");
  // client.println("<a href=\" /LED=OFF\"\"><button>Turn Off </button></a><br />");
  client.println("<br><br>");

  client.print("<script>");
  client.print(" document.write(\"Hello java Script World!!! \");");
  client.print("</script>");

  client.println("</html>");

  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
}
