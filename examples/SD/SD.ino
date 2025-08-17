#include <SPI.h>
#include <SD.h>
#include <avr/io.h>

/*** SD Card ***/
#define SD_CS_PIN    PIN_PC3

// 電源電圧とSDの電源電圧をSDに書き出す
void writeVCCVoltageValueToSD(){
  digitalWrite(SD_CS_PIN, HIGH);  // CSを無効化
  digitalWrite(SD_CS_PIN, LOW);   // CSを有効化
  SPI.swap(SPI1_SWAP_DEFAULT);    // SPI IFをPort Cで行う。https://github.com/SpenceKonde/DxCore/tree/master/megaavr/libraries/SPI
  SPI.begin();
  SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("SD init failed!");
    return;
  } else Serial.println("SD init done.");
  delay(20);
  File myFile = SD.open("LOG.TXT", FILE_WRITE);
  if (myFile) {
    float vcc = readVcc(); // Vcc を取得
    Serial.print("VDD   : "); Serial.println(vcc, 3);
    myFile.print("VDD   : "); myFile.println(vcc, 3); // 小数点以下3桁表示

    vcc = readVcc2(); // Vcc2 を取得
    Serial.print("VDDIO2: "); Serial.println(vcc, 3);
    myFile.print("VDDIO2: "); myFile.println(vcc, 3); // 小数点以下3桁表示
  
    myFile.flush();
    myFile.close();
    Serial.println("done.");
  } else {
    Serial.println("error opening log.txt");
  }
  delay(200);
  digitalWrite(SD_CS_PIN, HIGH);  // CSを無効化
}

/*** ADC ***/
float readVcc2() {
  analogReference(INTERNAL1V024); // 参照電圧を 1.024V に設定
  // 最初の測定値を破棄（ウォームアップ）
  analogRead(ADC_VDDIO2DIV10);
  uint16_t adc_result = analogRead(ADC_VDDIO2DIV10); // VDDIO2 を 1/10 に分圧した電圧を測定
  // VDDIO2の電圧を計算（1.024V基準、測定値を10倍）
  float vcc = (1.024 * adc_result * 10) / 1023.0;
  return vcc;
}
float readVcc() {
  analogReference(INTERNAL1V024); // 参照電圧を 1.024V に設定
  // 最初の測定値を破棄（ウォームアップ）
  analogRead(ADC_VDDDIV10);
  uint16_t adc_result = analogRead(ADC_VDDDIV10); // Vcc を 1/10 に分圧した電圧を測定
  // Vcc を計算（1.024V基準、測定値を10倍）
  float vcc = (1.024 * adc_result * 10) / 1023.0;
  return vcc;
}


void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_PA7, OUTPUT);
  digitalWrite(PIN_PA7, HIGH);  // turn the LED on

  pinMode(SD_CS_PIN, OUTPUT);
  digitalWrite(SD_CS_PIN, HIGH); // Deactivate SS pin
  
  Serial.pins(0,1);//AVR64DB32 TX=0,RX=1
  Serial.begin(115200);
  while (!Serial);
  Serial.println("\nSTART!");
  
  //writeTimeAndVCCVoltageValueAndTHToSD();  //SDに書き出し
  writeVCCVoltageValueToSD();
  delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
