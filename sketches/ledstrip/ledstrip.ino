#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid      = "olmani";
const char* password  = "Irisistop7!";

ESP8266WebServer server(80);

const int REDPIN = 12; // D6
const int BLUEPIN = 15; // D8 (was 13(D7))
const int GREENPIN = 16; // D0 (was 14(D5))

// rgb variables
int r = 0;
int g = 0;
int b = 0;

void setup(){
  // change PWM range
  analogWriteRange(255);
  
  // set pin modes
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  // test
  digitalWrite(REDPIN, HIGH);
  delay(300);
  digitalWrite(REDPIN, LOW);
  digitalWrite(GREENPIN, HIGH);
  delay(300);
  digitalWrite(GREENPIN, LOW);
  digitalWrite(BLUEPIN, HIGH);
  delay(300);
  digitalWrite(BLUEPIN, LOW);

  // begin serial
  Serial.begin(115200);
  delay(100);

  // connect to WiFi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
    digitalWrite(REDPIN, HIGH);
    delay(250);
    digitalWrite(REDPIN, LOW);
  }

  // connected
  digitalWrite(BLUEPIN, HIGH);
  delay(50);
  digitalWrite(BLUEPIN, LOW);
  delay(50);
  digitalWrite(GREENPIN, HIGH);
  delay(50);
  digitalWrite(GREENPIN, LOW);
  delay(50);
  digitalWrite(REDPIN, HIGH);
  delay(50);
  digitalWrite(REDPIN, LOW);

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // pagina
  server.on("/langzaam", langzaam);
  server.on("/direct", direct);
  server.on("/", pickColor);

  // Start the server
  server.begin();
  Serial.println("Server started");

}


void loop() {

  server.handleClient();

}

void langzaam() { 

  digitalWrite(LED_BUILTIN, LOW);
  delay(10);
  digitalWrite(LED_BUILTIN, HIGH);

  int r2 = 0;
  int g2 = 0;
  int b2 = 0;
  
  if (server.arg("r") != ""){
    r2 = server.arg("r").toInt();
  } else {
    r2 = r;
  }
  
  if (server.arg("g") != ""){
    g2 = server.arg("g").toInt();
  } else {
    g2 = g;
  }
  
  if (server.arg("b") != ""){
    b2 = server.arg("b").toInt();
  } else {
    b2 = b;
  }

  server.send(200, "text/plain", "Verwerkt");
  
  fade(r2,g2,b2);  
  
  digitalWrite(LED_BUILTIN, LOW);
  delay(10);
  digitalWrite(LED_BUILTIN, HIGH);
  
}

void direct() { 

  digitalWrite(LED_BUILTIN, LOW);
  delay(10);
  digitalWrite(LED_BUILTIN, HIGH);
  
  if (server.arg("r") != ""){
    r = server.arg("r").toInt();
    analogWrite(REDPIN, r);
  }
  
  if (server.arg("g") != ""){
    g = server.arg("g").toInt();
    analogWrite(GREENPIN, g);
  }
  
  if (server.arg("b") != ""){
    b = server.arg("b").toInt();
    analogWrite(BLUEPIN, b);
  }

  server.send(200, "text/plain", "Verwerkt");
  
  digitalWrite(LED_BUILTIN, LOW);
  delay(10);
  digitalWrite(LED_BUILTIN, HIGH);
  
}

