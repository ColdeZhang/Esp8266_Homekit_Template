# Esp8266_Homekit_Template
Template of Homekit for the Esp8266 based on Arduino

基于Esp8266的Homekit固件编写方法

[TOC]



## 0x0 快速入门

以点亮一个LED灯为例的完全新手的简易使用方法：

### 一、环境搭建

1.前往[Arduino官网](https://www.arduino.cc)下载对应自己系统班的[Arduino IDE](https://www.arduino.cc/en/software)（Windows用户可以前往[应用商店](https://www.microsoft.com/zh-cn/p/arduino-ide/9nblggh4rsd8)下载）并安装。

2.打开Arduino，Windows用户点击“文件”>“首选项”，Mac用户点击左上角“Arduino”>“Preference”。

<img src="https://raw.githubusercontent.com/ColdeZhang/PicGo/master/image-20210303171759207.png?token=AHDJQ6B6ML22YUNGVV3KTSLAH5KIM" alt="image-20210303171759207" style="zoom: 50%;" />

3.在“附加开发板管理器网址”一栏填上：

> https://arduino.esp8266.com/stable/package_esp8266com_index.json

<img src="https://raw.githubusercontent.com/ColdeZhang/PicGo/master/image-20210303171849958.png?token=AHDJQ6H6SB7RC6S64ODGIQ3AH5KLS" alt="image-20210303171849958" style="zoom:33%;" />

4.关闭窗口，打开“工具”>“开发版”>“开发版管理器”

![image-20210303172359306](https://raw.githubusercontent.com/ColdeZhang/PicGo/master/image-20210303172359306.png?token=AHDJQ6ARXUN6ORUZVMZZKHDAH5K7A)

5.搜索“esp8266”并安装

<img src="https://raw.githubusercontent.com/ColdeZhang/PicGo/master/image-20210303174754999.png" alt="image-20210303174754999" style="zoom:50%;" />

6.关闭窗口，打开“工具”>“管理库...”

<img src="https://raw.githubusercontent.com/ColdeZhang/PicGo/master/image-20210303174922691.png" alt="image-20210303174922691" style="zoom:33%;" />

7.搜索“homekit”，安装“HomeKit-ESP8266”

<img src="https://raw.githubusercontent.com/ColdeZhang/PicGo/master/image-20210303175023078.png" alt="image-20210303175023078" style="zoom:50%;" />



### 二、硬件链接

将LED的正极（长的那端）连接在Esp8266开发板的IO0口上，负极（短的那端）连接在GND上。

### 三、代码修改

下载Template内的代码，一共有三个文件。使用Arduino打开Template.ino，另外两个文件会自动被打开。

#### 1.my_accessory.c

##### （1）创建变量

找到以下三行：

```c
homrkit_characteristic_t /*变量A*/ = HOMEKIT_CHARACTERISTIC_(/*变量类型X*/,/*变量初始值*/);
homrkit_characteristic_t /*变量B*/ = HOMEKIT_CHARACTERISTIC_(/*变量类型Y*/,/*变量初始值*/);
homrkit_characteristic_t /*变量C*/ = HOMEKIT_CHARACTERISTIC_(/*变量类型Z*/,/*变量初始值*/);
```

删去其中两行，仅保留一行并修改为如下代码：

```c
homrkit_characteristic_t cha_on = HOMEKIT_CHARACTERISTIC_(ON, false);
```

##### （2）配置信息

找到以下代码：

```c
/*
 * 定义配件们的属性
 * 存储在accessories[]中
*/
homekit_accessory_t *accessories[] = {
    /*
     * 定义第一个配件的属性
     * ｜编号｜从1开始，每个配件需要一个单独的编号
     * 如：1
     * ｜种类｜即配件所属的类别可在如下链接的文件中查看（p252）
     * https://github.com/ColdeZhang/Esp8266_Homekit_Template/blob/main/HAP-Specification-Non-Commercial-Version.pdf
     * 如：homekit_accessory_category_switch
     * 
     * 注意：种类需要使用大写字母，空格使用下划线（_）代替
    */
    HOMEKIT_ACCESSORY(.id=/*编号*/, .category=homekit_accessory_category_/*种类*/, .services=(homekit_service_t*[]) {
        /*
         * 配件基本信息定义
         * 从上到下依次为：
         * ｜配件名称｜引号内可以随便写，但是同一个局域网内不能出现同样名字的配件
         * ｜制造商名｜引号内可以随便写
         * ｜序列号码｜引号内可以随便写
         * ｜硬件型号｜引号内可以随便写
         * ｜固件版本｜引号内可以随便写
        */
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "未命名配件"),
            HOMEKIT_CHARACTERISTIC(MANUFACTURER, "Arduino HomeKit"),
            HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, "0123456"),
            HOMEKIT_CHARACTERISTIC(MODEL, "ESP8266/ESP32"),
            HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, "1.0"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, my_accessory_identify),
            NULL
        }),
        /*
         * 定义配件的服务
         * ｜服务名｜可在下面链接的文件中查看（p134）
         * https://github.com/ColdeZhang/Esp8266_Homekit_Template/blob/main/HAP-Specification-Non-Commercial-Version.pdf
         * 如：SWITCH
         * ｜是否为主服务｜每个配件除信息服务外有且仅有一个主服务，如果是主服务则填写true，否则可不填（删除.primmary）
         * 如：true
         * 
         * 注意：服务的变量名前需要加&
        */
        HOMEKIT_SERVICE(/*服务名*/, .primary=/*是否为主服务*/, .characteristics=(homekit_characteristic_t*[]) {
            &/*变量A*/,
			&/*变量B*/,
            &/*变量C*/
            NULL
        }),
        NULL
    }),
    NULL
};
```

修改为（可以删去所有注释）：

```c
homekit_accessory_t *accessories[] = {
    HOMEKIT_ACCESSORY(.id=1, .category=homekit_accessory_category_switch, .services=(homekit_service_t*[]) {
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "开关-测试01"),
            HOMEKIT_CHARACTERISTIC(MANUFACTURER, "Arduino HomeKit"),
            HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, "0123456"),
            HOMEKIT_CHARACTERISTIC(MODEL, "ESP8266/ESP32"),
            HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, "1.0"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, my_accessory_identify),
            NULL
        }),
        HOMEKIT_SERVICE(SWITCH, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
            &cha_on,
            NULL
        }),
        NULL
    }),
    NULL
};
```

#### 2.wifi_info.h



#### 3.Template.ino



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





