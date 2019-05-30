#include "cua_tu_esp_6_sensor.h"




void dirhallSensor1(){      //nhan du lieu tu cam bien ben ngoai
    // if(daytay == true && statusStop == true && luu_trang_thai_cua_sensor_ngay_khi_dung_lai == 2){
//         ECHOLN("true1");
    //     Forward = true;
    //     luu_trang_thai_cua_sensor_ngay_khi_dung_lai = 0;
    // }else if(daytay == true && statusStop == true && luu_trang_thai_cua_sensor_ngay_khi_dung_lai == 3){
    //     ECHOLN("false1");
    //     Forward = false;
    //     luu_trang_thai_cua_sensor_ngay_khi_dung_lai = 0;
    // }
    if(loai_bien_giong_nhau_cua_cam_bien != 1){
        loai_bien_giong_nhau_cua_cam_bien = 1;
         ECHOLN("1");

        // if(Forward == true){
        //     countPulFGDistant++;
        // }else{
        //     countPulFGDistant--;
        // }

        if(daytay == true && statusStop == true){
            //ECHOLN("1");
            // loai_bien_giong_nhau_cua_cam_bien = 0;
            if(countHall2 == true){
                //cho dong co chay thuan
                countHall1 = false;
                countHall2 = false;
                countHall3 = false;
                //ECHOLN("open");
                OpenClick();
            }
            else if(countHall3 == true){
                //cho dong co chay nghich
                countHall1 = false;
                countHall2 = false;
                countHall3 = false;
                //ECHOLN("close");
                CloseClick();
            }
            else{
                countHall1 = true;
            }
        }
    }
    
}

void dirhallSensor2(){
    // if(daytay == true && statusStop == true && luu_trang_thai_cua_sensor_ngay_khi_dung_lai == 3){
//         ECHOLN("true2");
    //     Forward = true;
    //     luu_trang_thai_cua_sensor_ngay_khi_dung_lai = 0;
    // }else if(daytay == true && statusStop == true && luu_trang_thai_cua_sensor_ngay_khi_dung_lai == 1){
    //     ECHOLN("false2");
    //     Forward = false;
    //     luu_trang_thai_cua_sensor_ngay_khi_dung_lai = 0;
    // }


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
            //ECHOLN("2");
            // loai_bien_giong_nhau_cua_cam_bien = 0;
            if(countHall3 == true){
                //cho dong co chay thuan
                countHall1 = false;
                countHall2 = false;
                countHall3 = false;
                //ECHOLN("open");
                OpenClick();
            }
            else if(countHall1 == true){
                //cho dong co chay nghich
                countHall1 = false;
                countHall2 = false;
                countHall3 = false;
                //ECHOLN("close");
                CloseClick();
            }
            else{
                countHall2 = true;
            }
        }
    }
}
void dirhallSensor3(){
    // if(daytay == true && statusStop == true && luu_trang_thai_cua_sensor_ngay_khi_dung_lai == 1){
//         ECHOLN("true3");
    //     Forward = true;
    //     luu_trang_thai_cua_sensor_ngay_khi_dung_lai = 0;
    // }else if(daytay == true && statusStop == true && luu_trang_thai_cua_sensor_ngay_khi_dung_lai == 2){
    //     ECHOLN("false3");
    //     Forward = false;
    //     luu_trang_thai_cua_sensor_ngay_khi_dung_lai = 0;
    // }

    if(loai_bien_giong_nhau_cua_cam_bien != 3){
        loai_bien_giong_nhau_cua_cam_bien = 3;
         ECHOLN("3");

        // if(Forward == true){
        //     countPulFGDistant++;
        // }else{
        //     countPulFGDistant--;
        // }

        if(daytay == true && statusStop == true){
            //ECHOLN("3");
            // loai_bien_giong_nhau_cua_cam_bien = 0;
            if(countHall1 == true){
                //cho dong co chay thuan
                countHall1 = false;
                countHall2 = false;
                countHall3 = false;
                //ECHOLN("open");
                OpenClick();
            }
            else if(countHall2 == true){
                //cho dong co chay nghich
                countHall1 = false;
                countHall2 = false;
                countHall3 = false;
                //ECHOLN("close");
                CloseClick();
            }
            else{
                countHall3 = true;
            }
        }
    }
}

