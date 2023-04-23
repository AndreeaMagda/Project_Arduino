void setup() {
  DDRB=0x01;
  DDRD=0x90; 
}
unsigned char numbers[4] = {0x92,0x88,0xC7,0xC7};
unsigned char digits[4] = {0x01, 0x02, 0x04, 0x08};

void SetLatch()
{
  PORTD=PORTD | 0x10;
}
void ResetLatch()
{
  PORTD=PORTD & 0xEF;
}

void SetCLK()
{
  PORTD=PORTD | 0x80;
}
void ResetCLK()
{
  PORTD=PORTD & 0x7F;
}


void Display(unsigned char digit,unsigned char number)
{
  ResetLatch();
  ResetCLK();
  PORTB=0x00;
  for(int i=7;i>=0;i--)
  {
    ResetCLK();
    PORTB=number>>i;
    SetCLK();
  }
  for(int j=7;j>=0;j--)
  {
    ResetCLK();
    PORTB=digit>>j;
    SetCLK();
  }
  
  PORTB=0x00;
  SetLatch();

}

int main() {
  setup();
  while(1){
   
    Display(digits[0],numbers[0]); 
    Display(digits[1],numbers[1]); 
    Display(digits[2],numbers[2]); 
    Display(digits[3],numbers[3]);


  }
  }