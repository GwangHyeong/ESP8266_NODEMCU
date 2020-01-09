#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
WiFiServer server(80); 

char   host[]      = "api.thingspeak.com"; // ThingSpeak address
String APIkey      = "914884";             // Thingspeak Read Key, works only if a PUBLIC viewable channel
String APIreadkey  = "47CMNSC7XDGQ0ZGX";   // Thingspeak Read Key, works only if a PUBLIC viewable channel
const int httpPort = 80;
 
const char *ssid     = "SMART324_3"; 
const char *password = "76543210"; 
WiFiClient client;
const unsigned long HTTP_TIMEOUT = 10000;  // max respone time from server

// ###################
#define PUBLIC  // define this as PUBLIC or PRIVATE to access the channels as required by their security setting
// ###################

void setup(){
  Serial.begin(115200);
  WiFi.begin(ssid,password);
}

void loop(){
  RetrieveTSChannelData();
  delay(30000); //Wait before we request again
}

void RetrieveTSChannelData() {  // Receive data from Thingspeak
  static char responseBuffer[3*1024]; // Buffer for received data
  client = server.available(); 
  if (!client.connect(host, httpPort)) { 
    Serial.println("connection failed"); 
    return; 
  } 
  String url = "/channels/" + APIkey; // Start building API request string
  //GET /channels/CHANNEL_ID/feeds.json?api_key=<your API key>&results=2
  #ifdef PRIVATE 
  url += "/fields/1.json?results=5";  // 5 is the results request number, so 5 are returned, 1 woudl return the last result received
  #else
  url += "/fields/1.json?api_key="+APIreadkey+"&results=5";  // 5 is the results request number, so 5 are returned, 1 woudl return the last result received
  #endif
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
  Serial.println("\n\r"+String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
  while (!skipResponseHeaders());                      // Wait until there is some data and skip headers
  while (client.available()) {                         // Now receive the data
    String line = client.readStringUntil('\n');
    if ( line.indexOf('{',0) >= 0 ) {                  // Ignore data that is not likely to be JSON formatted, so must contain a '{'
      Serial.println(line);                            // Show the text received
      line.toCharArray(responseBuffer, line.length()); // Convert to char array for the JSON decoder
      decodeJSON(responseBuffer);                      // Decode the JSON text
    }
  }
  client.stop();
}

bool skipResponseHeaders() { 
  char endOfHeaders[] = "\r\n\r\n"; // HTTP headers end with an empty line 
  client.setTimeout(HTTP_TIMEOUT); 
  bool ok = client.find(endOfHeaders); 
  if (!ok) { Serial.println("No response or invalid response!"); } 
  return ok; 
} 

bool decodeJSON(char *json) {
  StaticJsonBuffer <3*1024> jsonBuffer;
  char *jsonstart = strchr(json, '{'); // Skip characters until first '{' found and ignore length, if present
  if (jsonstart == NULL) {
    Serial.println("JSON data missing");
    return false;
  }
  json = jsonstart;
  JsonObject& root = jsonBuffer.parseObject(json); // Parse JSON
  if (!root.success()) {
    Serial.println(F("jsonBuffer.parseObject() failed"));
    return false;
  }
  JsonObject& root_data = root["channel"]; // Begins and ends within first set of { }
  String id   = root_data["id"];
  String name = root_data["name"];
  String field1_name = root_data["field1"];
  String datetime    = root_data["updated_at"];
  Serial.println("\n\n Channel id: "+id+" Name: "+ name);
  Serial.println(" Readings last updated at: "+datetime);
  
  for (int result = 0; result < 5; result++){
    JsonObject& channel = root["feeds"][result]; // Now we can read 'feeds' values and so-on
    String entry_id     = channel["entry_id"];
    String field1value  = channel["field1"];
    Serial.print(" Field1 entry number ["+entry_id+"] had a value of: ");
    Serial.println(field1value);
  }
}
