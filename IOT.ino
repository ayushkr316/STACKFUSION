/*
 * Author name : Ayush Kumar
 * Date created : 17/12/2020
 * Date updated : 18/12/2020
 * Email : ayushkr316@gmail.com
*/


#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
String Gtrequest; 
unsigned long startTime, endTime, queryTime; //timer variables

void setup() 
{
  Serial.begin(115200);
  WiFi.begin("Ayush", "AKM01234"); //user id and password WIFI
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(300);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());//IPaddress Printing
}

void loop() 
{
  // put your main code here, to run repeatedly:
if(WiFi.status()== WL_CONNECTED)
  {
    HTTPClient http;
    startTime = millis(); //records the time stamp just before get request was made
    //get request
    http.begin("https://fastag-internal.parkzap.com/account/mockable_test/"); //API
    int httpCode = http.GET();                                 
    if (httpCode > 0) 
    {   
        Gtrequest = http.getString();
    }
    else 
    {
      Serial.println("Error on HTTP request");
    }
    //After get request
      endTime = millis();      //records the time stamp just after  the transaction made
      //parsing  the data into myobject
      JSONVar myObject = JSON.parse(Gtrequest);  // JSON.typeof(jsonVar) can be used to get the type of the var
      if (JSON.typeof(myObject) == "undefined") 
      {
        Serial.println("Parsing input failed!");
        return;
      }
      queryTime=(endTime-startTime);// Exact timme for query
      String x=Serial.readString();//reading key from user
      JSONVar value = myObject[x];// returning the  value of the key
      Serial.println(value);
      Serial.println("Time for query : ");
      Serial.print(queryTime);
   }
}
