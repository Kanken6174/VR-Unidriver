#include "Wire.h" // This library allows you to communicate with I2C devices.

int fV[6] = {0,100,200,300,400,500};
int gyro[3] = {0,0,0};
int acc[3] = {0,0,0};
int mag[3] = {0,0,0};

bool decrementIMU = false;

bool fC[6] = {false, false, false, false, false, false};

char incoming = "";
String appendSerialData = "";
char ID = 'R';

void setup()
{
  Serial.begin(74800);
  fV[0] = 0;
  fV[1] = 100;
  fV[2] = 200;
  fV[3] = 300;
  fV[4] = 400;
  fV[5] = 500;
}

void setIMU(){
  for(int i = 0; i < 3; i++){
    if(decrementIMU){
      gyro[i]--;
      acc[i]--;
      mag[i]--;
    }else{
      gyro[i]++;
      acc[i]++;
      mag[i]++;
    }

    if(gyro[i] >= 360 && !decrementIMU){
        decrementIMU = true;
    }

    if(gyro[i] <= 0 && decrementIMU){
      decrementIMU = false;
    }
  }
}

void setValues(){
  for(int i = 0; i < 6; i++){
    
    if(fC[i]){
      fV[i]--;
    }else{
      fV[i]++;
    }

    if(fV[i] < 0)
      fC[i] = false;

    if(fV[i] > 800)
      fC[i] = true;
  }
}

//-------------------------------------------------------------------------------------------------------------------------
void loop()
{

  if(Serial.available() > 0) //get the number of bytes (characters) available that already arrived and stored in the serial receive buffer
  {
    incoming = Serial.read();     //read incoming serial data and store it into c variable
    Serial.flush(); //ignore trailing stuff
    appendSerialData += incoming; //append data in c and store it in this variable
  }
  if (incoming == '#') //if data inside c equals to end character (#) which corresponds to "send me data" order
  {
    setIMU();
    setValues();
    Serial.println("A"+String(fV[0])+"B"+String(fV[1])+"C"+String(fV[2])+"D"+String(fV[3])+"E"+String(fV[4])+"F"+String(fV[5])
    +"G"+String(fC[0])+"H"+String(fC[1])+"I"+String(fC[2])+"J"+String(fC[3])
    +"K"+String(gyro[0])+"L"+String(gyro[0])+"M"+String(gyro[0])+"N"+String(gyro[0])+"O"+String(gyro[0])+"P"+String(gyro[0])+"Q"+String(gyro[0])+"R"+String(gyro[0])+"S"+String(gyro[0]));
    incoming = ' ';
  }
  else if (incoming == '?') // end char (?) which corresponds to "kill yourself" order
  {
    incoming = ' ';
  }
  else if (incoming == '!') // end char (!) which corresponds to "identify yourself" order
  {
    Serial.print(ID);
    Serial.print('\n');
    incoming = ' ';
  }
  Serial.flush();
}