void dirhallSensor4(){
    // if(daytay == true && statusStop == true && luu_trang_thai_cua_sensor_ngay_khi_dung_lai == 1){
//         ECHOLN("true3");
    //     Forward = true;
    //     luu_trang_thai_cua_sensor_ngay_khi_dung_lai = 0;
    // }else if(daytay == true && statusStop == true && luu_trang_thai_cua_sensor_ngay_khi_dung_lai == 2){
    //     ECHOLN("false3");
    //     Forward = false;
    //     luu_trang_thai_cua_sensor_ngay_khi_dung_lai = 0;
    // }

    if(loai_bien_giong_nhau_cua_cam_bien != 3){
        loai_bien_giong_nhau_cua_cam_bien = 3;
         ECHOLN("3");

        // if(Forward == true){
        //     countPulFGDistant++;
        // }else{
        //     countPulFGDistant--;
        // }

        if(daytay == true && statusStop == true){
            //ECHOLN("3");
            // loai_bien_giong_nhau_cua_cam_bien = 0;
            if(countHall1 == true){
                //cho dong co chay thuan
                countHall1 = false;
                countHall2 = false;
                countHall3 = false;
                //ECHOLN("open");
                OpenClick();
            }
            else if(countHall2 == true){
                //cho dong co chay nghich
                countHall1 = false;
                countHall2 = false;
                countHall3 = false;
                //ECHOLN("close");
                CloseClick();
            }
            else{
                countHall3 = true;
            }
        }
    }
}

void dirhallSensor5(){
    // if(daytay == true && statusStop == true && luu_trang_thai_cua_sensor_ngay_khi_dung_lai == 1){
//         ECHOLN("true3");
    //     Forward = true;
    //     luu_trang_thai_cua_sensor_ngay_khi_dung_lai = 0;
    // }else if(daytay == true && statusStop == true && luu_trang_thai_cua_sensor_ngay_khi_dung_lai == 2){
    //     ECHOLN("false3");
    //     Forward = false;
    //     luu_trang_thai_cua_sensor_ngay_khi_dung_lai = 0;
    // }

    if(loai_bien_giong_nhau_cua_cam_bien != 3){
        loai_bien_giong_nhau_cua_cam_bien = 3;
         ECHOLN("3");

        // if(Forward == true){
        //     countPulFGDistant++;
        // }else{
        //     countPulFGDistant--;
        // }

        if(daytay == true && statusStop == true){
            //ECHOLN("3");
            // loai_bien_giong_nhau_cua_cam_bien = 0;
            if(countHall1 == true){
                //cho dong co chay thuan
                countHall1 = false;
                countHall2 = false;
                countHall3 = false;
                //ECHOLN("open");
                OpenClick();
            }
            else if(countHall2 == true){
                //cho dong co chay nghich
                countHall1 = false;
                countHall2 = false;
                countHall3 = false;
                //ECHOLN("close");
                CloseClick();
            }
            else{
                countHall3 = true;
            }
        }
    }
}

void dirhallSensor6(){
    // if(daytay == true && statusStop == true && luu_trang_thai_cua_sensor_ngay_khi_dung_lai == 1){
//         ECHOLN("true3");
    //     Forward = true;
    //     luu_trang_thai_cua_sensor_ngay_khi_dung_lai = 0;
    // }else if(daytay == true && statusStop == true && luu_trang_thai_cua_sensor_ngay_khi_dung_lai == 2){
    //     ECHOLN("false3");
    //     Forward = false;
    //     luu_trang_thai_cua_sensor_ngay_khi_dung_lai = 0;
    // }

    if(loai_bien_giong_nhau_cua_cam_bien != 3){
        loai_bien_giong_nhau_cua_cam_bien = 3;
         ECHOLN("3");

        // if(Forward == true){
        //     countPulFGDistant++;
        // }else{
        //     countPulFGDistant--;
        // }

        if(daytay == true && statusStop == true){
            //ECHOLN("3");
            // loai_bien_giong_nhau_cua_cam_bien = 0;
            if(countHall1 == true){
                //cho dong co chay thuan
                countHall1 = false;
                countHall2 = false;
                countHall3 = false;
                //ECHOLN("open");
                OpenClick();
            }
            else if(countHall2 == true){
                //cho dong co chay nghich
                countHall1 = false;
                countHall2 = false;
                countHall3 = false;
                //ECHOLN("close");
                CloseClick();
            }
            else{
                countHall3 = true;
            }
        }
    }
}



void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
