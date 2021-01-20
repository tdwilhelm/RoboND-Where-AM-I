#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>
#include<iostream>

// Define a global client that can request services
ros::ServiceClient client;
float position = 0.0;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    ROS_INFO_STREAM("Moving the robot to follow white ball");

    // Request velocities
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;

    // Call the ball_chaser service and pass the requested velocities
    if (!client.call(srv))
        ROS_ERROR("Failed to call service ball_chaser");    
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{
   ROS_INFO_STREAM("Proccess Image - Moving the robot to follow white ball"); 
   
   int white_pixel = 255;

    // TODO: Loop through each pixel in the image and check if there's a bright white one
    // Then, identify if this pixel falls in the left, mid, or right side of the image
    // Depending on the white ball position, call the drive_bot function and pass velocities to it
    // Request a stop when there's no white ball seen by the camera
	
    for (int i = 0; i < img.height; i++) {
        for (int j = 0; j < img.step; j++) {
                int position_index = i * img.step + j;
                if (img.data[position_index] == white_pixel && 
                img.data[position_index+1] == white_pixel &&
                img.data[position_index+2] == white_pixel) { 
             
                if((float)j/img.step <= 0.33) {  //image step 1
				                                drive_robot(0.0, 0.5);  // move rb toleft               
            	} else if ((float)j/img.step > 0.67) { //imgage step 3
				                                drive_robot(0.0, -0.5);  // move rb to right 
			    } else {                        //image step 2
				                                drive_robot(0.3, 0.0); // move rb straight
                }
			return;
		    }   
	    }   
    }
    drive_robot(0.0, 0.0);
    return;  
     
}

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}