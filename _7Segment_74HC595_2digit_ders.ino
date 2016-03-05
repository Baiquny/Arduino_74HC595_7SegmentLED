#define LATCH 2 //STCP
#define DATA 3 //DS
#define CLK 4 //SHCP
#define MR 5 //MR
#define NOKTA 128
#define HARF_A 119
#define HARF_L 56

byte cc_rakamlar[10] = {
        63, //0  (0b00111111)
        6, //1   (0b00000110)
        91, //2  (0b01011011)
        79, //3  (0b01001111)
        102, //4 (0b01100110)
        109, //5 (0b01101101)
        125, //6 (0b01111101)
        7, //7   (0b00000111)
        127, //8 (0b01111111)
        111 //9  (0b01101111)
      }; 

void setup(){
  pinMode(LATCH, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(MR, OUTPUT);
  digitalWrite(MR, LOW);
  digitalWrite(MR, HIGH);
  
  //yaz(45);
  //yazFloat(5.4);
}

void loop(){
  for (float i = 0.0; i <= 4.9; i += 0.1) {
    yazFloat(i);
    delay(150);
  }
}

void yaz_harf() {
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLK, MSBFIRST, HARF_A);
  shiftOut(DATA, CLK, MSBFIRST, HARF_L);
  digitalWrite(LATCH, HIGH);
}

void yaz(int deger) {
  digitalWrite(LATCH, LOW);
  byte onlar = deger / 10;  // deger = 54 ise 54 / 10 = 5 (yani onluk değer 5)
  byte birler = deger % 10; // deger = 54 ise 54 % 10 = 4 (yani birler değer 4)
  shiftOut(DATA, CLK, MSBFIRST, cc_rakamlar[onlar]);
  shiftOut(DATA, CLK, MSBFIRST, cc_rakamlar[birler]);
  digitalWrite(LATCH, HIGH);
}

void yazFloat(float deger) { //deger = 5.4 ch_deger = 5.4
  int poz = -1;
  char ch_deger[10] = {}; 
  String ilk_st, son_st = "";
  
  dtostrf(deger, 2, 1, ch_deger);  //2 haneli bir sayi, 1 ise ondalik miktari
  for (int i = 0; i < sizeof(ch_deger); i++) //5.4 . nın indexi : 1
  {
    if (ch_deger[i] == '.') poz = i;
  }

  for (int i = 0; i < poz; i++) {
    ilk_st += ch_deger[i];
  }

  for (int i = poz + 1; i < sizeof(ch_deger); i++) {
    son_st += ch_deger[i];
  }
  //Serial.print("ilk_st: "); Serial.println(ilk_st);
  //Serial.print("son_st: "); Serial.println(son_st);
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLK, MSBFIRST, cc_rakamlar[ilk_st.toInt()] | NOKTA); //  onlar (once MSBFIRST Arduino'ya en uzak olan registera deger aktariliyor)
  shiftOut(DATA, CLK, MSBFIRST, cc_rakamlar[son_st.toInt()]); //  birler
  digitalWrite(LATCH, HIGH);
}

