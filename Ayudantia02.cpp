#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
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
    
    // vector <Mat> planes;
    // split(image,planes);
    // imshow("Blue",planes[0]);
    // imshow("Green",planes[1]);
    // imshow("Red",planes[2]);
    // Mat out;
    // merge(planes,out);
    // imshow("Out",out);
    
    imshow("Original",image);
    // imshow("RGB",rgb);
    // imshow("HSV",hsv);
    // imshow("Gray",gray);
    // imshow("YUV",yuv);

    inRange(hsv,Scalar(5,0,50),Scalar(50,255,255),Y);
    bitwise_or(image,image,bit,Y);
    // imshow("Bitwise",bit);

    GammaCorrection(image,gamma,2);
    imshow("Gamma", gamma);

    // === Filtro de Suavizado ===

    Mat Gaussian, Median, Average;

    blur(image,Average,Size(5,5));
    GaussianBlur(image,Gaussian,Size(5,5),0,0);
    medianBlur(image,Median,5);
    imshow("Average",Average);
    imshow("Gaussian",Gaussian);
    imshow("Median",Median);

    waitKey(0);
    destroyAllWindows();
}