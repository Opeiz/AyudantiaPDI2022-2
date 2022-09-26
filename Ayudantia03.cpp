#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


int main(int, char**){

    // === Manejo de Colores ===

    Mat image = imread("C:/Ayudantia-PDI/AyudantiaPDI2022-2/Images/Image08.jpg");
    //Mat image(600, 800, CV_8UC3, Scalar(120,120,120));
    
    int cols = image.cols, rows = image.rows;
    resize(image,image,Size(cols/4,rows/4));

    Mat gray;
    cvtColor(image,gray,COLOR_BGR2GRAY);
    
    // imshow("Original",image);

    // === Filtro de Suavizado ===

    Mat Gaussian, Median;
    int x = 21; // Importante siempre impar, porque??
    GaussianBlur(gray,Gaussian,Size(x,x),BORDER_DEFAULT);
    /* Types:
        BORDER_DEFAULT
        BORDER_REPLICATE
        BORDER_REFLECT
        BORDER_REFLECT_101
        BORDER_TRANSPARENT
        BORDER_CONSTANT
    */
    medianBlur(gray,Median,x);

    // imshow("Gaussian",Gaussian);
    // imshow("Median",Median);

    // === Threshold ===

    Mat th1, th2;

    threshold(gray,th1, 125,255,3);
    threshold(gray,th2, 125,255,4);

    /* Types:
        0 = Binario
        1 = Binario Invertido
        2 = Truncado
        3 = A Cero
        4 = A Cero Invertido
    */
    
    // imshow("Threshold 1", th1);
    // imshow("Threshold 2", th2);

    // === Erosion y Dilatacion ===

    VideoCapture cap ( 0 ) ;
    Mat hsv , frame , hsv2, hsv3;

    while ( true ) {
        cap >> frame ;

        // imshow("Original", frame) ;
        
        cvtColor(frame, frame, COLOR_BGR2HSV) ;
        inRange(frame, Scalar(20, 0, 50), Scalar(40, 255, 255), hsv); // Amarillo
        erode(hsv, hsv2, getStructuringElement(MORPH_RECT, Size(7, 7)));
        dilate(hsv2, hsv3, getStructuringElement(MORPH_RECT, Size(7, 7)));
        // imshow("Hsv", hsv) ;
        // imshow("HSV2", hsv2);
        // imshow("HSV3", hsv3);
        if(waitKey(10) == 27){
            break;
        }
    }
    return 0 ;

    // waitKey(0); 
    destroyAllWindows();
}