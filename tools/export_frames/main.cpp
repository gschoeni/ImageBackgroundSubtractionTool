//opencv
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <opencv2/opencv.hpp>
//C
#include <stdio.h>
#include <unistd.h>
//C++
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <thread>

using namespace cv;
using namespace std;


// GLOBALS
size_t IMAGE_WIDTH = 342;
size_t IMAGE_HEIGHT = 512;

void help();
void processVideo(const std::string& a_videoFilename, const std::string& a_outputDir);

void help()
{
    cout
    << "Usage: ./export_frames <input_video> <output_dir>"
    << endl;
}

int main(int argc, char* argv[])
{
    //print help information
    help();
    //check for the input parameter correctness
    if(argc != 3) {
        cerr <<"Incorret input list" << endl;
        cerr <<"exiting..." << endl;
        return EXIT_FAILURE;
    }
    
    processVideo(argv[1], argv[2]);

    return EXIT_SUCCESS;
}

void processVideo(
    const std::string& a_videoFilename, const std::string& a_outputDir)
{
    //create the capture object
    VideoCapture capture(a_videoFilename);
    if (!capture.isOpened())
    {
        //error in opening the video input
        cerr << "Unable to open video file: " << a_videoFilename << endl;
        return;
    }


    bool l_isFirstImage = true;
    size_t l_frameNum = 0;
    while (true)
    {
        // read the current frame
        Mat frame; // current frame
        if(!capture.read(frame)) {
            cout << "Done reading frames.." << endl;
            break;
        }

        cv::resize(frame, frame, cv::Size(IMAGE_HEIGHT, IMAGE_WIDTH));
        cv::rotate(frame, frame, cv::ROTATE_90_CLOCKWISE);

        stringstream l_ss;
        l_ss << a_outputDir << "original_" << l_frameNum << ".png";
        cout << "Writing: " << l_ss.str() << endl;
        cv::imwrite(l_ss.str(), frame);
        l_frameNum++;
    }
    //delete capture object
    capture.release();
}

