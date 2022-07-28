#include "lcd.h"
void funcMenu(void (* fShow)(int pos), bool (*fProcess )(int pos),int nOpt);
void showOptions(char upOption[], char downOption[]);
void showOptions(char upOption[],int upValue, char downOption[]);
void showOptions(char upOption[],int upValue, char downOption[],int downValue);
