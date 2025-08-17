#include <Wire.h>

char DisplayData[]="n.k products";

/*** RX8035 ***/
#define RX8035_SLAVE_ADRS 0x32
//bool TimerEnable = false;
uint8_t date_time[8]={
  0x00,     // Seconds
  0x12,     // Minutes
  0x22+0x80,// Hours (MSB=1:24h,0:12h)
  0x00,     // Week
  0x16,     // Day
  0x03,     // Months
  0x25,     // Years
  0         // dummy
  };
void writeCommandToRTC(uint8_t reg1, uint8_t dat1){
  Wire.beginTransmission(RX8035_SLAVE_ADRS);
  Wire.write(reg1);
  Wire.write(dat1);
  Wire.endTransmission();
  delay(1);
}
uint8_t readRegDataFromRTC(uint8_t reg1){
  Wire.beginTransmission(RX8035_SLAVE_ADRS);
  Wire.write(reg1);
  Wire.endTransmission(false);  // false = No stop sequence
  Wire.requestFrom(RX8035_SLAVE_ADRS, 1);
  while( Wire.available() ){
    return( Wire.read() );
  }
  return 0xff;
}
//初期化
void initRTC(){
  writeCommandToRTC(0xe0,0b00010101);  //bit4(EDEN) 1の時電源ボタン2秒押し有効, bit0:2(定期的P-On) 5のとき1分毎(00秒)にOn、6のとき1時間毎(00分にOn
  writeCommandToRTC(0xf0,0);  // bit2(CTFG) 0を書き込むとINTRB端子は開放 = Power-Off
}
//時刻を設定
void writeDateTimeToRTC(){
  for (uint8_t i = 0; i<7; i++){
    writeCommandToRTC( (i)<<4, date_time[i] );  //例：レジスタテーブル6 = 0x60
  }
}
//日付時刻を読み出す
void readDateTimeFromRTC(){
  Wire.beginTransmission(RX8035_SLAVE_ADRS);
  Wire.write(0);
  Wire.endTransmission(false);  // false = No stop sequence
  Wire.requestFrom(RX8035_SLAVE_ADRS, 7);
  uint8_t i=0;
  while( Wire.available() ){
    date_time[i]= Wire.read();
    i++;
  }
}
//Time-stampの日付時刻を読み出す
void readTimeStampFromRTC(){
  writeCommandToRTC(0xf0,0b11111111); // select BANK1
  readDateTimeFromRTC();
  writeCommandToRTC(0xf0,0b01111111); // select BANK0
}

void setup() {
  // put your setup code here, to run once:
  /* initialize digital pin LED_BUILTIN as an output.*/
  pinMode(7, OUTPUT);     // LED pin7 (=PIN_PA7)
  digitalWrite(7, HIGH);  // turn the LED on

  Wire.begin();
  Wire.setClock(400000);

  Serial.pins(0,1);//AVR64DB32 TX=0,RX=1
  Serial.begin(115200);
  while (!Serial);

  /* 初回のみ時刻設定 */
  //initRTC();
  //writeDateTimeToRTC();
  Serial.println(DisplayData);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(7, LOW);  // turn the LED off

  readDateTimeFromRTC();
  sprintf(DisplayData, "20%02x %02x/%02x ", date_time[6],date_time[5],date_time[4]);
  Serial.print(DisplayData);

  sprintf(DisplayData, "%02x:%02x", date_time[2]&0x7f, date_time[1]);
  Serial.println(DisplayData);
  delay(900);
  digitalWrite(7, HIGH);  // turn the LED on
  delay(100);

  initRTC();  // If this system is battery powered, it will be turned off.
}
