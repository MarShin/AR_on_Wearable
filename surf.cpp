#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

// /** @function main */
// int main( int argc, char** argv ){
  
//   ofstream myfile;
//   myfile.open ("output.txt");
//  // Mat img_1 = imread( "/Users/MartinShin/code/UROP/opencv_1/opencv_1/photo1.jpg", IMREAD_GRAYSCALE );

//   //-- Step 1: Detect the keypoints using SURF Detector
//     int minHessian = 900;
//     int frame_num = 1;
//     SurfFeatureDetector detector(minHessian);
//     std::vector<KeyPoint> keypoints_1;

//     VideoCapture cap;
//     Mat frame;
//     Mat img_keypoints_1,img_descriptor_1;
//     //SurfDescriptorExtractor extractor;

//     Ptr<DescriptorExtractor> extractor = DescriptorExtractor::create("SURF");

//    // FileStorage file = new FileStorage("/Users/MartinShin/code/UROP/opencv_1/opencv_1/output.txt",1);
//     if(!cap.open(0))
//         return 0;

//     clock_t tStart = clock();
//     // start capturing  
//     for(;;frame_num++){
//         cap >> frame;
        
//         if( frame.empty() ) break; // end of video stream
//         detector.detect(frame, keypoints_1 );
//         drawKeypoints( frame, keypoints_1, img_keypoints_1, Scalar::all(-1), DrawMatchesFlags::DEFAULT );
//         imshow("surf", img_keypoints_1);

//          //-- Step 2: Calculate descriptors (feature vectors)
//         extractor->compute( frame, keypoints_1, img_descriptor_1 );
//         //cout<<"Extrator: "<<extractor->write(file)<<endl;
//         //print for even frame print mat img_kypoints_1
//         if (frame_num%2 == 0) 
//           myfile<<"Frame "<<frame_num<<": "<<endl<<" "<<img_descriptor_1<<endl;
        

//         if( waitKey(1) == 27 ) break; // stop capturing by pressing ESC 
//     }
//     // the camera will be closed automatically upon exit
//     // cap.close();
//     myfile<<"Time taken:"<<(double)(clock() - tStart)/CLOCKS_PER_SEC<<endl;
//     myfile<<"Last frame is "<<frame_num<<endl;
//     myfile.close();
//     return 0;
// }
////////////////////////////////////////////////////////////////////////////////////////////////////////
// class surf2{
// public:
// 	// Serialize a cv::Mat to a stringstream
// 	stringstream serialize(Mat input)
// 	{
// 	    // We will need to also serialize the width, height, type and size of the matrix
// 	    int width = input.cols;
// 	    int height = input.rows;
// 	    int type = input.type();
// 	    size_t size = input.total() * input.elemSize();

// 	    // Initialize a stringstream and write the data
// 	    stringstream ss;
// 	    ss.write((char*)(&width), sizeof(int));
// 	    ss.write((char*)(&height), sizeof(int));
// 	    ss.write((char*)(&type), sizeof(int));
// 	    ss.write((char*)(&size), sizeof(size_t));

// 	    // Write the whole image data
// 	    ss.write((char*)input.data, size);

// 	    return ss;
// 	}

// 	// Deserialize a Mat from a stringstream
// 	Mat deserialize(stringstream& input)
// 	{
// 	    // The data we need to deserialize
// 	    int width = 0;
// 	    int height = 0;
// 	    int type = 0;
// 	    size_t size = 0;

// 	    // Read the width, height, type and size of the buffer
// 	    input.read((char*)(&width), sizeof(int));
// 	    input.read((char*)(&height), sizeof(int));
// 	    input.read((char*)(&type), sizeof(int));
// 	    input.read((char*)(&size), sizeof(size_t));

// 	    // Allocate a buffer for the pixels
// 	    char* data = new char[size];
// 	    // Read the pixels from the stringstream
// 	    input.read(data, size);

// 	    // Construct the image (clone it so that it won't need our buffer anymore)
// 	    Mat m = Mat(height, width, type, data).clone();

// 	    // Delete our buffer
// 	    delete[]data;

// 	    // Return the matrix
// 	    return m;
// 	}
// };



