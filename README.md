# img_conversion
This file contain program file for the task submission for the internship interview.

## Setup
```bash
mkdir -p ~/mowito_ws/src
cd mowito_ws/src
git clone https://github.com/Ashutoshss/img_conversion.git
cd ..
colcon build --symlink-install

# Before running the project, ensure you have sourced the necessary setup files in your terminal. You can add the following lines to your `~/.bashrc` file:
# Source ROS2 Humble setup
source /opt/ros/humble/setup.bash
source ~/mowito_ws/install/setup.bash

# Source colcon_cd function
source /usr/share/colcon_cd/function/colcon_cd.sh
export _colcon_cd_root=/opt/ros/humble/
```

## To Launch the Srcipt 
use 
```bash
ros2 launch usb_cam_pkg image_conversion.launch.py 
```
## To Call the Service 
use 
```bash
#for changing the image from bgr(colored image) to grayscale image
ros2 service call /change_mode std_srvs/srv/SetBool "{data: True}"

# To make it Back to bgr format
ros2 service call /change_mode std_srvs/srv/SetBool "{data: False}"
```

## For Viewing The Images use
```bash
ros2 run rqt_image_view rqt_image_view
```
