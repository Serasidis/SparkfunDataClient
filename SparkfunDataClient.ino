/*
   Arduino SparkFun data client (data.sparkfun.com). 
   
   Created:     Vassilis Serasidis
   Date:        30 Jul 2014
   Last update: 03 Aug 2014
   Version:     1.00
   Home:        http://www.serasidis.gr
   email:       avrsite@yahoo.gr , info@serasidis.gr
   
   Tested with Arduino IDE 1.5.7 and UIPEthernet v1.57
  
 -= SparkFun data client =-
 
    * Create your own data stream (https://data.sparkfun.com)
    * You can mark your data as public or private during the data stream creation.
    * Replace PUBLIC_KEY and PRIVATE_KEY with these sparkfun give you
    * Replace the data names "humidity", "maxTemp" etc on sendToSparkfunDataServer() with those
      gave you sparkfun data stream creation.
    * You can view online or download your data as CSV or JSON file via 
      https://data.sparkfun.com/streams/ + YOUR_PUBLIC_KEY
      
      https://data.sparkfun.com/streams/WGGWNZLKGOFAzyLwLOzQ
      
      GET /input/WGGWNZLKGOFAzyLwLOzQ?private_key=XRRmzj9YR2iXzjnKn6zR&humidity=25.81&maxTemp=26.94&nowTemp=14.48
 */

#include <SPI.h>
#include <UIPEthernet.h>

char sparkfunDataServer[] = "data.sparkfun.com";
#define PUBLIC_KEY  "WGGWNZLKGOFAzyLwLOzQ" //Your SparkFun public_key
#define PRIVATE_KEY "XRRmzj9YR2iXzjnKn6zR" //Your SparkFun private_key

#define SPARKFUN_UPDATE_TIME 60000         //Update SparkFun data server every 60000 ms (1 minute).

#define TIMEOUT 1000 //1 second timout

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xAE, 0xCD };
IPAddress ip(192, 168, 1, 250); //Your local IP

#define RELAY 5 //Relay is connected on Arduino pin 5 (through tranzistor of course).

// Initialize the Ethernet client.
EthernetClient client;

unsigned long timer1 = 0;
unsigned long timer2 = 0;

int failedResponse = 0;
String humidity;
String maxTemp;
String currentTemp;


//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void setup()
{
  pinMode(RELAY, OUTPUT);
  delay(1000);
  
  //Initiallize the serial port.
  Serial.begin(9600);

  // start the Ethernet connection:
  Ethernet.begin(mac, ip);
}
  
//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void loop()
{
  //Update sparkfun data server every 60 seconds.
  if(millis() > timer1 + SPARKFUN_UPDATE_TIME)
  {
      timer1 = millis(); //Update timer1 with the current time in miliseconds.
      sendToSparkfunDataServer(); //Send data to sparkfun data server.
  }
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void sendToSparkfunDataServer()
{ 
    //Establish a TCP connection to sparkfun server.
    if (client.connect(sparkfunDataServer, 80))
    {
        //if the client is connected to the server...
        if(client.connected())
        {
            // send the HTTP PUT request:
            client.print("GET /input/");
            client.print(PUBLIC_KEY);
            client.print("?private_key=");
            client.print(PRIVATE_KEY);
            client.print("&humidity=");
            client.print(random(0,100)); //Send a random number from 0-100 or ...
            //client.print(humidity);    //send the number stored in 'humidity' variable. Select only one.
            client.print("&maxTemp=");   // I don't use it. I add it as an example.
            //client.print(maxTemp);      
            client.print("&nowTemp="); 
            client.println(random(0,40));    //Send a random number from 0-40 or ...
            //client.println(currentTemp);   //send the number stored in 'currentTemp' variable. Select only one.
         
            delay(1000);
            timer2 = millis();
            while((client.available() == 0)&&(millis() < timer2 + TIMEOUT)); //Wait here until server respond or timer2 expires. 
            
            // if there are incoming bytes available
            // from the server, read them and print them:
            while(client.available() > 0)
            {
                char inData = client.read();
                Serial.println(inData);
            }         
            client.stop(); //Disconnect the client from server.  
         }
     } 
}
