# TC78H653FTG Stepper Motor Driver
This is small Arduino stepper motor library for the cheap [TC78H653FTG H-bridge](https://akizukidenshi.com/catalog/g/gK-14746/).
Currently this library is under development.
Please be aware that this library and the H-bridge won't be the direct replacement of the dedicated stepper drivers like Allegro A4988. Yet one big advantage of this library is you can drive the stepper motor much slinetly. Also the TC78H653FTG is much cheaper than dedicated stepper driver.
[日本語の情報はCerevoのブログで公開しています。よろしければご覧ください。](https://tech-blog.cerevo.com/)

## What can this library do?
- You can drive a bipolar stepper motor with rate up to 7.5V, 2A.
- Able to drive stepper very silently in **forward direction**.
- Customize motor excitation profile.

## What this library cannot do?
- Current control is not possible.
- Unable to use stepper above 12V.
- Currently specialized for micro stepping. Driving in high speed is not very suitable.

## TODO
- Implement reverse direction with silent stepping pattern.
- Implement speed control mode.
- Write example codes for some MCUs. Currently only Arduino UNO example is available.
- Convert the library in Arduino-Style library format, so you can load to ArduinoIDE.

## License
BSD-3-clause