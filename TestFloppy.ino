/*
   ----
   Floppy Player Library.

   This library makes your arduino able to play music using a
   floppy disk drive.

   Made by Rumd3x.

   This library was intensively tested and its extremely reliable.
   ----
   "dirpin" corresponds to pin 18 on the Floppy Drive.
   "steppin" corresponds to pin 12 AND 20 on the Floppy Drive.

   When the "dirpin" is set to LOW(0v/Gnd) it will go forward, and backward when set to HIGH(5v).
   When the "steppin" is on falling edge (going from HIGH(5v) to LOW(0v/Gnd)) it steps on 
   the direction that is at the "dirpin".

   Going Forward -> Moving towards the center.
   Going Backward -> Moving away from the center.
   ----
   ----
   _finitialize:

   This function is used to setup the Arduino and the Floppy Drive.
   It sets the pins set as "dirpin" and "steppin" as outputs, and makes the
   floppy step motor bring the reader read all the way back (to pos == 0) and
   then be able to track it, and control it, so when playing stuff it doesn't
   get jammed around and screwing then sound.

   This function doesn't return any value.

   Example:

   _finitialize();
   Sets up the floppy drive, and the arduino.   
   ----
   ----
   _fplay_hz:

   The _fplay_hz can play sound frequencies between 30Hz to 500Hz.

   This function doesn't return any value.

   Example:

   _fplay_hz(50, 1000);
   This will play a 50Hz on the floppy drive for 1 second.

   _fplay_hz(650, 500);
   Playing a note that is out of range (650Hz) will cause a pause.
   In this example it will pause for 500ms.
   ----
   ----
   _fplay_note:

   Plays a note acording to the table below.
   Note: All notes below 11 and note 60 doesn't work. All the others up to 59 do.

   This function doesn't return any value.

   Example

   _fplay_note(25, 1000);
   This will play a C#2 for a second.

   _fplay_note(5, 250);
   This will play no sound for 1/4 seconds.

   Note Table:
   C0 - 0 - Lowest
   C#0/Db0 - 1
   D0 - 2
   D#0/Eb0 - 3
   E0 - 4
   F0 -5
   F#0/Gb0 - 6
   G0 - 7
   G#0/Ab0 - 8
   A0 - 9
   A#0/Bb0 - 10
   B0 - 11
   C1 - 12
   C#1/Db1 - 13
   D1 - 14
   D#1/Eb1 - 15
   E1 - 16
   F1 - 17
   F#1/Gb1 - 18
   G1 - 19
   G#1/Ab1 - 20
   A1 - 21
   A#1/Bb1 - 22
   B1 - 23
   C2 - 24
   C#2/Db2 - 25
   D2 - 26
   D#2/Eb2 - 27
   E2 - 28
   F2 - 29
   F#2/Gb2 - 30
   G2 - 31
   G#2/Ab2 - 32
   A2 - 33
   A#2/Bb2 - 34
   B2  - 35
   C3  - 36
   C#3/Db3 - 37
   D3 - 38
   D#3/Eb3 - 39
   E3 - 40
   F3 - 41
   F#3/Gb3 - 42
   G3 - 43
   G#3/Ab3 - 44
   A3  - 45
   A#3/Bb3 - 46
   B3 - 47
   C4 - 48
   C#4/Db4 - 49
   D4 - 50
   D#4/Eb4 - 51
   E4 - 52
   F4 - 53
   F#4/Gb4 - 54
   G4 - 55
   G#4/Ab4 - 56
   A4 - 57
   A#4/Bb4 - 58
   B4  - 59
   C5  - 60 - Highest
   ----
   ----
   _step_once:

   This makes the floppy reader head move by 1 position.
   As the function suggests, it makes the step-motor step once.

   When executed, the reader head will go forward all the way to the end and then will
   go back all the way to the beggining.

   This function doesn't return any value.

   Example:

   _step_once();
   This will make the motor move 1 step in any direction.
   ----
   ----
   _step_forward:

   This makes the floppy reader head move 1 position forward.
   As the function suggests, it makes the step-motor step forward.

   When executed, the reader head will go forward. If it is not able to go forward
   it will go back instead.

   This function does return a integer value of 1 if succeed to step forward, and 0 if it failed.

   Example:

   _step_forward();
   This will make the head go forward if it is able to, if not will go back instead.
   ----
   ----
   _step_back:

   This makes the floppy reader head move 1 position back.
   As the function suggests, it makes the step-motor step back.

   When executed, the reader head will go back. If it is not able to go back
   it will go forward instead.

   This function does return a integer value of 1 if succeed to step back, and 0 if it failed.

   Example:

   _step_back();
   This will make the head go back if it is able to, if not will go forward instead.

*/

#define steppin 12
#define dirpin 10


#define front LOW
#define back HIGH

int pos, dir = 0;

void _finitialize() {
  pinMode(steppin, OUTPUT);
  pinMode(dirpin, OUTPUT);
  digitalWrite(steppin, HIGH);
  digitalWrite(dirpin, back);
  delay(15);
  for (int i = 0; i <= 81; i++) {
    digitalWrite(steppin, LOW);
    delay(2);
    digitalWrite(steppin, HIGH);
    delay(2);
  }
  pos = 0;
  dir = 1;
  delay(250);
}

