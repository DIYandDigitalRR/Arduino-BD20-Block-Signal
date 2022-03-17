int Sensor = 10; //Sensor is setup on Pin 10
int Green1 = 2; //Green Signal 1 on Pin 2
int Yellow1 = 3;
int Red1 = 4;
int Green2 = 5;
int Yellow2 = 6;
int Red2 = 7;//Sets up all of our separate signals on their pins
int BlockASend = 8;//Sets up signal to be sent to previous block
int BlockBSend = 9;//Sets up Signal to be sent to next block
int blockARec = A0; //Sets up A0 as pin for receiving signal from previous block
int blockBRec = A1; //Sets up A1 as pin for receiving signal from next block
int clearcount;

void setup() {
  Serial.begin(9600);

  //Establish all of our pins as inputs or outputs

  pinMode(Sensor, INPUT);
  pinMode(Green1, OUTPUT);
  pinMode(Yellow1, OUTPUT);
  pinMode(Red1, OUTPUT);
  pinMode(Green2, OUTPUT);
  pinMode(Yellow2, OUTPUT);
  pinMode(Red2, OUTPUT);
  pinMode(BlockASend, OUTPUT);
  pinMode(BlockBSend, OUTPUT);
  pinMode(blockARec, INPUT);
  pinMode(blockBRec, INPUT);
}

enum SIGNALSTATES
{
ST_GG,
ST_GY,
ST_YG,
ST_YY,
ST_RR,
ST_YY1,
};//Sets up different signal states to switch to

SIGNALSTATES signalState = ST_GG;//GG is the default signal state

void loop() {
  int valA1 = digitalRead(Sensor);//Reads Sensor
  int valA2 = analogRead(blockARec);//Reads Block A
  int valA3 = analogRead(blockBRec);//Reads Bock B
  Serial.println(valA1);
  Serial.println(valA2);
  Serial.println(valA3);//Allows for values to be read on Serial Monitor
  delay(200);

 switch(signalState)
 {
  case ST_GG:
  signalgg(valA1, valA2, valA3);
  break;
  case ST_GY:
  signalgy(valA1, valA2, valA3);
  break;
  case ST_YG:
  signalyg(valA1, valA2, valA3);
  break;
  case ST_YY:
  signalyy(valA1, valA2, valA3);
  break;
  case ST_RR:
  signalrr(valA1, valA2, valA3);
  break;
 case ST_YY1:
  signalyy1(valA1, valA2, valA3);
  break;
    //This sets up our different loops within the main loop to switch between signal states
  }
}

