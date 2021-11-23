//#include "stdafx.h"

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	//Open the default video camera
	VideoCapture cap(1);

	// if not success, exit program
	if (cap.isOpened() == false)
	{
		cout << "Cannot open the video camera" << endl;
		cin.get(); //wait for any key press
		return -1;
	}

	double dWidth = cap.get(CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
	double dHeight = cap.get(CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

	cout << "Resolution of the video : " << dWidth << " x " << dHeight << endl;

	string window_name = "My Camera Feed";
	namedWindow(window_name); //create a window called "My Camera Feed"
	auto fps = cap.get(CAP_PROP_FPS); // frames per seconds
	auto delay = 1000 / fps;
	cout << "Çàäåðæêà â ìñ = " << delay << endl;
	while (true)
	{
		Mat frame;
		bool bSuccess = cap.read(frame); // read a new frame from video 

		//Breaking the while loop if the frames cannot be captured
		if (bSuccess == false)
		{
			cout << "Video camera is disconnected" << endl;
			cin.get(); //Wait for any key press
		break;
		}

		//show the frame in the created window
		auto time = clock();
		//cap >> frame; //ñ÷èòàåì ôðåéì
		imshow(window_name, frame);
		if (frame.channels() != 1) cvtColor(frame, frame, COLOR_RGB2GRAY);
		Mat x, y;
		Sobel(frame, x, CV_16S, 1, 0);
		Sobel(frame, y, CV_16S, 0, 1);
		// ìîäóëü ñîáåëÿ
		convertScaleAbs(x, x);
		convertScaleAbs(y, y);
		addWeighted(x, 0.5, y, 0.5, 0, frame); //ñîâìåùàåì êàðòèíêè
		imshow("sobel", frame);
		// ñêîðîñòü âèäåî
		double time_work = (clock() - time) * 1000 / CLOCKS_PER_SEC;
		if (time_work > delay - 1) time_work = 1;
		else time_work = delay - time_work;
		//  åñëè îáðàáîòêà ñîáåëåì áîëüøå ÷åì çàäåðæêà òîãäà ïîëó÷èòñÿ îòðèöàòåëüíîå çíà÷åíèå(îøèáêà)
		/*int cap = waitKey(time_work);
		if (cap >= 0) break;*/
		

		//wait for for 10 ms until any key is pressed.  
		//If the 'Esc' key is pressed, break the while loop.
		//If the any other key is pressed, continue the loop 
		//If any key is not pressed withing 10 ms, continue the loop 
		if (waitKey(10) == 27)
		{
		cout << "Esc key is pressed by user. Stoppig the video" << endl;
		break;
		}
	}
	

	//auto fps = cap.get(CAP_PROP_FPS); // frames per seconds
	//auto delay = 1000 / fps;
	//cout << "Çàäåðæêà â ìñ = " << delay << endl;

	//Mat frame;

	//while (1)
	//{
	//	auto time = clock();
	//	cap >> frame; //ñ÷èòàåì ôðåéì
	//	if (frame.channels() != 1) cvtColor(frame, frame, COLOR_RGB2GRAY);
	//	Mat x, y;
	//	Sobel(frame, x, CV_16S, 1, 0);
	//	Sobel(frame, y, CV_16S, 0, 1);
	//	// ìîäóëü ñîáåëÿ
	//	convertScaleAbs(x, x);
	//	convertScaleAbs(y, y);
	//	addWeighted(x, 0.5, y, 0.5, 0, frame); //ñîâìåùàåì êàðòèíêè
	//	imshow("sobel", frame);
	//	// ñêîðîñòü âèäåî
	//	double time_work = (clock() - time) * 1000 / CLOCKS_PER_SEC;
	//	if (time_work > delay - 1) time_work = 1;
	//	else time_work = delay - time_work;
	//	//  åñëè îáðàáîòêà ñîáåëåì áîëüøå ÷åì çàäåðæêà òîãäà ïîëó÷èòñÿ îòðèöàòåëüíîå çíà÷åíèå(îøèáêà)
	//	int cap = waitKey(time_work);
	//	if (cap >= 0) break;
	//}
	//destroyAllWindows();
	//
	//return 0;

}
