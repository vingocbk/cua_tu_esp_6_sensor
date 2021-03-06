#include "cua_tu_esp_6_sensor.h"


void handleRoot() {
    server.send(200, "text/html", "<h1>You are connected</h1>");
    ECHOLN("done!");
}

void getStatus(){
    if(Forward == true){
        server.send(200, "text/html", "{\"status\" : \"close\"}");
    }else{
        server.send(200, "text/html", "{\"status\" : \"open\"}");
    }
    ECHOLN("getstatus");

}


void setModeRunBegin(){
    server.send(200, "application/json; charset=utf-8", "{\"status\":\"success\"}");
    StaticJsonBuffer<RESPONSE_LENGTH> jsonBuffer;
    ECHOLN(server.arg("plain"));
    JsonObject& rootData = jsonBuffer.parseObject(server.arg("plain"));
    ECHOLN("--------------");
    if (rootData.success()){
        String setmoderunstr = rootData["setmoderun"];
        // if(setmoderunstr == "1"){
        //     setmoderunbegin = 1;
        // }else if(setmoderunstr == "2"){
        //     setmoderunbegin = 2;
        // }else if(setmoderunstr == "3"){
        //     setmoderunbegin = 3;
        // }
        setmoderunbegin = setmoderunstr.toInt();
        setmoderunbeginchange = setmoderunbegin;
        ECHO("Writed: ");
        ECHOLN(setmoderunbegin);
        EEPROM.write(EEPROM_SET_MODE_RUN_BEGIN, char(setmoderunbegin));
        EEPROM.commit();
    }
}


void setPercentLowSpeed(){
    server.send(200, "application/json; charset=utf-8", "{\"status\":\"success\"}");
    StaticJsonBuffer<RESPONSE_LENGTH> jsonBuffer;
    ECHOLN(server.arg("plain"));
    JsonObject& rootData = jsonBuffer.parseObject(server.arg("plain"));
    ECHOLN("--------------");
    if (rootData.success()){
        String setpercentoutstr = rootData["setpercentout"];
        String setpercentinstr = rootData["setpercentin"];
        percentLowSpeedIn = setpercentinstr.toInt();
        percentLowSpeedOut = setpercentoutstr.toInt();
        ECHO("Writed: ");
        ECHO(percentLowSpeedOut);
        ECHO(",");
        ECHOLN(percentLowSpeedIn);
        EEPROM.write(EEPROM_SET_PERCENT_OUT_LOW_SPEED, char(percentLowSpeedOut));
        EEPROM.write(EEPROM_SET_PERCENT_IN_LOW_SPEED, char(percentLowSpeedIn));
        EEPROM.commit();
    }
}


void setTimeReturn(){
    server.send(200, "application/json; charset=utf-8", "{\"status\":\"success\"}");
    StaticJsonBuffer<RESPONSE_LENGTH> jsonBuffer;
    ECHOLN(server.arg("plain"));
    JsonObject& rootData = jsonBuffer.parseObject(server.arg("plain"));
    ECHOLN("--------------");
    if (rootData.success()){
        String timeReturnstr = rootData["timereturn"];
        time_return = timeReturnstr.toInt();
        ECHO("Writed: ");
        ECHO(time_return);
        EEPROM.write(EEPROM_SET_TIME_RETURN, char(time_return));
        EEPROM.commit();
    }
}

void resetDistant(){
    server.send(200, "text/html", "{\"status\":\"ok\"}");
    EEPROM.write(EEPROM_DISTANT, 0);
    EEPROM.commit();
    countPulFGDistant = 0;
    isSaveDistant = false;
    fristRun = true;
    countFrirstRun = 0;
    ECHOLN("resetDistant");
}