void signalgg(int valA1, int valA2, int valA3) {
  digitalWrite(Green1, LOW); //Turns Green 1 On
  digitalWrite(Yellow1, HIGH);
  digitalWrite(Red1, HIGH);
  digitalWrite(Green2, LOW); //Turns Green 2 On
  digitalWrite(Yellow2, HIGH);
  digitalWrite(Red2, HIGH);
  digitalWrite(BlockASend, LOW); //No signal from this block
  digitalWrite(BlockBSend, LOW); //No signal from this block
  Serial.println("No Train");//Allows text to be seen in serial monitor
  delay(200);
  clearcount = 0;

  if ((valA1 > 0) && (valA2 < 1000) && (valA3 > 1000)) {
    signalState = ST_GY;//Block clear but Block B occupied
  }
  if ((valA1 > 0) && (valA2 > 1000) && (valA3 < 1000)) {
    signalState = ST_YG;//Block clear but Block A occupied
  }
  if ((valA1 > 0) && (valA2 > 1000) && (valA3 > 1000)) {
    signalState = ST_YY;//Block clear but blocks A and B are occupied
  }
  if (valA1 < 1) {
    signalState = ST_RR;//Block occupied
  }
}
void signalgy(int valA1, int valA2, int valA3) {
  digitalWrite(Green1, LOW); //Turns Green 1 On
  digitalWrite(Yellow1, HIGH);
  digitalWrite(Red1, HIGH);
  digitalWrite(Green2, HIGH);
  digitalWrite(Yellow2, LOW);// Turns Yellow 2 On
  digitalWrite(Red2, HIGH);
  digitalWrite(BlockASend, LOW); //No signal from this block
  digitalWrite(BlockBSend, LOW); //No signal from this block
  Serial.println("Approach with Caution");//Allows text to be seen in serial monitor
  delay(200);


  if ((valA1 > 0) && (valA2 < 1000) && (valA3 < 1000)) {
    signalState = ST_GG;//Block clear
  }
  if ((valA1 > 0) && (valA2 > 1000) && (valA3 < 1000)) {
    signalState = ST_YG;//Block clear but Block A occupied
  }
  if ((valA1 > 0) && (valA2 > 1000) && (valA3 > 1000)) {
    signalState = ST_YY;//Block clear but blocks A and B are occupied
  }
  if (valA1 < 1) {
    signalState = ST_RR;//Block occupied
  }
}
void signalyg(int valA1, int valA2, int valA3) {
  digitalWrite(Green1, HIGH);
  digitalWrite(Yellow1, LOW);//Turns Yellow 1 On
  digitalWrite(Red1, HIGH);
  digitalWrite(Green2, LOW); //Turns Green 2 On
  digitalWrite(Yellow2, HIGH);
  digitalWrite(Red2, HIGH);
  digitalWrite(BlockASend, LOW); //No signal from this block
  digitalWrite(BlockBSend, LOW); //No signal from this block
  Serial.println("No Train");//Allows text to be seen in serial monitor
  delay(200);


  if ((valA1 > 0) && (valA2 < 1000) && (valA3 > 1000)) {
    signalState = ST_GY;//Block clear but Block B occupied
  }
  if ((valA1 > 0) && (valA2 < 1000) && (valA3 < 1000)) {
    signalState = ST_GG;//Block clear
  }
  if ((valA1 > 0) && (valA2 > 1000) && (valA3 > 1000)) {
    signalState = ST_YY;//Block clear but blocks A and B are occupied
  }
  if (valA1 < 1) {
    signalState = ST_RR;//Block occupied
  }
}
void signalyy(int valA1, int valA2, int valA3) {
  digitalWrite(Green1, HIGH);
  digitalWrite(Yellow1, LOW);//Turns Yellow 1 On
  digitalWrite(Red1, HIGH);
  digitalWrite(Green2, HIGH);
  digitalWrite(Yellow2, LOW);//Turns Yellow 2 On
  digitalWrite(Red2, HIGH);
  digitalWrite(BlockASend, LOW); //No signal from this block
  digitalWrite(BlockBSend, LOW); //No signal from this block
  Serial.println("No Train");//Allows text to be seen in serial monitor
  delay(200);


  if ((valA1 > 0) && (valA2 < 1000) && (valA3 > 1000)) {
    signalState = ST_GY;//Block clear but Block B occupied
  }
  if ((valA1 > 0) && (valA2 > 1000) && (valA3 < 1000)) {
    signalState = ST_YG;//Block clear but Block A occupied
  }
  if ((valA1 > 0) && (valA2 < 1000) && (valA3 < 1000)) {
    signalState = ST_GG;//Block clear but blocks A and B are occupied
  }
  if (valA1 < 1) {
    signalState = ST_RR;//Block occupied
  }
}
void signalrr(int valA1, int valA2, int valA3) {
  digitalWrite(Green1, HIGH);
  digitalWrite(Yellow1, HIGH);
  digitalWrite(Red1, LOW);//Turns on Red 1
  digitalWrite(Green2, HIGH);
  digitalWrite(Yellow2, HIGH);
  digitalWrite(Red2, LOW);//Turns on Red 2
  digitalWrite(BlockASend, HIGH); //signal from this block
  digitalWrite(BlockBSend, HIGH); //signal from this block
  Serial.println("Block is Occupied");//Allows text to be seen in serial monitor
  delay(200);

  if (valA1 > 0) {
    signalState = ST_YY1; //switches over to the transition yellow signal state
  }
}

void signalyy1(int valA1, int valA2, int valA3) {
  digitalWrite(Green1, HIGH);
  digitalWrite(Yellow1, LOW);//Turns Yellow 1 On
  digitalWrite(Red1, HIGH);
  digitalWrite(Green2, HIGH);
  digitalWrite(Yellow2, LOW);//Turns Yellow 2 On
  digitalWrite(Red2, HIGH);
  digitalWrite(BlockASend, HIGH); //signal from this block
  digitalWrite(BlockBSend, HIGH); //signal from this block
  Serial.println("Block is Occupied");//Allows text to be seen in serial monitor
  delay(1000);

  if ((valA1 > 0) && (clearcount < 5)) {
    clearcount++;
  }
  else if ((valA1 < 1) && (clearcount < 5)) {
    clearcount = 0; //checks for false positives of clear track
  }
  else if ((valA1 > 0) && (clearcount > 4)) {
    signalState = ST_GG;//resets to beginning
  }
}
