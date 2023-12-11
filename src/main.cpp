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

// Needed for portability
const int ledPin = 22;
const int buttonPin = 27;

RTC_DATA_ATTR int bootCount = 0;

int ledState = LOW;
int buttonState = LOW;
int lastButtonState;

void print_wakeup_reason()
{
    esp_sleep_wakeup_cause_t wakeup_reason;

    wakeup_reason = esp_sleep_get_wakeup_cause();

    switch (wakeup_reason)
    {
    case ESP_SLEEP_WAKEUP_EXT0:
        Serial.println("Wakeup caused by external signal using RTC_IO");
        break;
    case ESP_SLEEP_WAKEUP_EXT1:
        Serial.println("Wakeup caused by external signal using RTC_CNTL");
        break;
    case ESP_SLEEP_WAKEUP_TIMER:
        Serial.println("Wakeup caused by timer");
        break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD:
        Serial.println("Wakeup caused by touchpad");
        break;
    case ESP_SLEEP_WAKEUP_ULP:
        Serial.println("Wakeup caused by ULP program");
        break;
    default:
        Serial.printf("Wakeup was not caused by deep sleep: %d\n", wakeup_reason);
        break;
    }
}

void setup()
{
    Serial.begin(115200);
    delay(500);

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

    Serial.println("Portability pack setup start");
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(ledPin, OUTPUT);

    digitalWrite(ledPin, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);

    Serial.println("Setup finished.");

    ++bootCount;
    Serial.println("Boot number: " + String(bootCount));
    print_wakeup_reason();
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_27, HIGH);

    digitalWrite(ledPin, HIGH);
}

void loop()
{
    lastButtonState = buttonState;
    buttonState = digitalRead(buttonPin);
    if (lastButtonState == HIGH && buttonState == LOW)
    {
        Serial.println("Button pressed");
        Serial.print("Led state:");
        Serial.println(ledState);
        ledState = !ledState;
        digitalWrite(ledPin, ledState);
        Serial.println("Going to sleep");
        esp_deep_sleep_start();
    }
    byte text = 255; // just some random string
    radio.writeFast(&text, sizeof(text));
    radio2.writeFast(&text, sizeof(text));
    radio3.writeFast(&text, sizeof(text));
}
