Undergraduate Research Project: Augmented Reality on Wearable Devices 
Vision component: Perform feature extraction on live camera feed with Speeded Up Robust Features (SURF) and data compression with reasonable compute time.

Features will be transmitted to cloud for machine learning and overlay virtual objects in graphics component later on.

Dependencies:
OpenCV
CMake

Files:
project.cpp: combine compress.cpp with original surf.cpp, compression done on every even number frame. Able to modify the detector and extractor algorithm through variable Ptr<FeatureDetector> detector and Ptr<DescriptorExtractor> extractor respectively.

compress_boost.cpp: [reference only] compression using boost library

compress.cpp: [reference only] compress test image

surf.cpp: [reference only] original file reading from camera, detect and extract datapoint from OpenCV surf algorithm 