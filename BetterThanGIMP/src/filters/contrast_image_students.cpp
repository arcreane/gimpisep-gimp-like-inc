#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//int main(int argc, char** argv)
//{
//    // Read the image file
//
//    Mat source = imread("van_gogh.jpg");
//    
//    // Check for failure
//
//    if (!source.data) {
//        cout << "No image data" << endl;
//        return -1;
//    }
//
//    Mat output1 = Mat::zeros(Size(source.cols, source.rows), source.type());
//    Mat output2 = Mat::zeros(Size(source.cols, source.rows), source.type());
//    Mat output3 = Mat::zeros(Size(source.cols, source.rows), source.type());
//    Mat output4 = Mat::zeros(Size(source.cols, source.rows), source.type());
//
//    //increase the contrast by 2
//
//    source.convertTo(output1, -1, 2, 0);
//
//    //increase the contrast by 4
//
//    source.convertTo(output2, -1, 4, 0);
//
//    //decrease the contrast by 0.5
//
//    source.convertTo(output3, -1, 0.5, 0);
//
//    //decrease the contrast by 0.25
//
//    source.convertTo(output3, -1, 0.25, 0);
//
//
//    //Defining window names for above images
//    
//    namedWindow("Original", WINDOW_AUTOSIZE);
//    namedWindow("Contrast *2", WINDOW_AUTOSIZE);
//    namedWindow("Contrast *4", WINDOW_AUTOSIZE);
//    namedWindow("Contrast *0.5", WINDOW_AUTOSIZE);
//    namedWindow("Contrast *0.25", WINDOW_AUTOSIZE);
//
//    //Create and open windows for above images
//    
//
//    //Show above images inside the created windows.
//
//    imshow("Original", source);
//    imshow("Contrast *2", output1);
//    imshow("Contrast *4", output2);
//    imshow("Contrast *0.5", output3);
//    imshow("Contrast *0.25", output4);
//    
//     // Wait for any key stroke
//
//    waitKey();
//
//    //destroy all open windows
//
//    destroyAllWindows();
//
//    return 0;
//}