void pickColor() {

  String html ="<!DOCTYPE html> <html> <head> <title>Led strip</title> <meta charset=\"utf-8\"> <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\"> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> <style> body{ background-color: rgb(0,0,0); text-align: center; padding: 40px 0 0 0; } fieldset{ border: none; } output{ display: inline-block; min-width: 2.5em; } label, output{ padding: 2px 9px; border-radius: 3px; font-family: 'Roboto', sans-serif; color: #000; font-size: 1.1em; } label[for=r], output[for=r]{ background-color: #f00; } label[for=g], output[for=g]{ background-color: #0f0; } label[for=b], output[for=b]{ background-color: #00f; } #hex{ min-width: 4.5em; font-size: 3em; background: rgba(255,255,255,.3); } button { padding: 12px 60px; margin: 4px 2px; }\" </style> </head> <body> <fieldset> <label for=\"r\">R</label> <input type=\"range\" min=\"0\" max=\"255\" id=\"r\" step=\"1\" value=\"0\"> <output for=\"r\" id=\"r_out\">0</output> </fieldset> <fieldset> <label for=\"g\">G</label> <input type=\"range\" min=\"0\" max=\"255\" id=\"g\" step=\"1\" value=\"0\"> <output for=\"g\" id=\"g_out\">0</output> </fieldset> <fieldset> <label for=\"b\">B</label> <input type=\"range\" min=\"0\" max=\"255\" id=\"b\" step=\"1\" value=\"0\"> <output for=\"b\" id=\"b_out\">0</output> </fieldset> <output id=\"hex\">#000000</output> <div><button onClick=\"change(0,0,0)\" style=\"background-color:rgb(0,0,0)\"></button></div> <div><button onClick=\"change(255,255,255)\" style=\"background-color:rgb(255,255,255)\"></button></div> <div><button onClick=\"change(255,172,68)\" style=\"background-color:rgb(255,172,68)\"></button></div> <div><button onClick=\"change(255,44,0)\" style=\"background-color:rgb(255,44,0)\"></button></div> <div><button onClick=\"change(255,0,0)\" style=\"background-color:rgb(255,0,0)\"></button></div> <div><button onClick=\"change(0,255,0)\" style=\"background-color:rgb(0,255,0)\"></button></div> <div><button onClick=\"change(0,0,255)\" style=\"background-color:rgb(0,0,255)\"></button></div> <script> var body = document.body, r = document.querySelector('#r'), g = document.querySelector('#g'), b = document.querySelector('#b'), r_out = document.querySelector('#r_out'), g_out = document.querySelector('#g_out'), b_out = document.querySelector('#b_out'), hex_out = document.querySelector('#hex'); function setColor(){ var r_hex = parseInt(r.value, 10).toString(16), g_hex = parseInt(g.value, 10).toString(16), b_hex = parseInt(b.value, 10).toString(16), hex = \"#\" + pad(r_hex) + pad(g_hex) + pad(b_hex); body.style.backgroundColor = hex; hex_out.value = hex; } function pad(n){ return (n.length<2) ? \"0\"+n : n; } function change(r,g,b) { r_out.value = r; document.getElementById(\"r\").value = r; g_out.value = g; document.getElementById(\"g\").value = g; b_out.value = b; document.getElementById(\"b\").value = b; setColor(); var xmlHttp = new XMLHttpRequest(); xmlHttp.open( \"GET\", \"http://192.168.178.66/langzaam?r=\" + r + \"&g=\" + g + \"&b=\" + b, true ); xmlHttp.send( null ); } r.addEventListener('change', function() { setColor(); r_out.value = r.value; var xmlHttp = new XMLHttpRequest(); xmlHttp.open( \"GET\", \"http://192.168.178.66/langzaam?r=\" + r.value, true ); xmlHttp.send( null ); }, false); r.addEventListener('input', function() { setColor(); r_out.value = r.value; }, false); g.addEventListener('change', function() { setColor(); g_out.value = g.value; var xmlHttp = new XMLHttpRequest(); xmlHttp.open( \"GET\", \"http://192.168.178.66/langzaam?g=\" + g.value, true ); xmlHttp.send( null ); }, false); g.addEventListener('input', function() { setColor(); g_out.value = g.value; }, false); b.addEventListener('change', function() { setColor(); b_out.value = b.value; var xmlHttp = new XMLHttpRequest(); xmlHttp.open( \"GET\", \"http://192.168.178.66/langzaam?b=\" + b.value, true ); xmlHttp.send( null ); }, false); b.addEventListener('input', function() { setColor(); b_out.value = b.value; }, false); </script> </body> </html>";

  server.send(200, "text/html", html);

  digitalWrite(LED_BUILTIN, LOW);
  delay(30);
  digitalWrite(LED_BUILTIN, HIGH);
  
}

void fade(int r2, int g2, int b2) {
  double steps = 30.0;
  double r_step = ((double)(r2-r))/steps;
  double g_step = ((double)(g2-g))/steps;
  double b_step = ((double)(b2-b))/steps;
  
  for (int i=1; i<=steps; i++) {
    analogWrite(REDPIN, (int)(r+r_step*i));
    analogWrite(GREENPIN, (int)(g+g_step*i));
    analogWrite(BLUEPIN, (int)(b+b_step*i));
    delay(30);
  }

  r = r2;
  g = g2;
  b = b2;
  
}



