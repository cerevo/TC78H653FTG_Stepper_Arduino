# TC78H653FTG Stepper Motor Driver
This is a tiny Arduino stepper motor library (or, rather just a sample code) for the cheap [TC78H653FTG H-bridge](https://akizukidenshi.com/catalog/g/gK-14746/).

Currently this library is under development.

Please be aware that this library and the H-bridge won't be the direct replacement of the dedicated stepper drivers like Allegro A4988. Yet one big advantage of this library is you can drive the stepper motor much slinetly. Also the TC78H653FTG is cheaper than dedicated stepper driver.

このライブラリは格安の[TC78H653FTG H-bridge](https://akizukidenshi.com/catalog/g/gK-14746/)を使ったステッピングモータ用のArduinoライブラリです。
[日本語の情報はCerevoのブログで公開しています。よろしければご覧ください。](https://tech-blog.cerevo.com/)

## What can this library do? / このライブラリで出来ること
- You can drive a bipolar stepper motor with rate up to 7.5V, 2A. / 7.5V, 2Aまでのバイポーラタイプのステッピングモータを駆動することができます。
- Able to drive stepper very silently in **forward direction**. / ステッピングモータを**前方向に**とても静かに駆動することができます。
- Customize motor's excitation current profile. / モータに流す励磁電流プロファイルをカスタマイズできます。

## What this library cannot do? / このライブラリで出来ないこと
- Current control is not possible. / 電流制御は出来ません。
- Unable to use stepper above H-Bridge's rating 7.5V. / Hブリッジの定格7.5V以上でモータを駆動することは出来ません。
- Currently specialized for micro stepping. Driving in high speed is not very suitable. / 現在マイクロステッピングのみに特化しています。高速駆動にはあまり適していません。


## TODO
- Implement reverse direction with silent stepping pattern. / 逆転方向への静かなステッピングパターン実装
- Implement speed control mode. / 速度制御モード実装
- Write example codes for some MCUs. Currently only Arduino UNO example is available. / 他のMCU用サンプルコード作成。現在ArduinoUno用のサンプルコードのみあります。
- Convert the library in Arduino-Style library format, so you can load to ArduinoIDE. / ライブラリをArduinoスタイルのライブラリフォーマットへ変更しArduinoIDEからロード出来るようにする。

## License
BSD-3-clause