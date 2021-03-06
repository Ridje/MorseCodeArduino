#define LED_PIN  13
#define BEEP_PIN 3
//#define DEBUG 1

char alphabet[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
int moses[26][5] = {
  {1, 3, 0, 0, 0},
  {3, 1, 1, 1, 0},
  {3, 1, 3, 1, 0},
  {3, 1, 1, 0, 0},
  {1, 0, 0, 0, 0},
  {1, 1, 3, 1, 0},
  {3, 3, 1, 0, 0},
  {1, 1, 1, 1, 0},
  {1, 1, 0, 0, 0},
  {1, 3, 3, 3, 0},
  {3, 1, 3, 0, 0},
  {1, 3, 1, 1, 0},
  {3, 3, 0, 0, 0},
  {3, 1, 0, 0, 0},
  {3, 3, 3, 0, 0},
  {1, 3, 3, 1, 0},
  {3, 3, 1, 3, 0},
  {1, 3, 1, 0, 0},
  {1, 1, 1, 0, 0},
  {3, 0, 0, 0, 0},
  {1, 1, 3, 0, 0},
  {1, 1, 1, 3, 0},
  {1, 3, 3, 0, 0},
  {3, 1, 1, 3, 0},
  {3, 1, 3, 3, 0},
  {3, 3, 1, 1, 0}
};
int timeEndWord = 7;
int timeEndLetter = 3;
int timeBreak = 1;

String wordToType = "GD";

void setup() {
#ifdef DEBUG
  Serial.begin(9600);
#endif
  pinMode(LED_PIN, OUTPUT);
  pinMode(BEEP_PIN, OUTPUT);
}

void loop() {
  showWord(wordToType);
  showBreakBetweenWords();
}

void showWord(String wordToType) {
#ifdef DEBUG
  Serial.print("Печать слова "); Serial.println(wordToType);
#endif
  for (int i = 0; i < wordToType.length(); i++) {
    char currentLetter = wordToType.charAt(i);
    showLetter(currentLetter);
    if (i + 1 != wordToType.length()) {
      showBreakBetweenLetters();
    }
  }
}

void showLetter(char letter) {
#ifdef DEBUG
  Serial.print("Печать буквы "); Serial.println(letter);
#endif
  int elementOfArray = findLetterInAlphabet(letter);
  for (int i = 0; i < sizeof(moses[elementOfArray]) / sizeof(moses[elementOfArray][0]); i++) {
    if (moses[elementOfArray][i] == 0) break;
#ifdef DEBUG
    Serial.print("Печать элемента "); Serial.println(i + 1);
#endif
    showElement(moses[elementOfArray][i]);
    if (i + 1 != sizeof(moses[elementOfArray]) && moses[elementOfArray][i + 1] != 0) {
      showBreakBetweenElementsOfLetter();
    }
  }
}


int findLetterInAlphabet(char symbol) {
  for (int i = 0; i < sizeof(alphabet); i++) {
    if (alphabet[i] == symbol) {
      return i;
    }
  }
}

void showBreakBetweenLetters() {
  digitalWrite(LED_PIN, LOW);
#ifdef DEBUG
  Serial.println("Лампочка выключена");
  Serial.println("***");
#endif
  delay(1000 * timeEndLetter);
}

void showBreakBetweenWords() {
  digitalWrite(LED_PIN, LOW);
#ifdef DEBUG
  Serial.println("Лампочка выключена");
  Serial.println("*******");
#endif
  delay(1000 * timeEndWord);
}

void showBreakBetweenElementsOfLetter() {
  digitalWrite(LED_PIN, LOW);
#ifdef DEBUG
  Serial.println("Лампочка выключена");
  Serial.println("*");
#endif
  delay(1000 * timeBreak);
}

void showElement(int timeElement) {
#ifdef DEBUG
  Serial.println("Лампочка включена");
#endif
  digitalWrite(LED_PIN, HIGH);
  int beep_freq = 400;
  if (timeElement == 3) {
#ifdef DEBUG
    Serial.println("-");
#endif
    beep_freq = 200;
  }
#ifdef DEBUG
  else {
    Serial.println("*");
  }
#endif
  tone(BEEP_PIN, beep_freq, timeElement * 1000);
  delay(1000 * timeElement);
}
