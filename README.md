# AVR128DB32 microcontroller board

This is an AVR128DB32 microcontroller board that can be programmed using Arduino IDE. It is equipped with a real-time clock circuit that can be turned on and off at will by programming, making it ideal for battery-powered applications that collect sensor information at set times.

Arduino IDEでプログラミングできるAVR128DB32マイコン基板です。プログラムで自分自身の電源を任意にOn/Off可能なリアルタイムクロック回路を備えています。決まった時刻毎にセンサー情報を収集するバッテリー駆動のアプリケーションなどに最適です。
![image](image/a01.JPG)  
![image](image/a02.JPG)  

## ピン配置
![image](image/AVR128DB32.png)  


## 特徴
- USB-Serial I/FでPCと繋いでArduino IDEでプログラミング可能です(ブートローダー書き込み済み)。<br>CIt can be connected to a PC via USB-Serial I/F and programmed using Arduino IDE (bootloader pre-installed).<br>
  <p float="left">
    <img src="image/t01_FTDI.png" height="200" /> &nbsp;&nbsp; <img src="image/t02_FTDI.png" height="200" />
  </p>
  初期状態はシリアルが選択されています。(左の図)　ブートローダーを使わないUPDI書き込みも選択可能です。(右の図)<br>The default setting is serial (left figure). UPDI writing without using the bootloader can also be selected (right figure).<br>
  <p float="left">
    <img src="image/t03_Serial.png" height="200" /> &nbsp;&nbsp;&nbsp;&nbsp; <img src="image/t04_UPDI.png" height="200" />
  </p>

  ボードマネージャは [DxCore](https://github.com/SpenceKonde/DxCore/blob/master/README.md) を使用。<br>Uses DxCore for board manager.<br>
  動作確認済みの設定<br>The following settings have been confirmed to work.<br>(no BOD, enable boot loader, select AVR128DB32, internal clock 24MHz, enable MVIO, Use float with printf, ...)：
  ![image](image/ArduinoSettings.png)

- リアルタイムクロック(RTC) [RX8035](https://akizukidenshi.com/goodsaffix/rx-8035_am.pdf)搭載。I2C I/Fでプログラム可能です。<br>Equipped with a real-time clock.Communication via I2C.<br>

  RTCのバックアップに超小型Li２次電池 [MS621](https://akizukidenshi.com/catalog/goods/search.aspx?search=x&keyword=ms621&search=search) を裏面に搭載可能です。電源が供給されている時に充電されます。<br>An ultra-small rechargeable Li battery can be installed on the back for RTC backup. It charges when power is supplied.

- マイクロSDカードコネクター搭載、電源はLDO [AP7333](https://akizukidenshi.com/goodsaffix/ap7333.pdf)で3.3Vを供給しています。<br>Equipped with a micro SD card connector, power is supplied at 3.3V by LDO.<br> I/Fは、Port Cを使ったSPIを使用しています<br>The I/F uses SPI via Port C.<br> AVR***DB32シリーズのPort Cにはレベルシフタが内蔵されており、VDDIO2に3.3Vを供給することで、3.3VのロジックレベルでのSPI通信が可能です。<br>The AVR***DB32 series' Port C has a built-in level shifter, enabling SPI communication at a logic level of 3.3V by supplying 3.3V to VDDIO2.
  https://github.com/SpenceKonde/DxCore/tree/master/megaavr/libraries/SPI
- AVRマイコンの電源をRTCからON/OFF制御可能です。ON/OFFはFETスイッチで行うので、OFFの時マイコンの消費電力は0です！<br>The AVR's power can be controlled ON/OFF from the RTC. Since ON/OFF is performed via an FET switch, the microcontroller's power consumption is 0 when OFF!

- 電源入力は３系統あります。全てダイオードORされています。マイクロSDカードを使うには3.3V以上の電源電圧が必要です。<br>There are three power input lines, all of which are diode OR-ed. To use a microSD card, a power supply voltage of 3.3V or higher is required.
  <p float="left">
    <img src="image/p05_power_supply_diagram.png" height="300" /> 
  </p>

  - J1（バッテリー入力）:<br> 電源電圧は2.6Vから5.5Vです。Liバッテリー×1セルで動作可能。J1からの電源はRTCでON/OFF制御可能です。また、POWERボタンを長押しすると電源をONするようにプログラム可能です。サンプルプログラムを参照してください。<br>The power supply voltage is 2.6V to 5.5V. Operates on a single Li battery cell. Power from J1 can be turned on and off via RTC. It can also be programmed to turn on when the POWER button is held down. Please refer to the sample program.<br>
    <p float="left">
      <img src="image/p01_J1.png" height="200" /> &nbsp;&nbsp;&nbsp;&nbsp; <img src="image/p02_J1.png" height="200" />
    </p>
    2.5Vから3Vの電源電圧でSDカードを使いたい場合は、裏面のJP5をカットし、[buck-boost_converter](https://akizukidenshi.com/catalog/g/g116055/) を裏面に実装すれば可能です。<br>If you want to use an SD card by a power supply voltage lower than 3.3V, cut JP5 on the back and attach a buck-boost converter to the back.

  - シリアル（Serial）:<br> 電源電圧は2.6Vから5.5Vです。マイコンに接続されています。<br>The power supply voltage is 2.6V to 5.5V. It is connected to a AVR.<br>
    <p float="left">
      <img src="image/p04_Serial.png" height="300" />
    </p>

  - VIN:<br> 電源電圧は2.6Vから5.5Vです。初期状態ではU5の1ピンと2ピンにR14が実装されています。これを外してSOT23タイプのLDO [AP7375](https://akizukidenshi.com/goodsaffix/ap7375.pdf)を実装することで、クルマの12Vバッテリーなどの電圧（Max 45V）も使用可能になります（ただし消費電力に注意）。<br>The power supply voltage is 2.6V to 5.5V. In the initial state, R14 is mounted on pins 1 and 2 of U5. If you want to use a voltage of 12V or higher, such as a car battery (max. 45V), you can do so by removing R14 and mounting an SOT23 type LDO (however, be aware of power consumption).<br>
    <p float="left">
      <img src="image/p03_VIN.png" height="200" />
    </p>

- ボードサイズ 95mm x 18.2mm、付属のピンヘッダをハンダ付けすればブレッドボードで使用できるスリム設計です。<br>The board size is 95 mm x 18.2 mm, and it has a slim design that can be used with a breadboard by soldering the included pin header.<br>ピンヘッダをボードの おもて面に実装し、裏返して使用することも可能。この場合、リセットボタンとPOWERボタン、それからLEDも裏面実装可能です。どちらのボード面にもピン情報がシルク印刷してあります。<br>The pin header can be mounted on the front of the board, and it can also be used upside down. In this case, the reset button, POWER button, and LED can also be mounted on the back. Pin information is silk-screened on both sides of the board.

## Specifications
- プログラムメモリは128KB、RAMは16KB、内蔵のクロックは24MHzです。
- 12ビットのADC、10ビットのDAC、OPアンプ、ロジック回路を装備しています。
- 詳細は [Datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/AVR128DB28-32-48-64-DataSheet-DS40002247A.pdf) 参照。

## Here's how you can use it!
![image](image/a03.JPG) 

## schematics
* [schematics](schematics/AVRT_2.pdf)



