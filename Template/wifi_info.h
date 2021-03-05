/*
 * wifi_info.h
 * 
 * 该文件专用于配置、保存与处理wifi的连接与方法。
 * 
 * 一般情况下只需要修改第18行与19行引号之间的内容，分别为wifi的名称与密码
 */

#ifndef WIFI_INFO_H_
#define WIFI_INFO_H_

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#endif

const char *ssid = "Your-Wifi-Name";
const char *password = "Your-Wifi-Password";

void wifi_connect() {
	WiFi.persistent(false);
	WiFi.mode(WIFI_STA);
	WiFi.setAutoReconnect(true);
	WiFi.begin(ssid, password);
	Serial.println("WiFi connecting...");
	while (!WiFi.isConnected()) {
		delay(100);
		Serial.print(".");
	}
	Serial.print("\n");
	Serial.printf("WiFi connected, IP: %s\n", WiFi.localIP().toString().c_str());
}

#endif