![banner](files/hexapod_og.jpg)

# hexapod-v2-7697

> 中文版本請看 [這裡](README_tw.md)

Hexapod v2 using Linkit 7697

This is a Hexapod project.

You can use any mobile phone (iOS or Android) to control the movement of hexapod (move foreward, backward, etc...).

See demo video: https://youtu.be/NJ7DdDEcq3U & https://youtu.be/To2Y6Mhu-CE to get the idea.

<a href='https://youtu.be/NJ7DdDEcq3U'><img src='http://img.youtube.com/vi/NJ7DdDEcq3U/mqdefault.jpg'/></a>
<a href='https://youtu.be/To2Y6Mhu-CE'><img src='http://img.youtube.com/vi/To2Y6Mhu-CE/mqdefault.jpg'/></a>

> More videos can be found at https://smallptsai.github.io/hexapod-web/

## Brief introduction

* **Remote control** is done via `BLE` of `Linkit 7697`
* It has 6 legs, each leg has 3 joint. So there are total `18` **Servo motors** (TowerPro `MG92B`)
* Linkt 7697 dont have so many **PWM control**, so NXP `PCA9685` x 2 are used to control these servo motors
* **Power** comes from a `2S Lipo battery (7.4v)`. Also 7 x `mini360 DC-DC` step down voltage regulator are used. One to provide `5V` to Linkit 7697, The other six to provide `6V` to each legs (1 mini360 serve 3 servo)
* The **body** is 3D printed PLA. I use `Prusa i3 MK2S`, a really good 3D printer.
* Everything (3D STL, PCB schematic, 7697 source code) are included in the project under **GPL license**, Happy making!

## Skill requirement

If you want to make one hexapod by yourself. You should at least knows how to:

* Mechanism part
    * Use `3D printer` to print a model.
    * Able to adjust 3D model to fit your custom need.
* Electronics
    * Make a `PCB` (suggest to use professional PCB services)
    * Soldering `SMD` component (0805 and TSSOP28)
    * How to use/charge/store `LIPO batteries`
* Software
    * Use `Linkit 7697` (ie. upload and run any program)
    * Use `LRemote` to communicate 7697 and your mobile phone

## Table of Content

1. [Mechanism](mechanism/) - How to build the body
1. [Electronics](electronics/) - Circuit explanition
1. [Software](software/) - The software running on Linkit 7697

