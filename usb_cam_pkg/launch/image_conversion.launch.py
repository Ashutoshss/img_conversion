from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        
        # This Driver node connect to the machine camera hardware and then publish this the image on topic /
        #     /camera_info
        #     /image_raw
        #     /image_raw/compressed
        #     /image_raw/compressedDepth
        #     /image_raw/theora

        Node(
            package='usb_cam',
            executable='usb_cam_node_exe',
            name='usb_cam_node',
            parameters=[{'video_device': '/dev/video0'}]
        ),

        # my image conversion node
        Node(
            package='usb_cam_pkg',
            executable='img_conversion_node',
            name='img_conversion_node',
            parameters=[
                {'input_image_topic': '/image_raw'},
                {'output_image_topic': '/converted_image'}
            ]
        ),
    ])

