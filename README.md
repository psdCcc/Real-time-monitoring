<div align=center>
<img src="https://user-images.githubusercontent.com/48510316/164079523-7f6552f5-77a8-4690-a945-5483983474c3.png" width="180" height="180"/>
</div>

<h1 align="center">A Real-time Indoor Monitoring System</h1>

<div align=center>
  
[![github](https://img.shields.io/badge/Contributors-3-orange)](https://github.com/psdCcc/Real-time-monitoring/graphs/contributors)   [![github](https://img.shields.io/badge/License-MIT-red)](https://github.com/psdCcc/Real-time-monitoring/blob/add-license-1/LICENSE)  [![github](https://img.shields.io/badge/issues-0%20open-blue)](https://github.com/psdCcc/Real-time-monitoring/issues)
  
 </div>



---
# Table of Contents
- [Background](#background)
- [Hardware](#hardware)
- [Software](#software)
- [Installation](#installation)
- [Contributors](#contributors)
- [Links](https://github.com/psdCcc/Real-time-monitoring/edit/main/README.md#links)

---
# Background
For various reasons, such as work, school, or travel, sometimes we leave the house for long periods of time, leaving no one at home. Spending time outside can be a joy, however, an empty house can have many safety hazards, such as heat  from forgetting to turn off the stove, or an unexpected open fire. According to statistics, the initial stage of a fire is the golden period for extinguishing the fire, but if the owner is not at home, the possibility of extinguishing the initial fire is almost zero, and the disaster can only be allowed to intensify. We want to do something to mitigate the damage caused by this disaster, such as enabling homeowners to detect abnormalities in their homes as soon as possible. 

Moreover, in addition to this disaster, the danger from intruders cannot be ignored. According to a report, the total reported burglaries in London was 55,252 in 2021, which is a scary number. Even more frightening, more than 75 % of Metropolitan police burglary investigations failed to identify a suspect. Therefore, we are also thinking of an indoor surveillance system that can alert homeowners of burglaries in real time and help police track them down.
Even without these accidents, being able to take control of our home remotely makes us feel more secure and more focused on what's important in the moment.

Based on these situations, we designed a real-time indoor monitoring system based on Raspberry Pi. In this system, homeowners will be able to remotely use mobile applications or web pages to monitor the indoor status in real time, including but not limited to indoor images, temperature and humidity. In addition, the system will also provide a line graph about these quantities to show the trend of these characteristics in the past period of time, so that users will be able to judge for themselves whether the current state of the house is normal. In addition, the system will also come with a set of algorithms to determine whether the house is in a dangerous state through the comparison of these received values with normal values and real-time processing of the camera's picture, such as the fire hazard that may be caused by excessive smoke concentration, as well as the property and personal safety hazards brought by intruders.

Our system consists of hardware part and software part. The hardware part consists of a Raspberry Pi and some simple sensors and camera. The software part consists of server, website, and mobile application, which contains a set of our original control logic, including data acquisition, data processing, data analysis, image analysis and real-time feedback (such as issuing warnings).

We hope that this system can go beyond the definition of a coursework and can actually help more homeowners to add a layer of monitoring to their homes, making them more secure and avoiding possible disasters and theft.

![image](https://user-images.githubusercontent.com/48510316/159191576-ef766f4d-4469-4849-9271-77aa3e35234c.png)

# Hardware
- Raspberry pie 4B (2GB) 

- DHT11 module: measure the temperature and humidity.

- Camera: Create a real-time video stream server.


![D72CC1486AAC4D9514F434E370CF5000](https://user-images.githubusercontent.com/48510316/164082296-1239be40-647e-42ce-bf24-f96e4e24a474.jpg)



# Software

- C++ for the embedded part.

- Node.js for the server (Back-ended) part

- HTML+CSS+JavaScript for the webpage(Front-ended) part

- echarts (a open-source library https://echarts.apache.org/zh/index.html) for drawing the Real-time graph

- Android Studio (Java) for the android part

- CMake for installation











# Installation
## 1. Download the project from github

`$ git clone https://github.com/psdCcc/Real-time-monitoring.git` 

## 2. Compile it
change directory

`$ cd Source/Embedded_part` 

compile

`$ cmake . `

`$ make  `







# Contributors

ENG5220, University of Glasgow, Team 28

- Bingchu Cui ([@psdCcc](https://github.com/psdCcc))

- Yizhi   Lu([@Gavin1999](https://github.com/Gavin1999))

- Zhiyuan Chen([@MDJue](https://github.com/MDJue))







# Links

- ![image](https://user-images.githubusercontent.com/48510316/164111440-f9279d8b-a951-4dd6-98ac-7bb2160d4030.png)
Youtube video: https://www.youtube.com/watch?v=6bfweTa4KWA

- ![image](https://user-images.githubusercontent.com/48510316/164113953-6edeadae-adc1-4432-80b5-c3523852cb4f.png)
TikTok video: https://www.tiktok.com/@zyuanchen/video/7088450183805127942?is_copy_url=1&is_from_webapp=v1&lang=zh-Hant-TW 

- [Sensor Sequence Diagram](https://github.com/psdCcc/Real-time-monitoring/tree/main/Source/Embedded-part/DHT11)

- [Android part functions](https://github.com/psdCcc/Real-time-monitoring/tree/main/Source/Android-part)