void loadDataBegin(){
    setmoderunbegin = char(EEPROM.read(EEPROM_SET_MODE_RUN_BEGIN));
    setmoderunbeginchange = setmoderunbegin;
    ECHOLN(setmoderunbegin);
    if(setmoderunbegin != 1 && setmoderunbegin != 2 && setmoderunbegin != 3 && setmoderunbegin != 4 && setmoderunbegin != 5){
        setmoderunbegin = 3;
        setmoderunbeginchange = setmoderunbegin;
        ECHOLN("read setmoderunbegin EEPROM fail, auto set 3!");
    }else{
        ECHO("read EEPROM done: ");
    }


    if(EEPROM.read(EEPROM_DISTANT) != 255 && EEPROM.read(EEPROM_DISTANT) != 0){
        isSaveDistant = true;
        countPulDistant = EEPROM.read(EEPROM_DISTANT);
        ECHO("Distant = ");
        ECHOLN(countPulDistant);
        CloseClick();
    }else{
        isSaveDistant = false;
        ECHOLN("isSaveDistant fasle!");
    }

    if(EEPROM.read(EEPROM_SET_TIME_RETURN) != 255 && EEPROM.read(EEPROM_SET_TIME_RETURN) != 0){
        time_return = EEPROM.read(EEPROM_SET_TIME_RETURN);
        ECHO("time_return = ");
        ECHO(time_return);
        ECHOLN("0 (ms)");
    }else{
        time_return = 30;
        ECHOLN("isSetTimeReurn fasle, auto set 300(ms)");
    }

    if(EEPROM.read(EEPROM_SET_PERCENT_OUT_LOW_SPEED) != 255 && EEPROM.read(EEPROM_SET_PERCENT_OUT_LOW_SPEED) != 0
        && EEPROM.read(EEPROM_SET_PERCENT_IN_LOW_SPEED) != 255 && EEPROM.read(EEPROM_SET_PERCENT_IN_LOW_SPEED) != 0){
        isSavePercentLowSpeed = true;
        percentLowSpeedIn = EEPROM.read(EEPROM_SET_PERCENT_IN_LOW_SPEED);
        ECHO("percentLowSpeedIn = ");
        ECHOLN(percentLowSpeedIn);

        percentLowSpeedOut = EEPROM.read(EEPROM_SET_PERCENT_OUT_LOW_SPEED);
        ECHO("percentLowSpeedOut = ");
        ECHOLN(percentLowSpeedOut);
    }else{
        isSavePercentLowSpeed = false;
        ECHOLN("isSavePercentLowSpeed fasle!");
    }


	countLedLight = 255;
	ledcWrite(LED_CHANNEL_R, countLedLight);




    valueAnalogRead = analogRead(ANALOG_READ_BUTTON);
    prevalueAnalogRead = valueAnalogRead;

    // ECHOLN("--------------------");
    // ECHOLN(int(((100 - (float)percentLowSpeedOut)/100)*countPulDistant - 2*(setmoderunbegin - 1)));
    // ECHOLN(int(((100 - (float)percentLowSpeedOut)/100)*countPulDistant));
    // ECHOLN(int(((100 - (float)percentLowSpeedOut)/100)*countPulDistant - 2*(setmoderunbegin - 1) + 2));
    // ECHOLN(int(((100 - (float)percentLowSpeedOut)/100)*countPulDistant - 2*(setmoderunbegin - 1) + 4));

    for(int i = 1; i <= 5; i++){
        valueTouchSensorFix += touchRead(PIN_TOUCH_SENSOR);
        if(i == 5){
            valueTouchSensorFix = valueTouchSensorFix/5;
            ECHO("valueTouchSensorFix = ");
            ECHOLN(valueTouchSensorFix);
            break;
        }
    }
}

void Open(){
    server.send(200, "text/html", "{\"status\":\"open\"}");
    ECHOLN("open");
    statusStop = false;
    Forward = true;
    daytay = false;
    digitalWrite(DIR, HIGH);
    SetPWMspeed.start();
    tickerCaculateSpeed.start();
	//bat den led
	if(countLedLight == 0){
		tickerSetPwmLedLightOff.stop();
		tickerSetPwmLedLightOn.start();
	}
}
void OpenClick(){
    ECHOLN("open_click");
    statusStop = false;
    Forward = true;
    daytay = false;
    digitalWrite(DIR, HIGH);
    SetPWMspeed.start();
    tickerCaculateSpeed.start();
	//bat den led
	if(countLedLight == 0){
		tickerSetPwmLedLightOff.stop();
		tickerSetPwmLedLightOn.start();
	}
}

void Close(){
    server.send(200, "text/html", "{\"status\":\"close\"}");
    ECHOLN("close");
    statusStop = false;
    Forward = false;
    daytay = false;
    digitalWrite(DIR, LOW);
    SetPWMspeed.start();
    tickerCaculateSpeed.start();
}

void CloseClick(){
    ECHOLN("close_click");
    statusStop = false;
    Forward = false;
    daytay = false;
    digitalWrite(DIR, LOW);
    SetPWMspeed.start();
    tickerCaculateSpeed.start();
}

void Stop(){
    ECHOLN("Stop");
    server.send(200, "text/html", "{\"status\":\"stop\"}");
    tickerCaculateSpeed.stop();
    SetPWMspeed.stop();
    digitalWrite(PWM, LOW);
    delay(200);
    statusStop = false;
    daytay = false;
    timecaculateSpeed = 0;
    if(Forward == true){
        digitalWrite(DIR, LOW);     //cho dong co quay nghich
        Forward = false;
    }else{
        digitalWrite(DIR, HIGH);
        Forward = true;
    }
    SetPWMStopSpeed.start();
}

