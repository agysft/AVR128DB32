# AVR128DB32 microcontroller board

This is an AVR128DB32 microcontroller board that can be programmed using Arduino IDE. It is equipped with a real-time clock circuit that can be turned on and off at will by programming, making it ideal for battery-powered applications that collect sensor information at set times.

Arduino IDEでプログラミングできるAVR128DB32マイコン基板です。プログラムで自分自身の電源を任意にOn/Off可能なリアルタイムクロック回路を備えており、決まった時刻毎にセンサー情報を収集するバッテリー駆動のアプリケーションなどに最適です。
![image](image/a01.JPG)  
![image](image/a02.JPG)  

ピン配置：
![image](image/AVR128DB32.png)  
---
ボードマネージャはDxCoreを使用：
![image](image/ArduinoSettings.png)

---

特徴
- Arduino IDEでプログラミング可能。Arduino PRO Miniの様にUSB-Serial I/FでPCと繋いでプログラミング可能です(ブートローダー書き込み済み)。

  <img src="image/t01_FTDI.png" height="200"><img src="image/t02_FTDI.png" height="200">
  初期状態はシリアルが選択されていますが、ブートローダーを使わないUPDI書き込みも選択可能です。
  <img src="image/t03_Serial.png" height="200"><img src="image/t04_UPDI.png" height="200">
- リアルタイムクロック(RTC)RX8035搭載。I2Cでプログラム可能です。
  https://akizukidenshi.com/goodsaffix/rx-8035_am.pdf

  RTCのバックアップに超小型Li２次電池MS621を搭載可能。電源が供給されている時に充電されます。
  https://akizukidenshi.com/catalog/g/g117518/
- マイコンの電源をRTCからON/OFF制御可能。ON/OFFはFET-SWで行うので、OFFの時、マイコンの消費電力は0です！
- ３系統の電源入力があります。
  J1からの電源電圧は2.6Vから5.5Vの範囲で可能です。Liバッテリー×1セルで動作可能。J1からの電源はRTCでON/OFF制御可能です。
  <img src="image/p01_J1.png" height="200"><img src="image/p02_J1.png" height="200">

  Serial(J2)からの電源電圧は2.6Vから5.5Vの範囲で可能です。マイコンに直結されています。

  VINからの電源電圧はSerialと同じです。U5にSOT23タイプのLDO、AP7375を追加すればクルマの12Vバッテリーでの動作など(Max 45V)も可能です（消費電力注意）。
  <img src="image/p03_VIN.png" height="200">
- マイクロSDカードコネクター搭載（マイクロSDカードを使うには3.3V以上の電源電圧が必要です）。マイクロSDカードI/Fは、Port Cを使ったSPI通信を使用しています（ SPI.swap(SPI1_SWAP_DEFAULT); を設定）。AVR***DB32シリーズのPort Cにはレベルシフタが内蔵されており、VDDIO2にはLDO AP7333で3.3Vを供給しているのでSDカード用3.3VのロジックレベルでのSPI通信ができます。
  https://github.com/SpenceKonde/DxCore/tree/master/megaavr/libraries/SPI
- ボードサイズ 95mm x 18.2mm、付属のピンヘッダをハンダ付けすればブレッドボードで使用できるスリム設計です。

スペック
- プログラムメモリは128KB、RAMは16KB、内蔵のクロックは24MHzです。
- 12ビットのADC、10ビットのDAC、OPアンプ、ロジック回路を装備しています。

使用例：
![image](image/a03.JPG) 
---
回路図：
* [schematics](schematics/AVRT_2.pdf)


---
