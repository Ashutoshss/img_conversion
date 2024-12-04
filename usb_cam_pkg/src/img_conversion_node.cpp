// IMPORT
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>

#include <std_srvs/srv/set_bool.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

class ProcessNode : public rclcpp::Node     // Inheriting properties from the rclcpp library
{
public:
  // Constructor of the ProcessNode class
  ProcessNode() : Node("image_conversion_Node"), UserMode(2)    
  {
    RCLCPP_INFO(this->get_logger(), "Node created: image_conversion_Node");

    subscriber = this->create_subscription<sensor_msgs::msg::Image>("/image_raw", 10,std::bind(&ProcessNode::imageCallback, this, std::placeholders::_1));
    
    publisher = this->create_publisher<sensor_msgs::msg::Image>("/image_converted", 10);

    service = this->create_service<std_srvs::srv::SetBool>("change_mode",std::bind(&ProcessNode::changeModeCallback, this, std::placeholders::_1, std::placeholders::_2));

  }

private:
  void changeModeCallback(const std::shared_ptr<std_srvs::srv::SetBool::Request> request,
                            std::shared_ptr<std_srvs::srv::SetBool::Response> response)
    {
        if (request->data) // True for grayscale
        {
            UserMode = 1;
            response->success = true;
            response->message = "Mode changed to Grayscale";
        }
        else
        {
            UserMode = 2;
            response->success = true;
            response->message = "Mode changed to Color";
        }
        RCLCPP_INFO(this->get_logger(), "%s", response->message.c_str());
    }
  void imageCallback(const sensor_msgs::msg::Image::SharedPtr msg)
    {
        try
        {
            // Convert ROS image to OpenCV image
            cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");
            cv::Mat cv_image = cv_ptr->image;

            if (UserMode == 1) // Grayscale
            {
                cv::Mat gray_image;
                cv::cvtColor(cv_image, gray_image, cv::COLOR_BGR2GRAY);
                auto output_msg = cv_bridge::CvImage(msg->header, "mono8", gray_image).toImageMsg();
                publisher->publish(*output_msg);
            }
            else // Color
            {
                auto output_msg = cv_bridge::CvImage(msg->header, "bgr8", cv_image).toImageMsg();
                publisher->publish(*output_msg);
            }
        }
        catch (cv_bridge::Exception &e)
        {
            RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
        }
    }
    // Variables
    int UserMode; 
   
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscriber;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher;
    rclcpp::Service<std_srvs::srv::SetBool>::SharedPtr service;
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);                       // Initialize ROS 2 communication

  rclcpp::spin(std::make_shared<ProcessNode>());  // Create the node and spin it

  rclcpp::shutdown();                               // Shutdown ROS 2 communication

  return 0;
}
