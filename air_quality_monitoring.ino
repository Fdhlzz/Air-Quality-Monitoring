//pemanggilan token blynk
#define BLYNK_AUTH_TOKEN "" //masukkan token sesuai yang ada di website blynk
#define BLYNK_TEMPLATE_ID "" //masukkan id sesuai yang ada di website blynk
#define BLYNK_DEVICE_NAME "" //masukkan nama sesuai yang ada di website blynk

//pemanggilan library
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <MQ135.h>

//define wifi dan pass
const char* ssid = ""; //masukkan nama  wifi
const char* pass = ""; //masukkan pass wifi

char auth[] = BLYNK_AUTH_TOKEN; //token blynk

int analogSensor = A0; //pin analog sensor MQ135
int buzzer = D1; //pin buzzer

void alarmBuzzer(){
    for (int i = 0; i < 3; i++){
        tone(buzzer, 1000);
        delay(500);
        noTone(buzzer);
        delay(500)
    }
    delay(2000);
}

void setup(){
    Serial.begin(115200); //memulai di serial monitor dengan baudrate 115200
    Blynk.begin(auth, ssid, pass); //memulai blynk

    Serial.println("Connecting to WIFI...");
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Wifi Connected...");
}

void loop(){
    Blynk.run(); //memulai blynk

    int gasValue = analogRead(analogSensor);
    pinMode(buzzer, OUTPUT);
    alarmBuzzer();

    Blynk.virtualWrite(V1, gasValue);
    Serial.println("Nilai Gas :");
    Serial.print(gasValue);
    delay(1000);

    if (gasValue > 500){
        alarmBuzzer();
    }
    else{
        noTone(buzzer);
    }
}