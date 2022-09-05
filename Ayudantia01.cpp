#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


int main(int argc, char** argv){
    
    // Read the image file
    Mat image = imread("C:/Users/jaopa/Downloads/lenna.png");

    // Check for failure
    if (image.empty()) 
    {
    cout << "Could not open or find the image" << endl;
    cin.get(); //wait for any key press
    return -1;
    }

    String windowName = "The Guitar"; //Name of the window

    namedWindow(windowName); // Create a window

    imshow(windowName, image); // Show our image inside the created window.

    waitKey(0); // Wait for any keystroke in the window

    destroyWindow(windowName); //destroy the created window

    return 0;
}


/*
int main(int argc, char** argv) {

    Mat image;
    VideoCapture cap(0);
    Mat RGB;
    Mat HSV;

    if (!cap.isOpened()) {

        cout << "cannot open camera";
    }

    while (true) {

        cap >> image;

        cvtColor(image,RGB,COLOR_BGR2RGB);
        cvtColor(image,HSV,COLOR_BGR2HSV);

        imshow("Main",image);
        imshow("RGB", RGB);
        imshow("HSV",HSV);

        if(waitKey(10)!= -1){
            break;
        }
    }
    cap.release();

    return 0;
}

*/