void StopClick(){
    ECHOLN("Stop_click");
    tickerCaculateSpeed.stop();
    SetPWMspeed.stop();
    digitalWrite(PWM, LOW);
    delay(200);
    statusStop = false;
    daytay = false;
    timecaculateSpeed = 0;
    if(Forward == true){
        digitalWrite(DIR, LOW);     //cho dong co quay nghich
        Forward = false;
    }else{
        digitalWrite(DIR, HIGH);
        Forward = true;
    }
    SetPWMStopSpeed.start();
}



void SetupNetwork() {
    ECHOLN("Reading EEPROM ssid");
    esid = "";
    for (int i = EEPROM_WIFI_SSID_START; i < EEPROM_WIFI_SSID_END; ++i){
        esid += char(EEPROM.read(i));
    }
    ECHO("SSID: ");
    ECHOLN(esid);
    ECHOLN("Reading EEPROM pass");
    epass = "";
    for (int i = EEPROM_WIFI_PASS_START; i < EEPROM_WIFI_PASS_END; ++i){
        epass += char(EEPROM.read(i));
    }
    ECHO("PASS: ");
    ECHOLN(epass);
    ECHOLN("Reading EEPROM IP");
    eip = "";
    for (int i = EEPROM_WIFI_IP_START; i < EEPROM_WIFI_IP_END; ++i){
        eip += char(EEPROM.read(i));
    }
    ECHO("IP: ");
    ECHOLN(eip);
    detachIP(eip);  //tach ip thanh 4 kieu uint8_t
    ECHOLN("Reading EEPROM IPSEND");
    eipSend = "";
    for (int i = EEPROM_WIFI_IP_SEND_START; i < EEPROM_WIFI_IP_SEND_END; ++i){
        if(char(EEPROM.read(i)) == '\0'){
            break;
        }
        eipSend += char(EEPROM.read(i));
    }
    ECHO("IPSEND: ");
    ECHOLN(eipSend);
    testWifi(esid, epass);
}

bool testWifi(String esid, String epass) {
    ECHO("Connecting to: ");
    ECHOLN(esid);
    WiFi.softAPdisconnect();
    WiFi.disconnect();
    server.close();
    delay(1000);
    setupIP();      //cai dat ip theo quy dinh
    // WiFi.config(ip, gateway, subnet);
    WiFi.mode(WIFI_STA);        //bat che do station
    WiFi.begin(esid.c_str(), epass.c_str());
    int c = 0;
    ECHOLN("Waiting for Wifi to connect");
    while (c < 40) {
        if (WiFi.status() == WL_CONNECTED) {
            ECHOLN("\rWifi connected!");
            ECHO("Local IP: ");
            ECHOLN(WiFi.localIP());
            digitalWrite(ledTestWifi, HIGH);
            StartNormalSever();
            // tickerSetApMode.start();
            return true;
        }
        if(digitalRead(PIN_CONFIG) == LOW){
            break;
        }
        delay(500);
        ECHO(".");
        c++;
    }
    ECHOLN("");
    ECHOLN("Connect timed out");
    return false;
}





void StartNormalSever(){
    server.on("/", HTTP_GET, handleRoot);
    server.on("/getstatus", HTTP_GET, getStatus);
    server.on("/setmoderun", HTTP_POST, setModeRunBegin);
    server.on("/setlowspeed", HTTP_POST, setPercentLowSpeed);
    server.on("/settimereturn", HTTP_POST, setTimeReturn);
    server.on("/resetdistant", HTTP_GET, resetDistant);
    server.on("/open", HTTP_GET, Open);
    server.on("/close", HTTP_GET, Close);
    server.on("/stop", HTTP_GET, Stop);
    server.begin();
    ECHOLN("HTTP server started");
    
}





void caculateSpeed(){
    //ECHOLN("speed");
    if(timecaculateSpeed <= 30){
        timecaculateSpeed++;
    }
    pul = countPulFG;
    speed = (pul - prepul)/(0.1*6);
    prepul = pul;
    

    if(countFrirstRun == 2 && countPulFG > stop_dau && countPulFG < (countPulDistant - stop_cuoi)){        //countFrirstRun = 2 la luc bat dau qua trinh chay nhanh (modeFast = true)
        countFrirstRun = 10;        //lan dau tien chay nhanh
    }


    // ECHO("van toc: ");
    // ECHOLN(speed);
    if(abs(speed) <= MINSPEED && timecaculateSpeed >= 3){   //sau 3 lan chay thi moi tinh den van toc
        ECHOLN("Da dung lai");
        tickerCaculateSpeed.stop();
        SetPWMspeed.stop(); 
        digitalWrite(PWM, LOW);
        statusStop = false;

        

        if(isSaveDistant == true && fristRun == true){
            fristRun = false;
            countPulFGDistant = 0;
            prepul = 0;
        }
        


        if(fristRun == true && countFrirstRun < 5){
            countFrirstRun++;
        }
        
        if(fristRun == true && countFrirstRun == 1){
            countPulFGDistant = 0;
            prepul = 0;
        }
        else if(fristRun == true && countFrirstRun == 2){
            countPulDistant = abs(countPulFGDistant);
            EEPROM.write(EEPROM_DISTANT, countPulDistant);
            EEPROM.commit();
            isSaveDistant = true;
            if(countPulFGDistant < 0){
                countPulFGDistant = 0;
                prepul = 0;
            }
            fristRun = false;
        }


        if(fristRun == false && countPulFGDistant <= 3){
            // //tat den
			// countLedOn = 0;
			// ledcWrite(LED_CHANNEL_R, countLedOn);
			countPulFGDistant = 0;
            flag_send_status_when_use_hand = true;
        }else if(fristRun == false && (countPulDistant -3) <= countPulFGDistant){
            countPulFGDistant = countPulDistant;
            flag_send_status_when_use_hand = true;
        }
        
        if(Forward == true){
            digitalWrite(DIR, LOW);     //cho dong co quay nghich
            Forward = false;
        }else{
            digitalWrite(DIR, HIGH);
            Forward = true;
        }

        timecaculateSpeed = 0;
        SetPWMStopSpeed.start();    
    }
}

