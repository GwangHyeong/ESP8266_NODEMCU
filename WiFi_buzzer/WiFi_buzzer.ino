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
  Serial.println(request);
  client.flush();

  // Match the request
  int value = turn_off;
  if (request.indexOf("/do") != -1)  {
    Serial.print("do");
    tone(Buzzer, tones[1]);
    delay(100);
    noTone(Buzzer);
  }

  if (request.indexOf("/re") != -1)  {
    Serial.print("re");
    tone(Buzzer, tones[2]);
    delay(100);
    noTone(Buzzer);
  }
  if (request.indexOf("/mi") != -1)  {
    Serial.print("mi");
    tone(Buzzer, tones[3]);
    delay(100);
    noTone(Buzzer);
  }
  if (request.indexOf("/pa") != -1)  {
    Serial.print("pa");
    tone(Buzzer, tones[4]);
    delay(100);
    noTone(Buzzer);
  }
  if (request.indexOf("/sol") != -1)  {
    Serial.print("sol");
    tone(Buzzer, tones[5]);
    delay(100);
    noTone(Buzzer);
  }
  if (request.indexOf("/ra") != -1)  {
    Serial.print("ra");
    tone(Buzzer, tones[6]);
    delay(100);
    noTone(Buzzer);
  }
  if (request.indexOf("/si") != -1)  {
    Serial.print("si");
    tone(Buzzer, tones[7]);
    delay(100);
    noTone(Buzzer);
  }

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");


  client.println("<br><br>");
  client.println("<form>");
  client.println("<a href=\" /do\"\"><button>do </button></a><br />");
  client.println("<a href=\" /re\"\"><button>re </button></a><br />");
  client.println("<a href=\" /mi\"\"><button>mi </button></a><br />");
  client.println("<a href=\" /pa\"\"><button>pa </button></a><br />");
  client.println("<a href=\" /sol\"\"><button>sol </button></a><br />");
  client.println("<a href=\" /ra\"\"><button>ra </button></a><br />");
  client.println("<a href=\" /si\"\"><button>si </button></a><br />");
  client.println("<br><br>");
  client.println("</form>");
  client.print("<script>");
  client.print(" document.write(\"Hello java Script World!!! \");");
  client.print("</script>");

  client.println("</html>");

  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
}


