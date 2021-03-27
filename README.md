# Esp8266_Homekit_Template
Template of Homekit for the Esp8266 based on Arduino

基于Esp8266的Homekit固件编写方法

[TOC]



## 0x0 快速入门

以点亮一个LED灯为例的，】完全新手的简易使用方法：



### 一、环境搭建

1.前往[Arduino官网](https://www.arduino.cc)下载对应自己系统班的[Arduino IDE](https://www.arduino.cc/en/software)（Windows用户可以前往[应用商店](https://www.microsoft.com/zh-cn/p/arduino-ide/9nblggh4rsd8)下载）并安装。

2.打开Arduino，Windows用户点击“文件”>“首选项”，Mac用户点击左上角“Arduino”>“Preference”。

<img src="https://raw.githubusercontent.com/ColdeZhang/PicGo/master/image-20210303171759207.png?token=AHDJQ6B6ML22YUNGVV3KTSLAH5KIM" alt="image-20210303171759207" style="zoom: 50%;" />

3.在“附加开发板管理器网址”一栏填上：

> https://arduino.esp8266.com/stable/package_esp8266com_index.json

<img src="https://raw.githubusercontent.com/ColdeZhang/PicGo/master/image-20210303171849958.png?token=AHDJQ6H6SB7RC6S64ODGIQ3AH5KLS" alt="image-20210303171849958" style="zoom:33%;" />

4.关闭窗口，打开“工具”>“开发版”>“开发版管理器”

<img src="https://raw.githubusercontent.com/ColdeZhang/PicGo/master/image-20210303172359306.png?token=AHDJQ6ARXUN6ORUZVMZZKHDAH5K7A" alt="image-20210303172359306" style="zoom:50%;" />

5.搜索“esp8266”并安装（文件较大，国内安装速度很慢且容易失败，多尝试几次即可）

<img src="https://raw.githubusercontent.com/ColdeZhang/PicGo/master/image-20210303174754999.png" alt="image-20210303174754999" style="zoom:50%;" />

6.关闭窗口，打开“工具”>“管理库...”

<img src="https://raw.githubusercontent.com/ColdeZhang/PicGo/master/image-20210303174922691.png" alt="image-20210303174922691" style="zoom: 50%;" />

7.搜索“homekit”，安装“HomeKit-ESP8266”

<img src="https://raw.githubusercontent.com/ColdeZhang/PicGo/master/image-20210303175023078.png" alt="image-20210303175023078" style="zoom:50%;" />



### 二、硬件链接

将LED的正极（长的那端）连接在Esp8266开发板的IO2口上，负极（短的那端）连接在GND上。



### 三、代码修改

[下载Template代码](https://github.com/ColdeZhang/Esp8266_Homekit_Template/releases/download/Template/Template.zip)解压后一共有三个文件。使用Arduino打开`Template.ino`，另外两个文件会自动被打开。

#### 1.my_accessory.c

##### （1）创建变量

找到以下行：

```c
homrkit_characteristic_t /*变量名*/ = HOMEKIT_CHARACTERISTIC_(/*变量类型*/,/*变量初始值*/);
```

修改`/*变量名*/`为`cha_on`，修改`/*变量类型*/`为`ON`，修改`/*变量初始值*/`为`false`，修改完成后应该是这个样子：

```c
homrkit_characteristic_t cha_on = HOMEKIT_CHARACTERISTIC_(ON, false);
```

##### （2）配置信息

找到以下代码：

```c
HOMEKIT_ACCESSORY(.id=/*编号*/, .category=homekit_accessory_category_/*种类*/, .services=(homekit_service_t*[])
```

修改`/*编号*/`为`1`，`/*种类*/`为`switch`，修改完后应该是这个样子：

```c
HOMEKIT_ACCESSORY(.id=1, .category=homekit_accessory_category_switch, .services=(homekit_service_t*[])
```

##### （3）服务设置

找到以下代码：

```c
HOMEKIT_SERVICE(/*服务名*/, .primary=/*是否为主服务*/, .characteristics=(homekit_characteristic_t*[]) {
	&/*变量名*/,
	NULL
}),
```

修改`/*服务名*/`为`SWITCH`，修改`/*是否为主服务*/`为`true`，修改`/*变量名*/`为`cha_on`，修改完后应该是这个样子：

```c
HOMEKIT_SERVICE(SWITCH, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
	&cha_on,
	NULL
}),
```



#### 2.wifi_info.h

找到如下两行：

```c
const char *ssid = "Your-Wifi-Name";
const char *password = "Your-Wifi-Password";
```

将第一行引号之间的`Your-Wifi-Name`替换为你的Wifi名称（区分大小写）。

在第二行引号之间的`Your-Wifi-Password`替换为你的Wifi密码。

#### 3.Template.ino

##### （1）定义引脚与触发器

在your_setup内添加：

```c
pinMode(2, OUTPUT);
digitalWrite(2, HIGH);
cha_on.setter = cha_on_setter;
```

##### （2）设置触发器：

在最末尾添加如下代码：

```c
void cha_on_setter(const homekit_value_t value) {
  bool on = value.bool_value;
  cha_on.value.bool_value = on;
  PRTLOG("开关状态: %s", on ? "开" : "O关");
  digitalWrite(2, on ? HIGH : LOW);
}
```



### 四、上传程序

打开Arduino，点击菜单栏中的“工具”，选择“开发板”>“ESP8266 Boards”>“Generic ESP8266 Module”。

再次点击菜单栏中的“工具”可以观察到相比于之前多出了一些选项，其中一些项目修改成如下内容：

- LwIP Variant: `v2 Lower Memory`
- Debug Level: `无`
- Espressif FW: `nonos-sdk 2.2.1+119(191122)` 
- SSL Support: `Basic SSL ciphers (lower ROM use)`
- VTables: `Flash`
- Erase Flash:  `All Flash Contents` 
- CPU Frequency: `160MHz`

修改完成后“工具”菜单应该如图所示：

<img src="https://raw.githubusercontent.com/ColdeZhang/PicGo/master/image-20210304181500770.png" alt="image-20210304181500770" style="zoom: 33%;" />

最后将你的ESP8266开发板连接至电脑，再在“工具”菜单内选择正确的端口（一般情况下唯一），点击上传按钮<img src="https://raw.githubusercontent.com/ColdeZhang/PicGo/master/image-20210314124254513.png" alt="image-20210314124254513" style="zoom:35%;" />等待程序上传。



### 五、连接验证

1. 确保你的手机与ESP8266处于同一Wifi内；
2. 打开家庭（Home）App<img src="https://raw.githubusercontent.com/ColdeZhang/PicGo/master/%E6%88%AA%E5%B1%8F%202021-03-05%2017.31.56.png" style="zoom:25%;" />，点击右上角加号，点击“添加或扫描配件”<img src="https://raw.githubusercontent.com/ColdeZhang/PicGo/master/%E6%88%AA%E5%B1%8F%202021-03-05%2017.34.31.png" style="zoom:20%;" />；
3. 点击最下方的“我没有或无法扫描代码”，如果一切正常那么此时应该会出现配件的图标<img src="https://raw.githubusercontent.com/ColdeZhang/PicGo/master/IMG_2618.jpg" style="zoom:20%;" />；
4. 点击配件的图标，会提示“未认证配件”的警告<img src="https://raw.githubusercontent.com/ColdeZhang/PicGo/master/IMG_2619.jpg" style="zoom:20%;" />选择“仍然添加”；
5. 输入代码“11111111”（八个1），稍等一会儿即可配对成功；



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

该文件专用于配置、保存与处理wifi的连接与方法。





## 0x2 设置一个传感器



