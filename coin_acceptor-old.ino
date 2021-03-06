/*
   Bas on Tech
   This course is part of the courses on https://arduino-tutorials.net
   (c) Copyright 2020 - Bas van Dijk / Bas on Tech
   This code and course is copyrighted. It is not allowed to use these courses commercially
   without explicit written approval
   YouTube:    https://www.youtube.com/c/BasOnTech
   Facebook:   https://www.facebook.com/BasOnTechChannel
   Instagram:  https://www.instagram.com/BasOnTech
   Twitter:    https://twitter.com/BasOnTech
   
*/
// some of the code is copyrighted for now until i can rewrite then it will be lgpl
//https://github.com/BasOnTech/Arduino-Beginners-EN/tree/master/E30-sound-sensor
//http://timewitharduino.blogspot.com/2014/01/isr-based-sketch-for-adafruit-coin.html

//method is opensource feel free to rewrite code, or wait until i can do it.



const int OUT_PIN = 8;
const int SAMPLE_TIME = 60;
unsigned long millisCurrent;
unsigned long millisLast = 0;
unsigned long millisElapsed = 0;

const int threshold1 = 285;
const int threshold2 = 1000;
const int threshold3 = 8000;

float money = 0.0;

// gets incremented by the ISR;
// gets reset when coin was recognized (after train of pulses ends);
volatile int pulses = 0;
volatile long timeLastPulse = 0;

// if loud then residual dont count them knock3

int sampleBufferValue = 0;


void setup() {
  Serial.begin(9600);
    pinMode(OUT_PIN, INPUT);
  pinMode(OUT_PIN,INPUT_PULLUP);
  
}

int count=0;
int count2=0;


void loop() {

  millisCurrent = millis();
  millisElapsed = millisCurrent - millisLast;

  if (digitalRead(OUT_PIN) == LOW) {
    sampleBufferValue++;
  }


  if (millisElapsed > SAMPLE_TIME) {
    // start processing loop

    
    if (sampleBufferValue > 0){
    //Serial.println(sampleBufferValue);
    
    if (sampleBufferValue >= threshold1) 
   {
        Serial.println(sampleBufferValue);
       // count++;
        pulses++;
          timeLastPulse = millis();
         //   Serial.println(count);
            Serial.println("Knock1!");
      if (sampleBufferValue >= threshold2) 
       {
            Serial.println("Knock2!");
          //  pulses++;
          if (sampleBufferValue >= threshold3) 
          {
            Serial.println("Knock3!");
          }
        }
   }
   }
    
    
  }

  if (millisElapsed > SAMPLE_TIME) {
    sampleBufferValue = 0;
    millisLast = millisCurrent;
  }
  
        long timeFromLastPulse = millis() - timeLastPulse;
        
  if (pulses > 0 && timeFromLastPulse > 365)
  {
    //check for doubles for fast coins
    
    // sequence of pulses stopped; determine the coin type;
   // if (pulses == 2)
  //  {
  //    Serial.println("Received dime (2 pulses)");
  //    money += .1;
  //  }
     if (pulses == 3)
    {
      Serial.println("Received quarter (3 pulses)");
      money += .25;
    }
        else if (pulses == 6)
    {
      Serial.println("Received 50 cents (6 pulses)");
      money += .50;
    }
    else if (pulses == 9)
    {
      Serial.println("Received 75 cents (9 pulses)");
      money += .75;
    }
    else if (pulses == 4) //10 pulses
    {
      Serial.println("Received looney (5 pulses)");
      money += 1.0;
    }
    else if (pulses == 8) 
    {
      Serial.println("Received 2looney (10 pulses)");
      money += 2.0;
    }
    else if (pulses == 5)
    {
      Serial.println("Received tooney (5 pulses)");
      money += 2.0;
    }
        else if (pulses == 10) //15 pulses
    {
      Serial.println("Received 2tooney (10 pulses)");
      money += 4.0;
    }
    else
    {
     Serial.print("Unknown coin: ");
      Serial.print(pulses);
      Serial.println(" pulses");
      
      // add 1 to total to try and make a coin
    }

     pulses = 0;
    timeFromLastPulse=0;
    timeLastPulse=0;

  }
  
  
         // delay(8);        // delay in between reads for stability
          
          
}