void setpwmMotor(){
    countSetPwm++;
    switch(setmoderunbeginchange){
        case 1:{
            if(modeFast == false){ //ti le PWM la 4 HIGH 1 LOW
                switch (countSetPwm){
                    case 1: {
                        digitalWrite(PWM, HIGH);
                        break;
                    }
                    case 5: {
                        digitalWrite(PWM, LOW);
                        countSetPwm = 0;
                        break;
                    }
                }
            }else{                //ti le PWM la 1 HIGH 3 LOWset
                digitalWrite(PWM, HIGH);
            }
            break;
        }
        case 2:{
            if(modeFast == false){ //ti le PWM la 3 HIGH 2 LOW
                switch (countSetPwm){
                    case 1: {
                        digitalWrite(PWM, HIGH);
                        break;
                    }
                    case 4: {
                        digitalWrite(PWM, LOW);
                        break;
                    }
                    case 5: {
                        countSetPwm = 0;
                        break;
                    }
                }
            }else{                //ti le PWM la 1 HIGH 3 LOW
                digitalWrite(PWM, HIGH);
            } 
            break;
        }
        case 3:{
            if(modeFast == false){ //ti le PWM la 2 HIGH 3 LOW
                switch (countSetPwm){
                    case 1: {
                        digitalWrite(PWM, HIGH);
                        break;
                    }
                    case 3: {
                        digitalWrite(PWM, LOW);
                        break;
                    }
                    case 5: {
                        countSetPwm = 0;
                        break;
                    }
                }
            }else{                //ti le PWM la 1 HIGH 3 LOW
                digitalWrite(PWM, HIGH);
            } 
            break;
        }
        case 4:{
            if(modeFast == false){ //ti le PWM la 1 HIGH 4 LOW
                switch (countSetPwm){
                    case 1: {
                        digitalWrite(PWM, HIGH);
                        break;
                    }
                    case 2: {
                        digitalWrite(PWM, LOW);
                        break;
                    }
                    case 5: {
                        countSetPwm = 0;
                        break;
                    }
                }
            }else{                //ti le PWM la 1 LOW 4 HIGH
                digitalWrite(PWM, HIGH);
            } 
            break;
        }

    }

}

