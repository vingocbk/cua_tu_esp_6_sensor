#include <Arduino.h>
#include "AppDebug.h"
#include "WiFi.h"
#include <HTTPClient.h>
#include "WiFiClient.h"
#include "WebServer.h"
#include "ESPmDNS.h"
#include "ArduinoJson.h"
#include "Ticker.h"
#include "EEPROM.h"


#define hallSensor1 4  
#define hallSensor2 16  
#define hallSensor3 17
#define hallSensor4 26
#define hallSensor5 27
#define hallSensor6 14
#define ledTestWifi 32
#define inputFG 21
#define PWM 18
#define DIR 19
// #define BUTTON 15
#define ANALOGREADBUTTON 34
#define PIN_CONFIG 25

#define WL_MAC_ADDR_LENGTH 6

#define SCALE_AUTO 0.95
#define MINSPEED 8

#define RESPONSE_LENGTH 512     //do dai data nhan ve tu tablet
#define EEPROM_WIFI_SSID_START 0
#define EEPROM_WIFI_SSID_END 32
#define EEPROM_WIFI_PASS_START 33
#define EEPROM_WIFI_PASS_END 64
#define EEPROM_WIFI_IP_START 65
#define EEPROM_WIFI_IP_END 95
#define EEPROM_WIFI_IP_SEND_START 96
#define EEPROM_WIFI_IP_SEND_END 148
#define EEPROM_SET_MODE_RUN_BEGIN 149
#define EEPROM_DISTANT 150
#define EEPROM_SET_PERCENT_OUT_LOW_SPEED 151
#define EEPROM_SET_PERCENT_IN_LOW_SPEED 152
#define EEPROM_SET_TIME_RETURN 153
#define EEPROM_WIFI_MAX_CLEAR 256

#define SSID_PRE_AP_MODE "AvyInterior-"
#define PASSWORD_AP_MODE "123456789"


#define HTTP_PORT 80

// #define SSID "HPT 2B"
// #define PASS "hpt12345"

//#define SSID "hpt cnc"
//#define PASS "hpt12345"
#define CONFIG_HOLD_TIME 5000
#define TIME_CHECK_ANALOG 500
#define VALUE_ERROR_ANALOG 100

HTTPClient httpclient;
// ESP8266WebServer server(HTTP_PORT);
WebServer server(HTTP_PORT);




int countPulFG = 0;
int countPulFGDistant = 0;
uint8_t setmoderunbegin = 1; // nhanh nhat
uint8_t setmoderunbeginchange = 1;      //bien nay co tac dung thay doi toc do cham dan
int countPulDistant;                                 
uint8_t countSetPwm = 0;        //bien nay co tac dung dieu chinh toc do dong co
uint32_t countTime = 0;          //tinh thoi gian, timer 2 la 10us, vi the 100ms bien nay se co gia tri la 10.000
uint8_t sau_1_s = 0;
uint8_t timecaculateSpeed = 0;  //sau 500ms moi bat dau tinh van toc
int pul, prepul = 0;
int percentLowSpeedIn = 15;          //gia tri set mac dinh ban dau la 15% moi dau.
int percentLowSpeedOut = 15;
float speed;
bool statusStop = true;     //true la he thong dang dung im, false la he thong dang chuyen dong
bool countHall1 = false, countHall2 = false, countHall3 = false, countHall4 = false, countHall5 = false, countHall6 = false;
bool modeFast = false;
bool Forward = true;    //chieu quay thuan
bool fristRun = true;   //kiem tra lan chay dau tinh khoang cach chieu dai tu
bool daytay = true;
bool Flag_Normal_Mode = true;
bool isSaveDistant = false;
bool isSavePercentLowSpeed = false;
bool flag_send_status_when_use_hand = false;
bool flag_reset_value_analog = false;
int start_count_hall_sensor = 0;    //bat dau den 2 thi moi tinh day tay
int count_number_of_click = 0;      //click 5 lan thi chuyen mode
uint8_t countFrirstRun = 0;  //dem so lan va cham
uint32_t count_stop_motor = 0;
uint32_t time_click_button = 0;
uint32_t time_check_analog_pin = 0;
uint32_t pre_time_click_button = 0;
uint8_t first_octet;
uint8_t second_octet;
uint8_t third_octet;
uint8_t fourth_octet;

String esid, epass, eip, eipSend;
int stop_dau = 0;           //gia tri set cho khoang dung lai
int stop_cuoi = 0;
int time_return = 10;        //10 *10ms;
int loai_bien_giong_nhau_cua_cam_bien = 0;
int luu_trang_thai_cua_sensor_ngay_khi_dung_lai = 0;

int valueAnalogRead = 0;
int prevalueAnalogRead = 0;

//normal mode
void handleRoot();
void getStatus();
void setModeRunBegin();
void setPercentLowSpeed();
void inputSpeed();
void dirhallSensor1();
void dirhallSensor2();
void dirhallSensor3();
void dirhallSensor4();
void dirhallSensor5();
void dirhallSensor6();
void loadDataBegin();
void setpwmMotor();
void tickerupdate();
void caculateSpeed();
bool testWifi(String esid, String epass);
void StartNormalSever();
void buttonClick();
void Open();
void OpenClick();
void Close();
void CloseClick();
void Stop();
void StopClick();
void setpwmStopMotor();
void inputDistant();        //doc quang duong
void resetDistant();
void setTimeReturn();
void SetupNetwork();
void setSpeedControl();
//config mode
void setLedApMode();
void SetupConfigMode();             //phat wifi
void ConfigMode();                  //nhan data tu app
void StartConfigServer();           //thiet lap sever
bool connectToWifi(String nssid, String npass, String ip, String ipsend);
String GetFullSSID();
void detachIP(String ip);
void setupIP();



Ticker tickerCaculateSpeed(caculateSpeed, 100);   //every 200ms
Ticker SetPWMspeed(setpwmMotor, 10, 0, MICROS_MICROS);
Ticker SetPWMStopSpeed(setpwmStopMotor, 10, 0, MICROS_MICROS);
Ticker tickerSetApMode(setLedApMode, 200, 0);   //every 200ms
