// MSZO Vonalkövető IR szenzor teszt kód
// készítette: Bagi Bulcsú
// bulcsu.bagi@gmail.com

const int LED1 = 8;
const int LED2 = 9;
const int LED3 = 10;
const int LED4 = 11;

int measured_val_1; 
int measured_val_2; 
int measured_val_3;
int measured_val_4; 

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  Serial.begin(9600);
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);
}

void loop() {

  measured_val_1 = analogRead(A0);
  measured_val_2 = analogRead(A1);
  measured_val_3 = analogRead(A2);
  measured_val_4 = analogRead(A3);

  Serial.print(0);
  Serial.print("; ");  
  Serial.print(1024);  
  Serial.print("; ");
  Serial.print(measured_val_1);  
  Serial.print("; "); 
  Serial.print(measured_val_2);  
  Serial.print("; ");
  Serial.print(measured_val_3);  
  Serial.print("; "); 
  Serial.println(measured_val_4);
  delay(100);
}
