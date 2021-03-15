/*
 * Template.ino
 * 
 * 主程序，用于发送接收处理数据、操作IO口等等。
 * 
 * 如果你在此之前有使用Arduino的经验，为了代码的整洁性以及避免错误删除，请
 * 将你要写在setup()与loop()中的内容写在your_setup()与your_loop()内。
 * 除非您充分了解或者能理解此文件中已存在于setup()与loop()中的内容，否则请
 * 尽量不要修改或者改写他们中的内容
 * 
 * homekit_storage_reset();擦除配对记录，以便于重新配对
 */

#include <Arduino.h>
#include "wifi_info.h"
#include <arduino_homekit_server.h>;

//用于通过串口输出debug信息
#define PRTLOG(fmt, ...)   printf_P(PSTR(fmt "\n") , ##__VA_ARGS__);

/* 
 * 引入my_accessory.c中的配置与变量
 * 
 * 由于my_accessory.c是使用c语言编写的，因此想要在Arduino的ino文件中引用
 * 变量需要使用宏进行如下扩展
 * 
 *｜变量名｜
 * 即在my_accessory.c中定义的变量
*/
extern "C" homekit_server_config_t config;
extern "C" homekit_characteristic_t /*变量名*/;

//在此处添加你的setup
void your_setup(){

}

//在此处添加你的loop
void your_loop(){

}


//如果不了解请不要动这段代码
void setup() {
    your_setup();
	wifi_connect();
	arduino_homekit_setup(&config);
}

//如果不了解请不要动这段代码
void loop() {
	arduino_homekit_loop();
	const uint32_t t = millis();
	if (t > next_heap_millis) {
		next_heap_millis = t + 5 * 1000;
		PRTLOG("Free heap: %d, HomeKit clients: %d",ESP.getFreeHeap(), arduino_homekit_connected_clients_count());
	}
    your_loop();
    delay(10);
}



