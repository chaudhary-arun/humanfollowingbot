#include<math.h>

float val1, val3, val5, val7,arc=38,angle,radius=6,a,d,t,lat,lon,x,y,test,distance;
int p=1,R=63710,val2,val4;
String inString = "",firstVal, secondVal, thirdVal, forthVal, fifthVal, sixthVal, seventhVal, eighthVal;

void setup()
{
  Serial.begin(9600);
  pinMode(10,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(3,OUTPUT);
  Serial.println("Start listening for GPS Shield...");
}

void loop() 
{
  Serial.println("Re looping");
  while (Serial.available() > 0) 
  {
    inString = Serial.readString();
    for (int i = 0; i < inString.length(); i++) 
    {
      if (inString.substring(i, i+1) == "*")
      {
        firstVal = inString.substring(1, i);
        secondVal = inString.substring(i+1);
        //Serial.println("Latitude: " + (firstVal) + ", second: " + (secondVal)); 
      }
    }
    for (int i = 0; i < secondVal.length(); i++) 
    {
      if (secondVal.substring(i, i+1) == "%")
      {
        thirdVal = secondVal.substring(0, i);
        forthVal = secondVal.substring(i+1);
        //Serial.println("Longitude: " + (thirdVal) + ", forth: " + (forthVal));    
      }
    }

    for (int i = 0; i < forthVal.length(); i++) 
    {
      if (forthVal.substring(i, i+1) == "@")
      {
        fifthVal = forthVal.substring(0, i);
        sixthVal = forthVal.substring(i+1);
        //Serial.println("Accuracy: " + (fifthVal) + ", sixth: " + (sixthVal));    
        //test = fifthVal.toFloat();
      }
    }
 
    for (int i = 0; i < sixthVal.length(); i++) 
    {
      if (sixthVal.substring(i, i+1) == "#")
      {
        seventhVal = sixthVal.substring(0, i);
        eighthVal = sixthVal.substring(i+1);
        //Serial.println("Time: " + (seventhVal) + ", eighth: " + (eighthVal));    
      }
    }
    val2=firstVal.toInt();
    val4=thirdVal.toInt();
    firstVal=firstVal.substring(3);
    thirdVal=thirdVal.substring(3);
    val1 = firstVal.toFloat();
    val3 = thirdVal.toFloat();
    val1=val2+val1/10000000;
    val3=val4+val3/10000000;
    if(p==1){
    lat=val3;
    lon=val1;
    }
    
    Serial.print("Latitude : ");
    Serial.println(val1,7);
    Serial.print("Longitude : ");
    Serial.println(val3,7);
    
    angle=atan(sin(val1-lon)*cos(lat)*cos(val3)*sin(lat)-sin(val3)*cos(lat)*cos(val1-lon));
    Serial.print("angle:");
    Serial.println(angle,7);
    d=angle*arc;
    t=d/(((3.14*2)/3)*radius);
    
    if(angle>0)
    {
      digitalWrite(10,LOW);
      digitalWrite(12,HIGH);
      digitalWrite(3,LOW);
      digitalWrite(2,LOW);
      }
  if(angle<0)
  {
    digitalWrite(10,LOW);
    digitalWrite(12,LOW);
    digitalWrite(2,HIGH);
    digitalWrite(3,LOW);
    Serial.println("here");
    
  }
  Serial.print("time for rotation : ");
  
  if(t<0)
  {
    t=t*-1;
  }
  Serial.println(t);
  delay(t*1000);
    digitalWrite(10,LOW);
    digitalWrite(12,LOW);
    digitalWrite(3,LOW);
    digitalWrite(2,LOW);
    delay(2000);
  
    digitalWrite(12,HIGH);
    digitalWrite(10,LOW);
    digitalWrite(2,HIGH);
    digitalWrite(3,LOW);
    
    Serial.println("Now straight");
    
    
    distance=(acos(sin(lat)*sin(val3)+cos(lat)*cos(val3)*cos(val1-lon)))*R;
    if(distance<0)
    {
      distance=(-1)*distance;
    }
    Serial.println("distance =" );
    Serial.print(distance);
    delay(  (distance/(3.14*(2/3)*radius*1000)));  
    delay(1000);
    digitalWrite(7,LOW);
    digitalWrite(8,LOW);
    digitalWrite(3,LOW);
    digitalWrite(2,LOW);
    p++;
    lat=val3;
    lon=val1;
    
  }

}

