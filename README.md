## **写在前面** 

为了更加有效且有趣地Code，本工程代码版本控制使用 [Gitmoji](<https://github.com/carloscuesta/gitmoji>) 作为提交信息的前缀，感兴趣的小伙伴们可以了解一下。



## 简介

本仓库主要用于快速搭建基于STM32为主控的控制系统，根据项目需要选择工程文件即可，配置下载设置后即可搭配相应的下载器进行测试。（本项目基于STM32**标准库**搭建，需要使用**HAL库**请移步https://github.com/peidzzz/STM32HALTemplate）



## 项目内容

本项目主要包括：

| MCU内核版本 | MCU闪存容量 | MCU型号     | 目前是否支持 |
| ----------- | ----------- | ----------- | ------------ |
| Cortex-M3   | 64KB        | STM32F103x8 | 否           |
| Cortex-M3   | 128KB       | STM32F103xB | 否           |
| Cortex-M3   | 256KB       | STM32F103xC | 是           |





目前驱动移植情况：

- [x] LED
- [x] FLASH
- [x] CAN
- [x] KEY

- [x] LCD

  