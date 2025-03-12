const int JSEBESSEG = 5;
const int JHATRA = 2;
const int JELORE = 3;

const int BSEBESSEG = 6;
const int BELORE = 4;
const int BHATRA = 7;


void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(JSEBESSEG, OUTPUT);
  pinMode(JHATRA, OUTPUT);
  pinMode(JELORE, OUTPUT);
  pinMode(BSEBESSEG, OUTPUT);
  pinMode(BELORE, OUTPUT);
  pinMode(BHATRA, OUTPUT);

  digitalWrite(JSEBESSEG, HIGH); //minden max sebessegen menjen
  digitalWrite(BSEBESSEG, HIGH);
}

void loop() {

  digitalWrite(BELORE, HIGH);
  digitalWrite(BHATRA, LOW); // bal kereket elloremenetben hajtani

  
}
