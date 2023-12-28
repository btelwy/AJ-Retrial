#ifndef HEADER_FILE //include guard
#define HEADER_FILE

int countLines(FILE*);
int* lineCharCount(FILE*, int);

void addHeader(FILE*);

void convertLine(char[], int, FILE*);
int readCommand(char[], int, int, FILE*);

void textColor(char[], FILE*);
void wait(char[], FILE*);
void textSpeed(char[], FILE*);
void spriteFade(char[], FILE*);
void flash(char[], FILE*);
void shake(char[], FILE*);
void name(char[], FILE*);
void charAnimation(char[], FILE*);
void centerText(char[], FILE*);
void textbox(char[], FILE*);
void courtRecordButton(char[], FILE*);
//void addEvidence(char[], FILE*);
void twoChoices(char[], FILE*);
void threeChoices(char[], FILE*);
void music(char[], FILE*);
void sound(char[], FILE*);
void musicFade(char[], FILE*);
void voiceSFX(char[], FILE*);
void background(char[], FILE*);
void setFlag(char[], FILE*);


#endif //end of include guard