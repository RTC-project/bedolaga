#include <ppm.h> 
#define THROTTLE        3
#define ROLL            4
#define PITCH           2
#define YAW             1
#define SWITCH3WAY_1    5
#define BUTTON          6
#define SWITCH3WAY_2    7     // trim-pot for left/right motor mix  (face trim)
#define POT             8     // trim-pot on the (front left edge trim)



int enA = 9;
int in1 = 7;
int in2 = 6;
int enB = 3;
int in3 = 5;
int in4 = 4;
int speed = 0;

const long interval = 50;
unsigned long previousMillis = 0;

void setup()
{
  Serial.begin(115200);
  ppm.begin(A0, false);
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

}

void loop()
{
  // Для чего этот интервал считать?
    unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) { 
    previousMillis = currentMillis;
  }
  //////////////////////////////////
    // Acquiring all the channels values
    short throttle      =   ppm.read_channel(THROTTLE);
    short roll          =   ppm.read_channel(ROLL);
    short pitch         =   ppm.read_channel(PITCH);
    short yaw           =   ppm.read_channel(YAW);
    short switch3way_1  =   ppm.read_channel(SWITCH3WAY_1);
    short button        =   ppm.read_channel(BUTTON);
    short switch3way_2  =   ppm.read_channel(SWITCH3WAY_2);
    short pot           =   ppm.read_channel(POT);
    int track = yaw - 1500;
    int speedL = roll - 1500;
    int frw = throttle - 1500;
    int moveFrw = map(frw,-500,500,-255,255);
    int force = map(track,-400 ,450,-255,255);
    int rollTurn = map(speedL,-400 ,400,-255,255);

    if (force>120){
      force=255;
    }
    
    if (force<-120){
      force=-255;
    }
    // Зачем нужен этот блок? эти переменные ведь ни где не используются
    int speedLeft, speedRight;
    if (rollTurn>0){
      speedLeft = rollTurn + force;
      speedRight = rollTurn - force;
    }
    ///////////////////////////////////////////////////////////////////

    // Print the values for the Arduino Serial Plotter
    Serial.print("Throttle:");        Serial.print(throttle);       Serial.print(" ");
    Serial.print("Roll:");            Serial.print(roll);           Serial.print(" ");
    Serial.print("Pitch:");           Serial.print(pitch);          Serial.print(" ");
    Serial.print("Yaw:");             Serial.print(yaw);            Serial.print(" ");
    Serial.print("Switch_3way_1:");   Serial.print(switch3way_1);   Serial.print(" ");
    Serial.print("Button:");          Serial.print(button);         Serial.print(" ");
    Serial.print("Switch_3way_2:");   Serial.print(switch3way_2);   Serial.print(" ");
    Serial.print("Pot:");             Serial.print(pot);            Serial.print(" ");
    Serial.print("SpeedLeft ");       Serial.print(speedLeft);      Serial.print(" ");
    Serial.print("SpeedRight ");      Serial.print(speedRight);     Serial.print(" ");
    Serial.print("roll ");            Serial.print(rollTurn);       Serial.print(" ");
    Serial.print("FRW ");             Serial.print(moveFrw);        Serial.print(" ");
    Serial.println();
 
 // Если мы считаем мощность левого и правого борта в зависимости от положения стиков, 
 // зачем мы ориентируемся на направление и зачем столько блоков управления моторами?
  if (moveFrw>50){
  analogWrite(enA, force); // здесь может быть отрицательное значение?
  digitalWrite(in1, HIGH);//FORWARD
  digitalWrite(in2, LOW);
  analogWrite(enB, force); // здесь может быть отрицательное значение?
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);// FORWARD
  }
    if (moveFrw<-50){
  analogWrite(enA, force); // здесь может быть отрицательное значение?
  digitalWrite(in1, LOW);//FORWARD
  digitalWrite(in2, HIGH);
  analogWrite(enB, force); // здесь может быть отрицательное значение?
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);// FORWARD
  }
  if (moveFrw<50 && moveFrw >-50){
     if (force>1){
  analogWrite(enA, force); // здесь может быть отрицательное значение?
  digitalWrite(in1, HIGH);//FORWARD
  digitalWrite(in2, LOW);
  analogWrite(enB, force); // здесь может быть отрицательное значение?
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);// FORWARD
  }
    if (force<-1) {
  analogWrite(enA, abs(force));
  digitalWrite(in1, LOW);//FORWARD
  digitalWrite(in2, HIGH);
  analogWrite(enB, abs(force));
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);// FORWARD
                    }
                                 }
  }

  // 
  

