#include <iostream>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

using namespace cv;
using namespace std;

int main(){
    int sobel_x[3][3] = {1,0,-1,2,0,-2,1,0,-1};
    int sobel_y[3][3] = {1,2,1,0,0,0,-1,-2,-1};
    IplImage* image;
    IplImage* clone;
    IplImage* result_x;
    IplImage* result_y;
    image = cvLoadImage("chessboard.bmp");
    if(!image){
        return 1;
    }
    int width = image->width;
    int height= image->height;
    int sum_x,sum_y;

    clone = cvCreateImage(cvSize(width,height),IPL_DEPTH_8U,1);
    result_x = cvCreateImage(cvSize(width,height),IPL_DEPTH_8U,1);
    result_y = cvCreateImage(cvSize(width,height),IPL_DEPTH_8U,1);
    
    //convert to gray image
    cvCvtColor(image,clone,CV_BGR2GRAY);

    for (int i =1; i < height-2 ; i++ )
    {
        
        for( int j = 1; j< width-2 ; j++ )
        {
            sum_x = 0;
            sum_y = 0;
            for(int p = 0;p<3;p++)
            {
                for (int q = 0; q < 3 ; q++)
                {
                    sum_x += ((uchar*)(clone->imageData + (i+p)*clone->widthStep ))[ j + q ] * sobel_x[q][p];
                    sum_y += ((uchar*)(clone->imageData + (i+p)*clone->widthStep ))[ j + q ] * sobel_y[q][p];
                }
            }
            //eliminate some noise on image        
            sum_x = abs(sum_x);
            sum_x = sum_x > 255 ? 255 : sum_x;
            sum_x = sum_x < 180 ? 0 : sum_x;

            sum_y = abs(sum_y);
            sum_y = sum_y > 255 ? 255 : sum_y;
            sum_y = sum_y < 180 ? 0 : sum_y;
            
            ((uchar*)( result_x->imageData + i * result_x->widthStep))[ j ] = sum_x;
            ((uchar*)( result_y->imageData + i * result_y->widthStep))[ j ] = sum_y;
        }
    }
    
    cvNamedWindow("sobel_x",0);    
    cvShowImage("sobel_x",result_x);
    cvNamedWindow("sobel_y",0);    
    cvShowImage("sobel_y",result_y);
    waitKey(0);
    cvReleaseImage(&image);
    cvReleaseImage(&clone);
    cvReleaseImage(&result_x);
    cvReleaseImage(&result_y);
    return 0;
}
