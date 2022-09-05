#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void GammaCorrection(Mat& src ,Mat& dst ,float fGamma){
    unsigned char lut [256];
    for(int i = 0; i < 256; i++ ){
        lut [i] = saturate_cast<uchar>(pow((float)(i/255.0), fGamma) * 255.0f );
    }
    dst = src.clone();
    
    const int channels = dst.channels( );
    switch(channels) {
        case 1 :{
            MatIterator_<uchar> it , end;
            for(it = dst.begin<uchar>(), end = dst.end<uchar>(); it != end; it++)
                * it = lut [( * it ) ];
            break;
        }
        case 3 : {
            MatIterator_<Vec3b> it , end;
            for(it = dst.begin<Vec3b>(), end = dst.end<Vec3b>(); it != end; it++){
               (*it)[0] = lut[((*it)[0])];
               (*it)[1] = lut[((*it)[1])];
               (*it)[2] = lut[((*it)[2])];
            }
        break;
        }
    }
}

int main(int, char**){

    // === Manejo de Colores ===

    Mat image = imread("C:/Ayudantia-PDI/AyudantiaPDI2022-2/Images/Image01.jpg");
    //Mat image(600, 800, CV_8UC3, Scalar(120,120,120));
    
    int cols = image.cols, rows = image.rows;
    resize(image,image,Size(cols/4,rows/4));

    Mat rgb, hsv, gray, yuv, Y, bit, gamma;
    
    cvtColor(image,rgb,COLOR_BGR2RGB);
    cvtColor(image,hsv,COLOR_BGR2HSV);
    cvtColor(image,gray,COLOR_BGR2GRAY);
    cvtColor(image,yuv,COLOR_BGR2YUV);
    
    imshow("Original",image);
    imshow("RGB",rgb);
    imshow("HSV",hsv);
    imshow("Gray",gray);
    imshow("YUV",yuv);

    inRange(hsv,Scalar(5,0,50),Scalar(50,255,255),Y);
    bitwise_or(image,image,bit,Y);
    // imshow("Bitwise",bit);

    GammaCorrection(image,gamma,2);
    imshow("Gamma", gamma);

    // === Filtro de Suavizado ===

    Mat Gaussian, Median, Average;

    blur(gray,Average,Size(5,5));
    GaussianBlur(gray,Gaussian,Size(5,5),0);
    medianBlur(gray,Median,5);
    imshow("Average",Average);
    imshow("Gaussian",Gaussian);
    imshow("Median",Median);


    // === Deteccion de Bordes ===

    Mat SobelX, SobelY, SobelXY, edges;

    Sobel(Gaussian, SobelX, CV_64F, 1,0,5);
    Sobel(Gaussian, SobelY, CV_64F, 0,1,5);
    Sobel(Gaussian, SobelXY, CV_64F, 1,1,5);
    imshow("X",SobelX);
    imshow("Y",SobelY);
    imshow("XY",SobelXY);

    Canny(Gaussian, edges, 100, 200 , 3);
    imshow("Canny",edges);

    waitKey(0); 
    destroyAllWindows();
}