#include <ESP8266WiFi.h>
#define Buzzer D2

const char* ssid = "SMART324_3";
const char* password = "76543210";

int tones[] = {261, 294, 330, 349, 392, 440, 494, 523};
int numTones = 8;

WiFiServer server(80);


// 변수 지정
int LED_pin = 16;
int turn_on = 0;
int turn_off = 1;

IPAddress ip;
void setup() {

  Serial.begin(115200);
  delay(10);

  pinMode(Buzzer, OUTPUT);



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
  String post1 = client.readString();
  Serial.println(request);
  client.flush();

  // Match the request
  int value = turn_off;
  if (request.indexOf("do") != -1)  {
    Serial.print("do");
    music(1);
  }

  if (request.indexOf("re") != -1)  {
    Serial.print("re");
    music(2);
  }
  if (request.indexOf("mi") != -1)  {
    Serial.print("mi");
    music(3);
  }
  if (request.indexOf("pa") != -1)  {
    Serial.print("pa");
    music(4);
  }
  if (request.indexOf("sol") != -1)  {
    Serial.print("sol");
    music(5);
  }
  if (request.indexOf("ra") != -1)  {
    Serial.print("ra");
    music(6);
  }
  if (request.indexOf("si") != -1)  {
    Serial.print("si");
    music(7);
  }

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");


  client.println("<br><br>");
  //포스트 방식 으로 보내기.
  client.println("<form action='\r' method='post'>");
  client.println("  <input type='submit' name='/do\' value='do'> ");
  client.println("  <input type='submit' name='/re\' value='re'> ");
  client.println("  <input type='submit' name='/mi\' value='mi'> ");
  client.println("  <input type='submit' name='/pa\' value='pa'> ");
  client.println("  <input type='submit' name='/sol\' value='sol'> ");
  client.println("  <input type='submit' name='/ra\' value='ra'> ");
  client.println("  <input type='submit' name='/si\' value='si'> ");

  client.println("</form>");
  client.print("<script>");
  client.print(" document.write(\"Hello java Script World!!! \");");
  client.print("</script>");

  client.println("</html>");

  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
}
void music(int mdata)
{
  tone(Buzzer, tones[mdata]);
  delay(100);
  noTone(Buzzer);
}

