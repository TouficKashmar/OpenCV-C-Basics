#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

int main(int argc, char *argv[])
{
    Mat img_blur, src_gray, dst, abs_dst;
    int kernel_size = 3;
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;

    //loading and displaying the image:
    Mat img = imread("bird.jpg", cv::IMREAD_COLOR);
    if(img.empty())
       return -1;
    namedWindow("bird image", WINDOW_AUTOSIZE );
    imshow("bird image", img);
    waitKey(0);

    // Blur the image for better edge detection using gaussianBlur -> removes noise
    GaussianBlur( img, img_blur, Size(3, 3), 0, 0, BORDER_DEFAULT );
    imwrite("blurred_bird_image.jpg", img_blur);
    // Convert image to graycsale
    cvtColor( img_blur, src_gray, COLOR_BGR2GRAY );
    imwrite("grayscale_blurred_bird_image.jpg", src_gray);

    //Detect the edges of the image using the Laplacian operator Laplace().
    Laplacian( src_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT );
    // converting back to CV_8U
    convertScaleAbs( dst, abs_dst );

    //Display the resulting Laplacian edge map.
    imshow( "Edges displayed using Laplace", abs_dst );
    imwrite("bird image with edges displayed using Laplace.jpg", abs_dst);
    waitKey(0);


    //Sobel

    //Detect the edges of the image using the Sobel operator Sobel().
    //detects edges that are marked by sudden changes in pixel intensity
    //edges can be detected in areas where the gradient is higher than a particular threshold value:
    //A sudden change in the derivative will reveal a change in the pixel intensity
    //the derivative can be approximated using a 3×3 kernel one for sudden changes in each X and Y directions.
    //When these kernels are convolved with the original image, you get a ‘Sobel edge image’.
    // Sobel edge detection
    Mat sobelx, sobely, sobelxy;
    Sobel(img_blur, sobelx, CV_64F, 1, 0, 5);
    Sobel(img_blur, sobely, CV_64F, 0, 1, 5);
    Sobel(img_blur, sobelxy, CV_64F, 1, 1, 5);

    //Display the resulting Sobel edge map
    imshow("Sobel X", sobelx);
    imwrite("bird image with edges displayed in the X direction using sobelx.jpg", sobelx);
    waitKey(0);
    imshow("Sobel Y", sobely);
    imwrite("bird image with edges displayed in the Y direction using sobely.jpg", sobely);
    waitKey(0);
    imshow("Sobel XY using Sobel() function", sobelxy);
    imwrite("bird image with edges detected using sobel in both X,Y directions.jpg", sobelxy);
    waitKey(0);

    //If we use only the Vertical Kernel, the convolution yields a Sobel image, with edges enhanced in the X-direction
    //Using the Horizontal Kernel yields a Sobel image, with edges enhanced in the Y-direction.

    //Canny:
    //Detect the edges of the image using the Canny edge detector Canny().
    Mat edges;
    Canny(img_blur, edges, 100, 200, 3, false);

    //Display the resulting Canny edge map.
    imshow("Canny edge detection", edges);
    imwrite("bird image with edges detected using canny.jpg", edges);
    waitKey(0);

    destroyAllWindows();
    return 0;
}