void _fstep_once() {
  if (dir == 0) {
    digitalWrite(dirpin, back);
    delayMicroseconds(500);
    digitalWrite(steppin, LOW);
    delayMicroseconds(750);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(750);
    pos--;
  }
  else {
    digitalWrite(dirpin, front);
    delayMicroseconds(500);
    digitalWrite(steppin, LOW);
    delayMicroseconds(750);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(750);
    pos++;
  }
  if ((pos == 80) or (pos == 0)) {
    dir = !dir;
  }
}

int _fstep_forward() {
  if (pos >= 80) {
    digitalWrite(dirpin, back);
    delayMicroseconds(500);
    digitalWrite(steppin, LOW);
    delayMicroseconds(750);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(750);
    pos--;
    return 0;
  }
  else {
    digitalWrite(dirpin, front);
    delayMicroseconds(500);
    digitalWrite(steppin, LOW);
    delayMicroseconds(750);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(750);
    pos++;
    return 1;
  }
  if ((pos == 80) or (pos == 0)) {
    dir = !dir;
  }
}

int _fstep_back() {
  if (pos > 0) {
    digitalWrite(dirpin, back);
    delayMicroseconds(500);
    digitalWrite(steppin, LOW);
    delayMicroseconds(750);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(750);
    pos--;
    return 1;
  }
  else {
    digitalWrite(dirpin, front);
    delayMicroseconds(500);
    digitalWrite(steppin, LOW);
    delayMicroseconds(750);
    digitalWrite(steppin, HIGH);
    delayMicroseconds(750);
    pos++;
    return 0;
  }
  if ((pos == 80) or (pos == 0)) {
    dir = !dir;
  }
}

void _fplay_hz(int freq, int duration) {
  float sleeptime;
  int cycles;
  sleeptime = ((1.0 / freq) * 1000);
  cycles = (duration / (sleeptime + 3));
  sleeptime = sleeptime * 1000;
  if ((duration > 0) and (freq >= 30) and (freq <= 500) and (cycles > 0)) {
    for (int c = 1; c <= cycles; c++) {
      _fstep_once();
      delayMicroseconds(sleeptime);
    }
  }
  else {
    delay(duration);
  }
}

void _fplay_note(int note, int duration) {
  int resfreq;
  resfreq = 29;
  switch (note) {
    case 0: resfreq = 16; break;
    case 1: resfreq = 17; break;
    case 2: resfreq = 18; break;
    case 3: resfreq = 19; break;
    case 4: resfreq = 20; break;
    case 5: resfreq = 21; break;
    case 6: resfreq = 23; break;
    case 7: resfreq = 24; break;
    case 8: resfreq = 25; break;
    case 9: resfreq = 27; break;
    case 10: resfreq = 29; break;
    case 11: resfreq = 30; break;
    case 12: resfreq = 32; break;
    case 13: resfreq = 34; break;
    case 14: resfreq = 36; break;
    case 15: resfreq = 38; break;
    case 16: resfreq = 41; break;
    case 17: resfreq = 43; break;
    case 18: resfreq = 46; break;
    case 19: resfreq = 49; break;
    case 20: resfreq = 52; break;
    case 21: resfreq = 55; break;
    case 22: resfreq = 58; break;
    case 23: resfreq = 62; break;
    case 24: resfreq = 65; break;
    case 25: resfreq = 69; break;
    case 26: resfreq = 73; break;
    case 27: resfreq = 78; break;
    case 28: resfreq = 82; break;
    case 29: resfreq = 87; break;
    case 30: resfreq = 93; break;
    case 31: resfreq = 98; break;
    case 32: resfreq = 104; break;
    case 33: resfreq = 110; break;
    case 34: resfreq = 117; break;
    case 35: resfreq = 123; break;
    case 36: resfreq = 131; break;
    case 37: resfreq = 138; break;
    case 38: resfreq = 146; break;
    case 39: resfreq = 155; break;
    case 40: resfreq = 164; break;
    case 41: resfreq = 174; break;
    case 42: resfreq = 185; break;
    case 43: resfreq = 196; break;
    case 44: resfreq = 207; break;
    case 45: resfreq = 220; break;
    case 46: resfreq = 233; break;
    case 47: resfreq = 246; break;
    case 48: resfreq = 261; break;
    case 49: resfreq = 277; break;
    case 50: resfreq = 293; break;
    case 51: resfreq = 311; break;
    case 52: resfreq = 329; break;
    case 53: resfreq = 349; break;
    case 54: resfreq = 370; break;
    case 55: resfreq = 392; break;
    case 56: resfreq = 415; break;
    case 57: resfreq = 440; break;
    case 58: resfreq = 466; break;
    case 59: resfreq = 494; break;
    case 60: resfreq = 523; break;
  }
  _fplay_hz(resfreq, duration);
}

// Library Functions ends here.
// Program starts just here.
//
// This program will play a sequence of notes from
// lowest to highest.


void setup() {
  _finitialize();
}

void loop() {
  for (int i = 11; i <= 59; i++) {
    _fplay_note(i, 250);
  }
}
