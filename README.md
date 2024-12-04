# img_conversion
This repository contains the program for the Image Conversion Task,for getting a call for internship interview.

## Setup
```bash
mkdir -p ~/mowito_ws/src
cd mowito_ws/src
git clone https://github.com/Ashutoshss/img_conversion.git

# Before running the project, ensure the necessary setup files are sourced. Add the following line to your ~/.bashrc file to automatically source the workspace on every terminal launch:
# Source ROS2 Humble setup
source ~/mowito_ws/install/setup.bash

cd ..
colcon build --symlink-install
Source ~/.bashrc

```

## To Launch the Srcipt 
To launch the package, use the following command:
```bash
ros2 launch usb_cam_pkg image_conversion.launch.py 
```
## To Call the Service 
The package includes a service to toggle between BGR (colored image) and grayscale modes.
```bash
#for changing the image from bgr(colored image) to grayscale image
ros2 service call /change_mode std_srvs/srv/SetBool "{data: True}"

# To make it Back to bgr format
ros2 service call /change_mode std_srvs/srv/SetBool "{data: False}"
```

## For Viewing The Images use
```bash
# Select /image_converted
ros2 run rqt_image_view rqt_image_view
```
## Additionally to acces the main program file 
```bash
ros2 run usb_cam_pkg img_conversion_node
```
- This script subscribes to the topic `/image_raw` and publishes the converted images to a custom topic `/image_converted`.
- You can view the converted images on /image_converted, and any changes in the mode (BGR to grayscale or vice versa) will be reflected dynamically.
