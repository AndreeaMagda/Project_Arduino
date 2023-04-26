
unsigned char numbers[4] = { 0x92, 0x88, 0xC7, 0xC7 };  //fOr display
unsigned char digits[4] = { 0x01, 0x02, 0x04, 0x08 };   //for display
unsigned char first_state[] = { 0xDF, 0xCF, 0xEF, 0XE7, 0xF7, 0XF3, 0xFB, 0XDB };  //for motor
unsigned char i = 0;

void setup() {
  DDRB = 0x01;
  DDRD = 0x90;
}

void setupMotor() {
  noInterrupts();
  DDRB = 0X3C;
  DDRC = 0x00;
  DDRD=0X00;
  TCCR1A = 0X00;
  TCCR1B = 0X1D;
  TIMSK1 |= (1 << OCIE1A);
  OCR1A = (16000000 / 1024) * 1;
  TCNT1 = 0X00;
  interrupts();
}

void displaySegments() {
  Display(digits[0], numbers[0]);
  Display(digits[1], numbers[1]);
  Display(digits[2], numbers[2]);
  Display(digits[3], numbers[3]);
}

ISR(TIMER1_COMPA_vect) {

  TCNT1 = 0;
  PORTB = first_state[i];{
  i++;
  if (i == 8) {
    i = 0;
  }
  }
}

ISR(PCINT8_vect){}


void SetLatch() {
  PORTD = PORTD | 0x10;
}
void ResetLatch() {
  PORTD = PORTD & 0xEF;
}

void SetCLK() {
  PORTD = PORTD | 0x80;
}
void ResetCLK() {
  PORTD = PORTD & 0x7F;
}


void Display(unsigned char digit, unsigned char number) {
  ResetLatch();
  ResetCLK();
  PORTB = 0x00;
  for (int i = 7; i >= 0; i--) {
    ResetCLK();
    PORTB = number >> i;
    SetCLK();
  }
  for (int j = 7; j >= 0; j--) {
    ResetCLK();
    PORTB = digit >> j;
    SetCLK();
  }

  PORTB = 0x00;
  SetLatch();
}



int main() {
  PORTB = 0Xff;
  PORTC = 0x02;

 

  while (1) {
     if ((PINC & 0x02) == 0x02) {
    
   setupMotor();
   }else {
    setup();
    displaySegments();
  }
  }
}