void setpwmStopMotor(){
    count_stop_motor++;
    //ECHOLN(count_stop_motor);
    // if(Forward == true){
    //     digitalWrite(DIR, HIGH);
    // }else{
    //     digitalWrite(DIR, LOW);
    // }
    if(count_stop_motor % 4 == 0){
        digitalWrite(PWM, HIGH);
    }else{
        digitalWrite(PWM, LOW);
        //countSetPwm = 0;
    }
    if(count_stop_motor >= time_return*1000){       //time_return *10 ms      
        SetPWMStopSpeed.stop();
        // delay(100);
        digitalWrite(PWM, LOW);
        delay(100);
        luu_trang_thai_cua_sensor_ngay_khi_dung_lai = loai_bien_giong_nhau_cua_cam_bien;
        // ECHOLN(luu_trang_thai_cua_sensor_ngay_khi_dung_lai);
        loai_bien_giong_nhau_cua_cam_bien = 0;
        count_stop_motor = 0;


        statusStop = true;
        daytay = true;
        if(flag_send_status_when_use_hand == true && Forward == true){      //dang o trang thai dong cua
            String ipsend = "http://";
            ipsend += eipSend;
            ipsend += ":8888/close";
            httpclient.begin(ipsend); //HTTP
            ECHOLN(ipsend);
            int httpCode = httpclient.GET();
            // httpCode will be negative on error
            if (httpCode > 0) {
                // HTTP header has been send and Server response header has been handled
                ECHO("[HTTP] GET... code: ");
                ECHOLN(httpCode);

                // file found at server
                if (httpCode == HTTP_CODE_OK) {
                    String payload = httpclient.getString();
                    ECHOLN(payload);
                }
            } else {
                ECHO("[HTTP] GET... failed, error: ");
                ECHOLN(httpclient.errorToString(httpCode).c_str());
            }
            httpclient.end();
            flag_send_status_when_use_hand = false;
            flag_reset_value_analog = true;
            
        }
        else if(flag_send_status_when_use_hand == true && Forward == false){    //dang o trang thai mo cua
            String ipsend = "http://";
            ipsend += eipSend;
            ipsend += ":8888/open";
            httpclient.begin(ipsend); //HTTP
            ECHOLN(ipsend);
            int httpCode = httpclient.GET();
            // httpCode will be negative on error
            if (httpCode > 0) {
                // HTTP header has been send and Server response header has been handled
                ECHO("[HTTP] GET... code: ");
                ECHOLN(httpCode);

                // file found at server
                if (httpCode == HTTP_CODE_OK) {
                    String payload = httpclient.getString();
                    ECHOLN(payload);
                }
            } else {
                ECHO("[HTTP] GET... failed, error: ");
                ECHOLN(httpclient.errorToString(httpCode).c_str());
            }
            httpclient.end();
            flag_send_status_when_use_hand = false;
        }
        //reset lai vi tri cua button analog
        // flag_reset_value_analog = true;
        // valueAnalogRead = analogRead(ANALOGREADBUTTON);
        // prevalueAnalogRead = valueAnalogRead;
        
    }
    
}


void setLedApMode() {
    digitalWrite(ledTestWifi, !digitalRead(ledTestWifi));
}

void setPwmLedLighton(){
	countLedLight++;
	if(countLedLight > 255){
		countLedLight = 255;
		return;
	}
	ledcWrite(LED_CHANNEL_R, countLedLight);
}

void setPwmLedLightoff(){
	countLedLight--;
	if(countLedLight < 0){
		countLedLight = 0;
		return;
	}
	ledcWrite(LED_CHANNEL_R, countLedLight);
}

bool connectToWifi(String nssid, String npass, String ip, String ipsend) {
    ECHOLN("Open STA....");
    WiFi.softAPdisconnect();
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    delay(100);
    setupIP();
    //WiFi.begin(nssid.c_str(), npass.c_str());

    if (testWifi(nssid, npass)) {
        ECHOLN("clearing eeprom");
        for (int i = 0; i < EEPROM_WIFI_IP_SEND_END; i++){ 
            EEPROM.write(i, 0); 
        }
        ECHOLN("writing eeprom ssid:");
        ECHO("Wrote: ");
        for (int i = 0; i < nssid.length(); ++i){
            EEPROM.write(i+EEPROM_WIFI_SSID_START, nssid[i]);             
            ECHO(nssid[i]);
        }
        ECHOLN("");
        ECHOLN("writing eeprom pass:"); 
        ECHO("Wrote: ");
        for (int i = 0; i < npass.length(); ++i){
            EEPROM.write(i+EEPROM_WIFI_PASS_START, npass[i]);
            ECHO(npass[i]);
        }
        ECHOLN("");
        ECHOLN("writing eeprom IP:"); 
        ECHO("Wrote: ");
        for (int i = 0; i < ip.length(); ++i){
            EEPROM.write(i+EEPROM_WIFI_IP_START, ip[i]);             
            ECHO(ip[i]);
        }
        ECHOLN("");
        EEPROM.commit();
        ECHOLN("writing eeprom IPSEND:");
        ECHO("Wrote: ");
        for (int i = 0; i < ipsend.length(); ++i){
            EEPROM.write(i+EEPROM_WIFI_IP_SEND_START, ipsend[i]);             
            ECHO(ipsend[i]);
        }
        ECHOLN("");
        EEPROM.commit();
        ECHOLN("Done writing!");
        return true;
    }

    return false;
}

void SetupConfigMode(){
    ECHOLN("[WifiService][setupAP] Open AP....");
    WiFi.softAPdisconnect();
    WiFi.disconnect();
    server.close();
    delay(500);
    WiFi.mode(WIFI_AP_STA);
    IPAddress APIP(192, 168, 4, 1);
    IPAddress gateway(192, 168, 4, 1);
    IPAddress subnet(255, 255, 255, 0);
    WiFi.softAPConfig(APIP, gateway, subnet);
    String SSID_AP_MODE = GetFullSSID();
    WiFi.softAP(SSID_AP_MODE.c_str(), PASSWORD_AP_MODE);
    ECHOLN(SSID_AP_MODE);

    ECHOLN("[WifiService][setupAP] Softap is running!");
    IPAddress myIP = WiFi.softAPIP();
    ECHO("[WifiService][setupAP] IP address: ");
    ECHOLN(myIP);
}


