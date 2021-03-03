# Esp8266_Homekit_Template
Template of Homekit for the Esp8266 based on Arduino

基于Esp8266的Homekit固件编写方法

[TOC]



## 0x0 快速入门

以点亮一个LED灯为例的完全新手的简易使用方法：

### 一、环境搭建

1.前往[Arduino官网](https://www.arduino.cc)下载对应自己系统班的[Arduino IDE](https://www.arduino.cc/en/software)（Windows用户可以前往[应用商店](https://www.microsoft.com/zh-cn/p/arduino-ide/9nblggh4rsd8)下载）并安装。

2.打开Arduino，Windows用户点击“文件”>“首选项”，Mac用户点击左上角“Arduino”>“Preference”。

<img src="https://raw.githubusercontent.com/ColdeZhang/PicGo/master/image-20210303171759207.png?token=AHDJQ6B6ML22YUNGVV3KTSLAH5KIM" alt="image-20210303171759207" style="zoom:50%;" />

3.在“附加开发版管理器网址”一栏填上：

> https://arduino.esp8266.com/stable/package_esp8266com_index.json

<img src="https://raw.githubusercontent.com/ColdeZhang/PicGo/master/image-20210303171849958.png?token=AHDJQ6H6SB7RC6S64ODGIQ3AH5KLS" alt="image-20210303171849958" style="zoom:33%;" />

4.关闭窗口，打开“工具”>“开发版”>“开发版管理器”

![image-20210303172359306](https://raw.githubusercontent.com/ColdeZhang/PicGo/master/image-20210303172359306.png?token=AHDJQ6ARXUN6ORUZVMZZKHDAH5K7A)

### 二、硬件链接



### 三、代码修改



### 四、上传验证

1.确定你所需要的智能配件功能
2.前往 https://github.com/ColdeZhang/Esp8266_Homekit_Template/blob/main/HAP-Specification-Non-Commercial-Version.pdf 在p134查找对应的服务（service）
3.根据文档中服务（service）对变量（characteristic）的要求，创建变量（characteristic）



## 0x1 进一步学习

### 一、名词定义

#### 1.配件（Accessories）

官方文档（2.3.1）解释：

> Accessories are comprised of services and characteristics. An example of an accessory is a ceiling fan with a light and a mister that sprays cool water.

并非是指硬件，而是一个概念（一个配件在HomeApp上就是一个开关之类的）。所以可以在同一个硬件上可以配置多个配件（比方带有温度检测功能的电风扇），但是除非有特殊需求（比方带有温度检测功能的电风扇），否则一般情况下不建议将许多配件揉杂在一个硬件上。

#### 2.服务（Services）

官方文档（2.3.2）解释：

> Services group functionality in order to provide context. In the aforementioned example accessory there are three services: a fan service to interact with the ceiling fan, a light service to interact with the light, and a mister service to interact with the spray mister.

服务定义了一个配件的实际功能，比方同样是属于开关（Switch）类别（Category）的配件，除了具有开关的基本（必须）功能，对于电风扇而言他可以具有调速的功能，对于电灯而言他可以有调整亮度或者颜色的功能。

#### 3.特征（Characteristics）

官方文档（2.3.3）解释：

> A characteristic is a feature that represents data or an associated behavior of a service. The characteristic is defined by a universally unique type, and has additional properties that determine how the value of the characteristic can be accessed.

特征在固件中也可以看作是变量，不同的服务要求有不同类型的特征（变量）。



### 二、定义一个完整的配件

一个完整的配件（Accessory）由若干个服务（Service）组成，其中必须包含一个“配件信息服务”（ACCESSORY_INFORMATION）与一个主服务（Primary Service），而主服务包含了若干的特征（Characteristic），并且分为必须（required）与可选（optional）。



### 三、程序结构

完整的固件程序由三个文件构成：

#### 1.template.ino

该文件为主程序，用于发送接收处理数据、操作IO口等等。

#### 2.my_accessory.c

该文件用于定义配件的属性。

#### 3.wifi_info.h

该文件专用于保存与处理wifi连接方法。





