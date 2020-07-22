int trigPin1 = 11;
int echoPin1 = 12;

int trigPin2 = 10;
int echoPin2 = 13;
long cm1, cm2;

int bucketHeight = 300;
int bucketWidth = 200;

int lRed = 6;
int lGreen = 3;
int lBlue = 5;

void setup() {
  Serial.begin (9600);
  
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  
  pinMode(lRed, OUTPUT);
  pinMode(lGreen, OUTPUT);
  pinMode(lBlue, OUTPUT);
}

long read(int trigger, int echo) {
  digitalWrite(trigger, LOW);
  delayMicroseconds(5);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  
  pinMode(echo, INPUT);
  return pulseIn(echo, HIGH);
}

long getCm(long duration) {
  return (duration/2) / 29.1;
}

float getPercent(int maxDistance, long measured) {
  Serial.print("");
  
  if (measured > maxDistance) {
    return 100;
  }
  if (measured < 0) {
    return 0;
  }
  return (1 - (float(measured) / float(maxDistance))) * 100.0;
}

void printValues(String type, float percent) {
  Serial.print(type);
  Serial.print(": ");
  Serial.print(percent);
  Serial.print("% full");
  Serial.println();
}
 
void loop() {
  cm1 = getCm(read(trigPin1, echoPin1));
  int perc1 = getPercent(bucketHeight, cm1);
  printValues(String("HEIGHT"), perc1);
  
  cm2 = getCm(read(trigPin2, echoPin2));
  int perc2 = getPercent(bucketHeight, cm2);
  printValues(String("WIDTH"), perc2);
  
  int comp = (perc1 + perc2) / 2;
  
  if (comp >= 80) {
    digitalWrite(lRed, 255);
    digitalWrite(lGreen, 0);
    digitalWrite(lBlue, 0);
  } else if (comp >= 40) {
    digitalWrite(lRed, 255);
    digitalWrite(lGreen, 255);
    digitalWrite(lBlue, 0);
  } else {
    digitalWrite(lRed, 0);
    digitalWrite(lGreen, 255);
    digitalWrite(lBlue, 0);
  }
  
  delay(500);
}
