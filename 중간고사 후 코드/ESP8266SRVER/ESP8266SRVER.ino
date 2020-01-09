#include <ESP8266WiFi.h>

#include <ESP8266WebServer.h>



const char * ssid = "SMART324_3";

const char * password = "76543210";



const char pageMain[] PROGMEM = R"=====(

<!doctype html>
<html>
<head>
<title>Main Page</title>
</head>
<body>
<h1>This is Main page</h1>
<p><a href="/">Main Page</a></p>
<p><a href="/second_page">Second Page</a></p>
<p><a href="/thrid_page">Thrid page</a></p>
</body>
</html>
)=====";

const char pageSecond[] PROGMEM =R"=====(

<!doctype html>
<html>
<head>
<title>Seconds Page</title>
</head>
<body>
<h1>This is Second page</h1>
<p><a href="/">Main Page</a></p>
<p><a href="/second_page">Second Page</a></p>
<p><a href="/thrid_page">Thrid page</a></p>
</body>
</html>
)=====";



const char pageThrid[] PROGMEM =R"=====(

<!doctype html>
<html>
<head>
<title>Thrid Page</title>
</head>
<body>
<h1>This is Thrid page</h1>
<p><a href="/">Main Page</a></p>
<p><a href="/second_page">Second Page</a></p>
<p><a href="/thrid_page">Thrid page</a></p>
</body>
</html>
)=====";

ESP8266WebServer server(80);


void handleMain(){

  String html = pageMain;
  server.send(200,"text/html", html);

  }

void handleSecondPage(){

  String html = pageSecond;
  server.send(200,"text/html",html);

  }

void handleThridPage(){

  String html = pageThrid;
  server.send(200,"text/html",html);

  }

void setup() {

  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);



  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");

    }

   Serial.println("");
   Serial.print("Connecting to");
   Serial.println(ssid);
   Serial.print("IP address:");
   Serial.println(WiFi.localIP());
   server.on("/",handleMain);
   server.begin();
   server.on("/second_page",handleSecondPage);
   server.begin();
   server.on("/thrid_page",handleThridPage);
   server.begin();



   
   Serial.println("Server started");

}



void loop() {
  server.handleClient();

}
