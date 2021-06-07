#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//int main(int argc, char** argv)
//{
//    // Read the image file
//    Mat image = imread("van_gogh.jpg");
//
//    // Check for failure
//    if (!image.data) {
//        cout << "An error occured while loading the image!" << endl;
//        return -1;
//    }
//
//    //Blur the image with 3x3 kernel
//    Mat output3Kernel;
//    blur(image, output3Kernel, Size(3,3), Point(-1, -1), BORDER_DEFAULT);
//
//    //Blur the image with 5x5 kernel
//    Mat output5Kernel;
//    blur(image, output5Kernel, Size(5, 5), Point(-1, -1), BORDER_DEFAULT);
//
//    //Define names of the windows
//    String inputWindowName = "Input";
//    String output3KernelWindowName = "Output 3x3 Kernel";
//    String output5KernelWindowName = "Output 5x5 Kernel";
//    
//
//    // Create windows with above names
//    namedWindow(inputWindowName, WINDOW_AUTOSIZE);
//    namedWindow(output3KernelWindowName, WINDOW_AUTOSIZE);
//    namedWindow(output5KernelWindowName, WINDOW_AUTOSIZE);
//
//    // Show our images inside the created windows.
//    imshow(inputWindowName, image);
//    imshow(output3KernelWindowName, output3Kernel);
//    imshow(output5KernelWindowName, output5Kernel);
//
//    // Wait for any keystroke in the window
//    waitKey();
//
//    //destroy all opened windows
//    destroyAllWindows();
//
//}
