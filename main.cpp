#include "functii.h"



int main(int argc, char* argv[])
{

    int w = 600;
    int h = 400;
    int bgchange = 15;
    int contor = 0;
    vector<vector<Point>> cnts;


    Mat frame;
    Mat color;
    Mat backgound;



    VideoCapture camera("C:/testVideo.mp4");
    if (!camera.isOpened())
    {
        cout << "eroare";
        return 0;
    }
    camera.set(3, w);
    camera.set(4, h);


    camera.read(frame);
    cvtColor(frame, backgound, COLOR_BGR2GRAY);



    while (camera.read(frame)) {

        color = frame;
        cvtColor(frame, frame, COLOR_BGR2GRAY);
        Mat difference = Difference(frame, backgound, 20);

        if (countDifferences(difference) != 0 || contor == bgchange)
        {
            backgound = frame;
            contor = 0;
        }

        imshow("Camera Output", color);
        imshow("Mask", difference);
        imshow("Background", backgound);


        if (waitKey(1) == 27)
            break;

        contor++;
    }

    return 0;

}