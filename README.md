# ENGG4000-Firmware

## Setup
- Create github account and clone this repo https://help.github.com/en/github/creating-cloning-and-archiving-repositories/cloning-a-repository
- Learn how to work with git https://developer.ibm.com/tutorials/d-learn-workings-git/
- Install Psoc Creator https://www.cypress.com/products/psoc-creator-integrated-design-environment-ide
- Follow the setup instructions in the videos at https://www.cypress.com/training/psoc-101-video-tutorial-series-how-use-arm-cortex-m4-based-psoc-6 (Chapter 1 will be helpful for setting up the environment, Chapter 2 will be helpful for learning about all the features of the chip, and Chapter 3 gives a deep-dive into BLE)

## Wearable
### Current Functionality
- Configured BLE module:
 - Advertises as "Wearable"
 - Contains 2 services:
    - IMU:
      - 2 Characteristics that have the acceleration (x,y,z) and gyroscope data (x,y,z) 
      - Notification functionality for both characteristics
    - Force:
      - 1 Characteristic with all force sensor data
      - Notification functionality for both characteristics
      
- LED incdicator:
  - Off when board is off
  - Blinks red every 1 seconds while disconnected
  - Blinks green every 5 seconds while connected
  
### Functionality to Implement
- Analog to Digital convertor (ADC):
  - Configure output pins and sampling rate
    - Sampling rate can potentially be controlled by a BLE characteristic?
  - Perform any data manipulation before updating the value of the characteristic and sending a BLE notification
  
- Charging recognition
  - Prohibit functionality while charging
  
- Battery Level
  - Can add a BLE service that contains the battery level remaining (percentage) to be displayed by the receiving device
  
## Mobile Application
### Current Functionality
- Graphing:
  - Displays data from randomly generated data points (8 sources currently)
  
- BLE:
  - Can print bluetooth devices to console
### Functionality to Implement
- Graphing:
  - Allow to switch between graphing force and IMU data
  - Choose from a range of times/dates to display data
  
- BLE:
  - Connect to wearable
  - Subscribe to wearable notifications
  - Connect to HMI
  - Send data to HMI
  
- Data Storage:
  - Store data locally
  - Store data in a cloud database
  
- Data Classification:
  - Integrate classifier into mobile application 
  
## HMI
  - Can potentially implement BLE mouse functionality directly onto the wearable and circumvent having to connect to a mobile device, example BLE HID mouse project ( https://www.cypress.com/documentation/code-examples/ce215122-ble-hid-mouse-psoc-6-ble )
