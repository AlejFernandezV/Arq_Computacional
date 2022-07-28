#include <arduino.h>
//----Pin connections----
#define BUZZER 48
//----Melody - Buzzer----
#define NOTE_c 261
#define NOTE_d 294
#define NOTE_e 329
#define NOTE_f 349
#define NOTE_g 391
#define NOTE_gS 415
#define NOTE_a 440
#define NOTE_aS 455
#define NOTE_b 466
#define NOTE_cH 523
#define NOTE_cSH 554
#define NOTE_dH 587
#define NOTE_dSH 622
#define NOTE_eH 659
#define NOTE_fH 698
#define NOTE_fSH 740
#define NOTE_gH 783
#define NOTE_gSH 830
#define NOTE_aH 880
//----functions----
void toneWith(int nota, int time_ms){
  tone(BUZZER, nota, time_ms);
  delay(time_ms+50);
}
//----StarWars song for the alarm
void song(){
  toneWith(NOTE_a,500);
  toneWith(NOTE_a,500);
  toneWith(NOTE_a,500);
  toneWith(NOTE_f,350);
  toneWith (NOTE_cH,150);
  toneWith(NOTE_a,500);
  toneWith(NOTE_f,350);
  toneWith(NOTE_cH,150);
  toneWith(NOTE_a,500);
  toneWith(NOTE_eH,500);
  toneWith(NOTE_eH,500);
  toneWith(NOTE_eH,500);
  toneWith(NOTE_fH,350);
  toneWith(NOTE_cH,150);
  toneWith(NOTE_gS,500);
  toneWith(NOTE_f,350);
  toneWith(NOTE_cH,150);
  toneWith(NOTE_a,1000);
  toneWith(NOTE_aH,500);
  toneWith(NOTE_a,350);
  toneWith(NOTE_a,150);
  toneWith(NOTE_aH,500);
  toneWith(NOTE_gSH,250);
  toneWith(NOTE_gH,250);
  toneWith(NOTE_fSH,125);
  toneWith(NOTE_fH,125);
  toneWith(NOTE_fSH,250);
  delay(250);
  toneWith(NOTE_aS,250);
  toneWith(NOTE_dSH,500);
  toneWith(NOTE_dH,250);
  toneWith(NOTE_cSH,250);  
  // virtuosismo :)))
  toneWith(NOTE_cH,125);
  toneWith(NOTE_b,125);
  toneWith(NOTE_cH,250);
  delay(250);
  toneWith(NOTE_f,125);
  toneWith(NOTE_gS,500);
  toneWith(NOTE_f,375);
  toneWith(NOTE_a,125);
  toneWith(NOTE_cH,500);
  toneWith(NOTE_a,375);
  toneWith(NOTE_cH,125);
  toneWith(NOTE_eH,1000);
  toneWith(NOTE_aH,500);
  toneWith(NOTE_a,350);
  toneWith(NOTE_a,150);
  toneWith(NOTE_aH,500);
  toneWith(NOTE_gSH,250);
  toneWith(NOTE_gH,250);
  toneWith(NOTE_fSH,125);
  toneWith(NOTE_fH,125);
  toneWith(NOTE_fSH,250);
  delay(250);
  toneWith(NOTE_aS,250);
  toneWith(NOTE_dSH,500);
  toneWith(NOTE_dH,250);
  toneWith(NOTE_cSH,250);
  toneWith(NOTE_cH,125);
  toneWith(NOTE_b,125);
  toneWith(NOTE_cH,250);     
  delay(250);
  toneWith(NOTE_f,250);
  toneWith(NOTE_gS,500);
  toneWith(NOTE_f,375);
  toneWith(NOTE_cH,125);
  toneWith(NOTE_a,500);
  toneWith(NOTE_f,375);
  toneWith(NOTE_c,125);
  toneWith(NOTE_a,1000);
}