void StartConfigServer(){    
    ECHOLN("[HttpServerH][startConfigServer] Begin create new server...");
    server.on("/", HTTP_GET, handleRoot);
    server.on("/config", HTTP_POST, ConfigMode);
    server.begin();
    ECHOLN("[HttpServerH][startConfigServer] HTTP server started");
}

String GetFullSSID() {
    uint8_t mac[WL_MAC_ADDR_LENGTH];
    String macID;
    WiFi.mode(WIFI_AP);
    WiFi.softAPmacAddress(mac);
    macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) + String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
    macID.toUpperCase();
    macID = SSID_PRE_AP_MODE + macID;
    ECHO("[Helper][getIdentify] Identify: ");
    ECHOLN(macID);
    return macID;
}


void ConfigMode(){
    StaticJsonBuffer<RESPONSE_LENGTH> jsonBuffer;
    ECHOLN(server.arg("plain"));
    JsonObject& rootData = jsonBuffer.parseObject(server.arg("plain"));
    ECHOLN("--------------");
    tickerSetApMode.stop();
    digitalWrite(ledTestWifi, LOW);
    if (rootData.success()) {
        server.sendHeader("Access-Control-Allow-Headers", "*");
        server.sendHeader("Access-Control-Allow-Origin", "*");
        server.send(200, "application/json; charset=utf-8", "{\"status\":\"success\"}");
        //server.stop();
        String nssid = rootData["ssid"];
        String npass = rootData["password"];
        String ip = rootData["set_ip"];
        String ipsend = rootData["ip_send"];

        detachIP(ip); 
        ECHO("Wifi new name: ");
        ECHOLN(nssid);
        ECHO("Wifi new password: ");
        ECHOLN(npass);
        ECHO("Wifi new IP: ");
        ECHO(first_octet);
        ECHO(".");
        ECHO(second_octet);
        ECHO(".");
        ECHO(third_octet);
        ECHO(".");
        ECHOLN(fourth_octet);
        ECHO("Wifi new ipSend: ");
        ECHOLN(ipsend);

        if (connectToWifi(nssid, npass, ip, ipsend)) {
            esid = nssid;
            epass = npass;
            eipSend = ipsend;
            StartNormalSever();
            Flag_Normal_Mode = true;
            return;
        }
        tickerSetApMode.start();
        ECHOLN("Wrong wifi!!!");
        SetupConfigMode();
        StartConfigServer();
        return;
    }
    ECHOLN("Wrong data!!!");
}

void detachIP(String ip){
    String first_octetStr = "";
    String second_octetStr = "";
    String third_octetStr = "";
    String fourth_octetStr = "";
    for(int i = 0, j = 0; i <= sizeof(ip)+1; i++){
        char c = ip[i];
        if(c == '.'){
            j++;
            continue;
        }
        switch(j){
            case 0:
                first_octetStr += c;
                break;
            case 1:
                second_octetStr += c;
                break;
            case 2:
                third_octetStr += c;
                break;
            case 3:
                fourth_octetStr += c;
                break;
        }

    }

    first_octet = atoi(first_octetStr.c_str());
    second_octet = atoi(second_octetStr.c_str());
    third_octet = atoi(third_octetStr.c_str());
    fourth_octet = atoi(fourth_octetStr.c_str());
}

void setupIP(){
    // config static IP
    IPAddress ip(first_octet, second_octet, third_octet, fourth_octet); // where xx is the desired IP Address
    IPAddress gateway(first_octet, second_octet, third_octet, 1); // set gateway to match your network
    IPAddress subnet(255, 255, 255, 0); // set subnet mask to match your network
    WiFi.config(ip, gateway, subnet);
}


void IRAM_ATTR dirhallSensor1(){      //nhan du lieu tu cam bien ben ngoai
    if(loai_bien_giong_nhau_cua_cam_bien != 1){
        loai_bien_giong_nhau_cua_cam_bien = 1;
        ECHOLN("1");
        if(Forward == true){
            countPulFGDistant++;
        }else{
            countPulFGDistant--;
        }

        if(daytay == true && statusStop == true){
            // loai_bien_giong_nhau_cua_cam_bien = 0;
            if(countHall2 == true){
                //cho dong co chay thuan
                countHall2 = false;
                ECHOLN("open");
                OpenClick();
            }
            else if(countHall6 == true){
                //cho dong co chay nghich
                countHall6 = false;
                ECHOLN("close");
                CloseClick();
            }
            else{
                countHall1 = true;
            }
        }
    }
    
}

