#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>
#include <SPI.h>
#include <Ethernet.h>

int LEDPIN = 11; // your LED PIN

int LED2    =  3;
int LED3    =  4;
int LED4    =  5;
int tempPin =  1;
float temp;

YunServer server;


bool Contains(String s, String search) {
    int max = s.length() - search.length();

    for (int i = 0; i <= max; i++) {
        if (s.substring(i) == search) return true; // or i
    }

    return false; //or -1
} 

void setup() {
  // Start our connection
  Serial.begin(9600);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
 

  //digitalWrite(LEDPIN,HIGH); // turn on Led while connecting
  Bridge.begin();  

 
  
  // server.listenOnLocalhost();
  server.begin();
 
}

void loop() {
  // Listen for clients
  YunClient client = server.accept();
  // Client exists?
  if (client) {
    // Lets process the request!
    process(client);
    client.stop();
  }
  delay(50);
}

void process(YunClient client) {
  // Collect user commands
  String command = client.readStringUntil('\\'); // load whole string

  
 // String command = client.readStringUntil('/');
  
  // Enable HTML
  client.println("Status: 200");
  client.println("Content-type: text/html");
  client.println();
  
  // Show UI
  client.println("<B><Center>");
  client.println("<a href='http://www.ericklan.com:8080/arduino/1\\'>Turn ON LED</a><br>");
  client.println("<a href='http://www.ericklan.com:8080/arduino/2\\'>Turn OFF LED</a><br>");

   client.println("<a href='http://www.ericklan.com:8080/arduino/3\\'>Turn ON TURBO</a><br>");
  client.println("<a href='http://www.ericklan.com:8080/arduino/4\\'>Turn OFF TURBO</a><br>");

  
  client.print("Command: ");
  client.println(command);
  client.println("</B></Center>");
  
//command.trim();

 int inChar = command.toInt();
  // Turn on
  if (inChar == 1)   {
    
    client.print("Command: ");
    client.println(command);
    digitalWrite(LED2,HIGH);

    digitalWrite(LED3,HIGH);    
 
  } 
  
  // Turn off
  if (inChar == 2) {
        digitalWrite(LED2,LOW);

    digitalWrite(LED3,LOW);
  }


  // Turn off
  if (inChar == 3) {
        digitalWrite(LED2,HIGH);
        digitalWrite(LED3,HIGH);
        digitalWrite(LED4,HIGH);
  }

  if (inChar == 4) {
        digitalWrite(LED4,LOW);

  }

 //getting the voltage reading from the temperature sensor
 int reading = analogRead(tempPin);  

 client.println("reading: ");
 client.println(reading);


  float mv = ( reading/1024.0)*5000; 

  float cel = mv/10;
                                               
 
  client.println(" degrees C: ");
  client.println(cel);
  Serial.print(cel); Serial.println(" degress C");

 delay(900);
}
