# ESP32BLE-Jammer: An Experiment in Bluetooth Jamming

This project explores the concept of Bluetooth jamming using an ESP32 microcontroller board, three NRF24L01 transceiver modules, and other electronic components in order to make the jammer portable. The projects main goal is to understand the principles of jamming technology and its potential implications for wireless security.

## Project Motivation

The project was conceived as part of the Information Systems Security course at the Faculty of Organization and Informatics. The motivation behind this project was to gain insights into Bluetooth jamming technology and its associated security concerns. With the increasing popularity of Bluetooth devices, particularly in wireless audio headsets, it's crucial to understand the vulnerabilities and ethical considerations surrounding jamming techniques.

## Project Implementation

The project involved implementing the code from this [repository](https://github.com/lws803/BLE-jammer) onto a ESP32 board. The code utilizes three NRF24L01 transceiver modules to generate interference on the Bluetooth frequency range (2.4 GHz), more specifically the three advertising channels. The project also incorporates a red LED indicator to indicate if the device is in deep sleep and a button to toggle sleep(and jamming) on and off.

## Project Evaluation

The project was successful in providing valuable insights into Bluetooth jamming technology. While the jamming effect was not strong enough to completely disrupt Bluetooth communication, it did significantly impact the pairing process between the Taotronics Soundliberty 79 earbuds and a Pixel 7 phone. The pairing time increased from approximately 2 seconds to 5 seconds when the jamming was active.

## Project Conclusion

This project serves as a learning tool for understanding the principles and practical implications of Bluetooth jamming. While the jamming effect was limited in this instance, it highlights the potential for such techniques to interfere with wireless communications. In order to jam Bluetooth devices in a manner that would disrupt the device completely you would need a device that has both more power and a wider coverage of the Bluetooth spectrum. Doing that would also most likely disrupt the Wi-Fi connectitvity aswell. An alternative would be making the device auto connect to any devices the jammer sees but that brings its own complications and problems. The frequency hopping aspect of the Bluetooth protocol makes it so that any attempt to jam a specific channel has little to no effect, necessitating a different solution. That all being said, even with this (relatively) simple and inexpensive jammer we were able to affect the device a noticable amount and learned quite about the Bluetooth protocol, jamming and it's implications on security.

## Additional Notes

* The project utilized the ESP32 WeMos LOLIN32 microcontroller board.
* The components include three NRF24L01 transceiver modules, a red LED, a button, a 500mAh battery, and a 330ohm resistor.
* The code implementation is based on the BLE-jammer repository.
