#define LED_PIN  13

char alphabet[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
int moses[5][5] = {
  {1, 3, 0, 0, 0},
  {3, 1, 1, 1, 0},
  {3, 1, 3, 1, 0},
  {3, 1, 1, 0, 0},
  {1, 0, 0, 0, 0}
};
int timeEndWord = 7;
int timeEndLetter = 3;
int timeBreak = 1;

String wordToType = "abc";

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  showWord(wordToType);
  showBreakBetweenWords();
}

void showWord(String wordToType) {
  Serial.println("Печать слова");
  for (int i = 0; i < wordToType.length(); i++) {
    char currentLetter = wordToType.charAt(i);
    showLetter(currentLetter);
    if (i + 1 != wordToType.length()) {
      showBreakBetweenLetters();
    }
  }
}

void showLetter(char letter) {
  Serial.println("Печать буквы");
  int elementOfArray = findLetterInAlphabet(letter);
  Serial.println(letter);
  for (int i = 0; i < sizeof(moses[elementOfArray])/sizeof(moses[elementOfArray][0]); i++) {
    if (moses[elementOfArray][i] == 0) break;
    showElement(moses[elementOfArray][i]);
    if (i + 1 != sizeof(moses[elementOfArray])) {
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
  Serial.println("Лампочка выключена");
  Serial.println("***");
  delay(1000 * timeEndLetter);
}

void showBreakBetweenWords() {
  digitalWrite(LED_PIN, LOW);
  Serial.println("Лампочка выключена");
  Serial.println("*******");
  delay(1000 * timeEndWord);
}

void showBreakBetweenElementsOfLetter() {
  digitalWrite(LED_PIN, LOW);
  Serial.println("Лампочка выключена");
  Serial.println("*");
  delay(1000 * timeBreak);
}

void showElement(int timeElement) {
  Serial.println("Лампочка включена");
  digitalWrite(LED_PIN, HIGH);
  if (timeElement == 3) {
    Serial.println("-");
  }
  else Serial.println("*");
  delay(1000 * timeElement);
}
