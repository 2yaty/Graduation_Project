
# Safe Drive Pro (AI Branch)

### The Safe Drive Pro System comes equipped with four important features, which are as follows:

    1. Driver Monitoring and Reporting System (DMRS)
    2. Traffic Sign Recognition System (TSRS)
    3. Lane Departure Warning System (LDWS)
    4. Forward Collision Warning System

### To effectively use these features, the following AI models are must be installed:

    1. Random Forest model for DMRS (add links to the models in the repo)
    2. Pre-trained YOLOv8 model for TSRS
    3. LDWS is still under investigation.





## Environment Setup

To run this project, you will need to Setup the following file:

` pip install -r requirments.txt
`

Tools:
- VS code or any python IDE.



## How to Use:

for the hardware you need:
- raspberry Pi4
- Raspberry camera at least 5MP.
- MPU6050 connected to the stm32f401.

for the software:
- you can test the application on your labtop by connecting to the stm and TTL by running this file >>> 

- you can test the application on the raspberry by running this file >>>
  ## Running AI Model on Raspberry Pi

This guide will walk you through the steps required to run an AI model on a Raspberry Pi.

### Steps

#### 1. Download and Install Raspberry Pi OS

1. Download and install [Raspberry Pi Imager](https://www.raspberrypi.org/software/) on your computer.

2. Insert your SD card into your computer.

3. Open Raspberry Pi Imager and follow these steps:

##### Step 1: Choose OS
Click on "CHOOSE OS" and select "Raspberry Pi OS (other)".

##### Step 2: Select Raspberry Pi OS 64-bit
Select "Raspberry Pi OS (64-bit)" from the list.

##### Step 3: Choose SD Card
Click on "CHOOSE SD CARD" and select your SD card from the list.

##### Step 4: Write the OS
Click on "WRITE" to start downloading and burning the OS onto your SD card.

4. Once the process is complete, insert the SD card into your Raspberry Pi and power it on.

#### 2. Move AI Models to Raspberry Pi

Use the `scp` tool to transfer your AI models to the Raspberry Pi. Replace `username`, `hostname`, and `/path/to/model` with your specific details.

scp /path/to/model username@hostname:/path/to/destination

