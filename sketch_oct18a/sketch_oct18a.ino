#define LED_PIN  13

char alphabet[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
int moses[5][5] = {
  {1, 3, 0, 0, 0},
  {3, 1, 1, 1, 0},
  {3, 1, 3, 1, 0},
  {3, 1, 1, 0, 0},
  {1, 0, 0, 0, 0},
};

String wordToType = "abc";

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {

  pingWord();
  endWord();
}

void pingWord(){
  for (int i = 0; i < sizeof(wordToType); i++) {
    char currentSymbol = wordToType.charAt(i);
    showSymbol(currentSymbol);
  } 
}

void showSymbol(char symbol) {
  int numberOfArray = findInAlphabet(symbol);
  pingASymbol(moses[numberOfArray]);
}

void pingASymbol(int seq[]){

  for (int i = 0; i < sizeof(seq); i++) { 
    digitalWrite(LED_PIN, 13);
    delay(1000* seq[i]);
  }
  
  
}

int findInAlphabet(char symbol) {
  for (int i = 0; i < sizeof(alphabet); i++) {
    if (alphabet[i] == symbol) {
      Serial.print(i);
      return i;
    }
  }
}
