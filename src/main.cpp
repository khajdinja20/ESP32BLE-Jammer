/*
 * Arduino nRF24L01 Noise Gen
 *
 * by Wilson
 *
 * Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
 */
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN_NRF1 32
#define CSN_PIN_NRF1 33
#define CE_PIN_NRF2 25
#define CSN_PIN_NRF2 26
#define CE_PIN_NRF3 12
#define CSN_PIN_NRF3 13

RF24 radio(CE_PIN_NRF1, CSN_PIN_NRF1); // CE, CSN
RF24 radio2(CE_PIN_NRF2, CSN_PIN_NRF2);
RF24 radio3(CE_PIN_NRF3, CSN_PIN_NRF3);

void setup()
{
    Serial.begin(115200);
    Serial.println("Setup starting!");
    radio.begin();
    radio2.begin();
    radio3.begin();
    radio.powerDown();
    radio2.powerDown();
    radio3.powerDown();
    delay(1000);

    Serial.println("Module 1 setup start");
    radio.powerUp();
    radio.setAutoAck(false); // Very important setting
    radio.setPALevel(RF24_PA_HIGH);
    radio.setDataRate(RF24_2MBPS);
    radio.stopListening();
    radio.setChannel(80);
    delay(1000);

    Serial.println("Module 2 setup start");
    radio2.powerUp();
    radio2.setAutoAck(false);
    radio2.setPALevel(RF24_PA_HIGH);
    radio2.setDataRate(RF24_2MBPS);
    radio2.stopListening();
    radio2.setChannel(26);
    delay(1000);

    Serial.println("Module 3 setup start");
    radio3.powerUp();
    radio3.setAutoAck(false);
    radio3.setPALevel(RF24_PA_HIGH);
    radio3.setDataRate(RF24_2MBPS);
    radio3.stopListening();
    radio3.setChannel(2);
    delay(1000);

    Serial.println("Setup finished.");
}

void loop()
{
    byte text = 255; // just some random string
    radio.writeFast(&text, sizeof(text));
    radio2.writeFast(&text, sizeof(text));
    radio3.writeFast(&text, sizeof(text));
}
