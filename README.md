# img_conversion
## OverView
This file contain program file for the task submission 

## Setup
Before running the project, ensure you have sourced the necessary setup files in your terminal. You can add the following lines to your `~/.bashrc` file:

```bash
# Source ROS2 Humble setup
source /opt/ros/humble/setup.bash
source ~/ros2_ws/install/setup.bash

# Source colcon_cd function
source /usr/share/colcon_cd/function/colcon_cd.sh
export _colcon_cd_root=/opt/ros/humble/
```



## To Launch the Srcipt 
use 
```
ros2 launch usb_cam_pkg image_conversion.launch.py 
```
## To Call the Service 
use 
```
#for changing the image from bgr(colored image) to grayscale image
ros2 service call /change_mode std_srvs/srv/SetBool "{data: True}"

# To make it Back to bgr format
ros2 service call /change_mode std_srvs/srv/SetBool "{data: False}"


```