void IRAM_ATTR dirhallSensor2(){
    if(loai_bien_giong_nhau_cua_cam_bien != 2){
        loai_bien_giong_nhau_cua_cam_bien = 2;
        ECHOLN("2");
        if(Forward == true){
            countPulFGDistant++;
        }else{
            countPulFGDistant--;
        }

        // ECHOLN(co untPulFGDistant);
        if(daytay == true && statusStop == true){
            // loai_bien_giong_nhau_cua_cam_bien = 0;
            if(countHall3 == true){
                //cho dong co chay thuan
                countHall3 = false;
                ECHOLN("open");
                OpenClick();
            }
            else if(countHall1 == true){
                //cho dong co chay nghich
                countHall1 = false;
                ECHOLN("close");
                CloseClick();
            }
            else{
                countHall2 = true;
            }
        }
    }
}
void IRAM_ATTR dirhallSensor3(){
    if(loai_bien_giong_nhau_cua_cam_bien != 3){
        loai_bien_giong_nhau_cua_cam_bien = 3;
        ECHOLN("3");
        if(Forward == true){
            countPulFGDistant++;
        }else{
            countPulFGDistant--;
        }

        if(daytay == true && statusStop == true){
            // loai_bien_giong_nhau_cua_cam_bien = 0;
            if(countHall4 == true){
                //cho dong co chay thuan
                countHall4 = false;
                ECHOLN("open");
                OpenClick();
            }
            else if(countHall2 == true){
                //cho dong co chay nghich
                countHall2 = false;
                ECHOLN("close");
                CloseClick();
            }
            else{
                countHall3 = true;
            }
        }
    }
}

void IRAM_ATTR dirhallSensor4(){
    if(loai_bien_giong_nhau_cua_cam_bien != 4){
        loai_bien_giong_nhau_cua_cam_bien = 4;
        ECHOLN("4");
        if(Forward == true){
            countPulFGDistant++;
        }else{
            countPulFGDistant--;
        }

        if(daytay == true && statusStop == true){
            // loai_bien_giong_nhau_cua_cam_bien = 0;
            if(countHall5 == true){
                //cho dong co chay thuan
                countHall5 = false;
                ECHOLN("open");
                OpenClick();
            }
            else if(countHall3 == true){
                //cho dong co chay nghich
                countHall3 = false;
                ECHOLN("close");
                CloseClick();
            }
            else{
                countHall4 = true;
            }
        }
    }
}

void IRAM_ATTR dirhallSensor5(){
    if(loai_bien_giong_nhau_cua_cam_bien != 5){
        loai_bien_giong_nhau_cua_cam_bien = 5;
        ECHOLN("5");
        if(Forward == true){
            countPulFGDistant++;
        }else{
            countPulFGDistant--;
        }

        if(daytay == true && statusStop == true){
            // loai_bien_giong_nhau_cua_cam_bien = 0;
            if(countHall6 == true){
                //cho dong co chay thuan
                countHall6 = false;
                ECHOLN("open");
                OpenClick();
            }
            else if(countHall4 == true){
                //cho dong co chay nghich
                countHall4 = false;
                ECHOLN("close");
                CloseClick();
            }
            else{
                countHall5 = true;
            }
        }
    }
}

void IRAM_ATTR dirhallSensor6(){
    if(loai_bien_giong_nhau_cua_cam_bien != 6){
        loai_bien_giong_nhau_cua_cam_bien = 6;
        ECHOLN("6");
        if(Forward == true){
            countPulFGDistant++;
        }else{
            countPulFGDistant--;
        }

        if(daytay == true && statusStop == true){
            // loai_bien_giong_nhau_cua_cam_bien = 0;
            if(countHall1 == true){
                //cho dong co chay thuan
                countHall1 = false;
                ECHOLN("open");
                OpenClick();
            }
            else if(countHall5 == true){
                //cho dong co chay nghich
                countHall5 = false;
                ECHOLN("close");
                CloseClick();
            }
            else{
                countHall6 = true;
            }
        }
    }
}


void IRAM_ATTR inputSpeed(){
    if(Forward == true){
        countPulFG++;
    }else{
        countPulFG--;
    }
    // ECHOLN(countPulFG);
}


void checkTouchSensor(){
    if(abs(millis() - time_check_touch_sensor) > TIME_CHECK_TOUCH_SENSOR){
        time_check_touch_sensor = millis();
        for(int i = 0; i <= 2; i++){
            valueTouchSensor = touchRead(PIN_TOUCH_SENSOR);
            if(abs(valueTouchSensorFix - valueTouchSensor) <= VALUE_ERROR_TOUCH_SENSOR){
                return;
            }
        }

        ECHOLN("buttonClick");
        digitalWrite(PWM, LOW);
        daytay = false;
        delay(500);
        if(statusStop == false){
            StopClick();
        }
        else if(Forward == false && statusStop == true){
            CloseClick();
        }else{
            OpenClick();
        }
    }
}


