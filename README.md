# ENGG4000-Firmware

## Setup
- Create github account and clone this repo (instructions: https://help.github.com/en/github/creating-cloning-and-archiving-repositories/cloning-a-repository)
- Learn how to work with git 
  - Conceptual explanation of Git: https://developer.ibm.com/tutorials/d-learn-workings-git/
  - How to work with Github: https://guides.github.com/activities/hello-world/
- Install Psoc Creator https://www.cypress.com/products/psoc-creator-integrated-design-environment-ide
- Follow the setup instructions in the videos at https://www.cypress.com/training/psoc-101-video-tutorial-series-how-use-arm-cortex-m4-based-psoc-6 (Chapter 1 will be helpful for setting up the environment, Chapter 2 will be helpful for learning about all the features of the chip, and Chapter 3 gives a deep-dive into BLE)

## Wearable
### Current Functionality
- Configured BLE module:
 - Advertises as "Wearable"
 - Contains 2 services:
    - IMU:
      - Characteristic with acceleration (x,y,z) and gyroscope data (x,y,z) 
      - Notification functionality for characteristic
    - Force:
      - 1 Characteristic with all force sensor data
      - Notification functionality for characteristic
      
- LED incdicator:
  - Off when board is off
  - Blinks red every 1 seconds while disconnected
  - Blinks green every 5 seconds while connected
  
- Analog to Digital convertor (ADC):
  - Read values from 8 input ports
  - Average multiple samples within the ADC
  - Sample at a rate of ####
  
- Battery Level
  - Has a Service/Characteristic that contains the current battery level of the device

### Functionality to Implement
- I2C interface configuration for communication with IMU

- Charging recognition
  - Prohibit functionality while charging
  
- Battery Level
  - Can add a BLE service that contains the battery level remaining (percentage) to be displayed by the receiving device
  
## HMI
  - Can potentially implement BLE mouse functionality directly onto the wearable and circumvent having to connect to a mobile device, example BLE HID mouse project ( https://www.cypress.com/documentation/code-examples/ce215122-ble-hid-mouse-psoc-6-ble )