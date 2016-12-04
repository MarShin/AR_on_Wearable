#include <string>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <zlib.h>

#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/** Compress a STL string using zlib with given compression level and return
  * the binary data. */
string compress_string(const std::string& str,
                            int compressionlevel = Z_BEST_COMPRESSION)
{
    z_stream zs;                        // z_stream is zlib's control structure
    memset(&zs, 0, sizeof(zs));

    if (deflateInit(&zs, compressionlevel) != Z_OK)
        throw(std::runtime_error("deflateInit failed while compressing."));

    zs.next_in = (Bytef*)str.data();
    zs.avail_in = str.size();           // set the z_stream's input

    int ret;
    char outbuffer[32768];
    string outstring;

    // retrieve the compressed bytes blockwise
    do {
        zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
        zs.avail_out = sizeof(outbuffer);

        ret = deflate(&zs, Z_FINISH);

        if (outstring.size() < zs.total_out) {
            // append the block to the output string
            outstring.append(outbuffer,
                             zs.total_out - outstring.size());
        }
    } while (ret == Z_OK);

    deflateEnd(&zs);

    if (ret != Z_STREAM_END) {          // an error occurred that was not EOF
        std::ostringstream oss;
        oss << "Exception during zlib compression: (" << ret << ") " << zs.msg;
        throw(std::runtime_error(oss.str()));
    }

    return outstring;
}

/** Decompress an STL string using zlib and return the original data. */
string decompress_string(const std::string& str)
{
    z_stream zs;                        // z_stream is zlib's control structure
    memset(&zs, 0, sizeof(zs));

    if (inflateInit(&zs) != Z_OK)
        throw(std::runtime_error("inflateInit failed while decompressing."));

    zs.next_in = (Bytef*)str.data();
    zs.avail_in = str.size();

    int ret;
    char outbuffer[32768];
    std::string outstring;

    // get the decompressed bytes blockwise using repeated calls to inflate
    do {
        zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
        zs.avail_out = sizeof(outbuffer);

        ret = inflate(&zs, 0);

        if (outstring.size() < zs.total_out) {
            outstring.append(outbuffer,
                             zs.total_out - outstring.size());
        }

    } while (ret == Z_OK);

    inflateEnd(&zs);

    if (ret != Z_STREAM_END) {          // an error occurred that was not EOF
        std::ostringstream oss;
        oss << "Exception during zlib decompression: (" << ret << ") "
            << zs.msg;
        throw(std::runtime_error(oss.str()));
    }

    return outstring;
}


int main(int argc, char* argv[])
{
    //-- Step 1: Detect the keypoints using Detector chosen with constructor with deafult parameter
    //both ways of declaration works, new object can specify the hessian threshold
    Ptr<FeatureDetector> detector = FeatureDetector::create("STAR"); 
    //Ptr<FeatureDetector> detector = Ptr<FeatureDetector>( new SURF(500) );

    // FOR using a prarticular detection algorithm, configure parameter for best performance
        //int minHessian = 500;
        //SurfFeatureDetector detector(minHessian);
        //SurfDescriptorExtractor extractor;

    vector<KeyPoint> keypoints_1;
    int frame_num = 1;
    VideoCapture cap;
    Mat frame;
    Mat img_keypoints_1,img_descriptor_1;
    
    Ptr<DescriptorExtractor> extractor = DescriptorExtractor::create("BRIEF");

   
    if(!cap.open(0))
        return 0;

    clock_t tStart;
    stringstream ss;
    string allinput;
    // start capturing  
    for(;;frame_num++){
        cap >> frame;
        tStart = clock();

        if( frame.empty() ) break; // end of video stream
        detector->detect(frame, keypoints_1 );
        drawKeypoints( frame, keypoints_1, img_keypoints_1, Scalar::all(-1), DrawMatchesFlags::DEFAULT );
        imshow("project", img_keypoints_1);

         //-- Step 2: Calculate descriptors (feature vectors)
        extractor->compute( frame, keypoints_1, img_descriptor_1 );
        if (frame_num%2 == 0) {
            // Read descriptor image
            Size size = img_descriptor_1.size();
            int total = size.width * size.height * img_descriptor_1.channels();
            cout<<"Compressing descriptor number" <<frame_num<<endl;
            cout << "Descriptor size = " << total << endl;
            
            ss<<img_descriptor_1;
            allinput = ss.str();

            //compression
            string cstr = compress_string(allinput);
            cout<<"Time taken:"<<(double)(clock() - tStart)/CLOCKS_PER_SEC<<endl; 
            cerr << "Deflated data: "
                      << allinput.size() << " -> " << cstr.size()
                      << " (" << std::setprecision(1) << std::fixed
                      << ( (1.0 - (float)cstr.size() / (float)allinput.size()) * 100.0)
                      << "% saved).\n";
        }

        if( waitKey(1) == 27 ) break; // stop capturing by pressing ESC
    }
    // the camera will be closed automatically upon exit
    //cap.close();

    //decompression
    //     std::string dstr = decompress_string( cstr );
    //     std::cout<<"decompress begins"<<std::endl;
    //     std::cerr << "Inflated data: "
    //               << cstr.size() << " -> " << dstr.size()
    //               << " (" << std::setprecision(1) << std::fixed
    //               << ( ((float)dstr.size() / (float)cstr.size() - 1.0) * 100.0 )
    //               << "% increase).\n";

    //     std::cout << dstr;
}