void checkAnalogReadButton(){
    //reset_value_analog
    //flag_reset_value_analog dung de reset lai gia tri bien tro: pre = current
    //flag = true thi se reset, con bang false la da reset roi, vi the load gia tri phai la bang false
    if(flag_reset_value_analog == true){
        valueAnalogRead = analogRead(ANALOG_READ_BUTTON);
        prevalueAnalogRead = valueAnalogRead;
        flag_reset_value_analog = false;
    }

    //analogRead
    if(flag_reset_value_analog == false && statusStop == true && Forward == true && abs(millis() - time_check_analog_pin) > TIME_CHECK_ANALOG){
        time_check_analog_pin = millis();

        for(int i = 0; i <= 1; i++){
            valueAnalogRead = analogRead(ANALOG_READ_BUTTON);
            if(abs(valueAnalogRead - prevalueAnalogRead) <= VALUE_ERROR_ANALOG){
                return;
            }
        }
        OpenClick();
    }
}

void setSpeedControl(){
    // ECHOLN(countPulFGDistant > (percentLowSpeedOut/100)*countPulDistant);
    if(fristRun == false && Forward == true && countPulFGDistant < ((100 - (float)percentLowSpeedOut)/100)*countPulDistant){
        modeFast = true;
    }else if(fristRun == false && Forward == false && countPulFGDistant > ((float)percentLowSpeedIn/100)*countPulDistant){
        modeFast = true;       
    }else{
        modeFast = false;
    }
}

void tickerupdate(){
    tickerCaculateSpeed.update();
    SetPWMspeed.update();
    SetPWMStopSpeed.update();
    tickerSetApMode.update();
	tickerSetPwmLedLightOn.update();
	tickerSetPwmLedLightOff.update();
}



void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);
    EEPROM.begin(EEPROM_WIFI_MAX_CLEAR);
    ledcAttachPin(PIN_LED_LIGHT_R, LED_CHANNEL_R); // analog pin to channel 1
    ledcSetup(LED_CHANNEL_R, 12000, 8); // 12 kHz PWM, 8-bit resolution
    ECHOLN("");
    ECHOLN("START!!!");
    pinMode(DIR, OUTPUT);
    pinMode(PWM, OUTPUT);
    pinMode(PIN_CONFIG, INPUT_PULLUP);
    pinMode(inputFG, INPUT_PULLUP);
    pinMode(hallSensor1, INPUT_PULLUP);
    pinMode(hallSensor2, INPUT_PULLUP);
    pinMode(hallSensor3, INPUT_PULLUP);
    pinMode(hallSensor4, INPUT_PULLUP);
    pinMode(hallSensor5, INPUT_PULLUP);
    pinMode(hallSensor6, INPUT_PULLUP);
    pinMode(ledTestWifi, OUTPUT);
    digitalWrite(ledTestWifi, LOW);
    
    
    loadDataBegin();
    SetupNetwork();


    attachInterrupt(digitalPinToInterrupt(hallSensor1), dirhallSensor1, RISING);
    attachInterrupt(digitalPinToInterrupt(hallSensor2), dirhallSensor2, RISING);
    attachInterrupt(digitalPinToInterrupt(hallSensor3), dirhallSensor3, RISING);
    attachInterrupt(digitalPinToInterrupt(hallSensor4), dirhallSensor4, RISING);
    attachInterrupt(digitalPinToInterrupt(hallSensor5), dirhallSensor5, RISING);
    attachInterrupt(digitalPinToInterrupt(hallSensor6), dirhallSensor6, RISING);
    attachInterrupt(digitalPinToInterrupt(inputFG), inputSpeed, FALLING);
    


}

void loop() {
    // put your main code here, to run repeatedly:
    if (Flag_Normal_Mode == true && WiFi.status() != WL_CONNECTED){
        digitalWrite(ledTestWifi, LOW);
        testWifi(esid, epass);
    }    


    //hold to config mode
    if(digitalRead(PIN_CONFIG) == HIGH){
        time_click_button = millis();
    }
    if(digitalRead(PIN_CONFIG) == LOW && (time_click_button + CONFIG_HOLD_TIME) <= millis()){
        time_click_button = millis();
        // StopClick();
        digitalWrite(ledTestWifi, LOW);
        Flag_Normal_Mode = false;
        tickerSetApMode.start();
        SetupConfigMode();
        StartConfigServer();
    }


	//tat den led khi quay ve
	if(statusStop == false  && countPulFGDistant <= 10){
		if(countLedLight == 255){
			countLedLight = 254;
			tickerSetPwmLedLightOn.stop();
			tickerSetPwmLedLightOff.start();
		}
	}


    checkTouchSensor();
    checkAnalogReadButton();
    setSpeedControl();
    tickerupdate();
    server.handleClient();

}
