
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include<string>
#include<sstream>
#include <iostream>
#include <stdio.h>
#include<cstdlib> 
#include<sys/stat.h>
#include<sys/types.h>  
using namespace std;
using namespace cv;
   
int main(int argv,const char** argc )
{
int j=0;
int a;

std::ostringstream dirname;
dirname<<"dataset";
string dir;
dir = dirname.str();
mkdir(dir.c_str(),0750);



VideoCapture capture;                  
cout<<"enter 1 for webcam"<<endl;
cout<<"enter 2 for open video from file"<<endl;
cin>>a;
if (a==1){
capture.open(0);
    if (!capture.isOpened())  
    throw "Error when reading file";  
    namedWindow("window", 1);
}
else if (a==2)
{
capture.open("(Tubidy.io)_Angreji_Wali_Madam_Full_Song_Kulwinder_Billa_Dr_Zeus_Shipra_Ft_Wamiqa_Gabbi_Latest_Song_2017.mp4");
 if (!capture.isOpened())  
    throw "Error when reading file";  
    namedWindow("window", 1);
}

else
{cout<<"wrong input";
}



double fps = capture.set(CV_CAP_PROP_FPS, 45);

double fp =capture.get(CV_CAP_PROP_FPS);
 
cout << "Frames per second using video.get(CV_CAP_PROP_FPS) : " << fp << endl;
 

for (;;)
     { 
       Mat image; 
       capture >> image;  
       if (image.empty())  
       break; 
 
       // Load Face cascade (.xml file)
       CascadeClassifier face_cascade;
       face_cascade.load( "/home/rajat/opencv/data/haarcascades/haarcascade_frontalface_alt.xml" );
       if(!face_cascade.load("/home/rajat/opencv/data/haarcascades/haarcascade_frontalface_alt.xml"))
       {
         cerr<<"Error Loading XML file"<<endl;
         return 0;
       }
  

  //detect and display



    std::vector<Rect> faces;
    Mat frame_gray;
    Mat crop;
    Mat res;
    Mat gray;
    string text;
    stringstream sstm;

  /*cvtColor(image, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);*/

    // Detect faces
    face_cascade.detectMultiScale(image, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

    // Set Region of Interest
    cv::Rect roi_b;
    cv::Rect roi_c;

    size_t ic = 0; // ic is index of current element
    int ac = 0; // ac is area of current element

    size_t ib = 0; // ib is index of biggest element
    int ab = 0; // ab is area of biggest element

    for (ic = 0; ic < faces.size(); ic++) // Iterate through all current elements (detected faces)

    {
        roi_c.x = faces[ic].x;
        roi_c.y = faces[ic].y;
        roi_c.width = (faces[ic].width);
        roi_c.height = (faces[ic].height);

        ac = roi_c.width * roi_c.height; // Get the area of current element (detected face)

        roi_b.x = faces[ib].x;
        roi_b.y = faces[ib].y;
        roi_b.width = (faces[ib].width);
        roi_b.height = (faces[ib].height);

        ab = roi_b.width * roi_b.height; // Get the area of biggest element, at beginning it is same as "current" element

        if (ac > ab)
        {
            ib = ic;
            roi_b.x = faces[ib].x;
            roi_b.y = faces[ib].y;
            roi_b.width = (faces[ib].width);
            roi_b.height = (faces[ib].height);
        }
        
        //crop and resize image
        crop = image(roi_b);
        resize(crop, res, Size(182, 182), 0, 0, INTER_LINEAR); // This will be needed later while saving images



  Point pt1(faces[ic].x, faces[ic].y); // Display detected faces on main window
        Point pt2((faces[ic].x + faces[ic].height), (faces[ic].y + faces[ic].width));
        rectangle(image, pt1, pt2, Scalar(0, 255, 0), 4, 8, 0);


int frame_number;
frame_number = capture.get(CV_CAP_PROP_POS_FRAMES);

/*if (frame_number=frame_number-1)
{j=0;
j++;}
else
{j++;}*/

 
//show image
imshow("dtected face",image); 

//write image
std::ostringstream name;
//name <<"/home/rajat/Desktop/new/images/" <<"framenumber_"<<frame_number<<"image_"<< j << ".jpg";
name<<"/home/rajat/Desktop/computer_vision/dataset/"<<"rajat_"<<j<<".png";
cv::imwrite( name.str(),res);

j++;

  }

   if (waitKey(10) == 27)
  {
   cout << "Esc key is pressed by user. Stoppig the video" << endl;
   break;
     }  
   }
return 0;
}
