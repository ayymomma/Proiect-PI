#include "functii.h"



int main(int argc, char* argv[])
{

    int w = 600;
    int h = 400;
    int bgchange = 15;
    int contor = 0;
    int threshold = 20;
    int sens = 20;
    int option = 1;

    Mat frame;
    Mat color;
    Mat backgound;



    //VideoCapture camera("testVideo2.mp4");
    VideoCapture camera("testVideo.mp4");
    //VideoCapture camera("vtest.avi");
    // VideoCapture camera(0);
    //VideoCapture camera("road_trafic.mp4");

    if (!camera.isOpened())
    {
        cout << "eroare";
        return 0;
    }
    camera.set(3, w);
    camera.set(4, h);


    camera.read(frame);
    cvtColor(frame, backgound, COLOR_BGR2GRAY);

    int fps;
    int delay;

    if (option == 1)
    {
        fps = (int)camera.get(CAP_PROP_FPS);
        delay = 1000 / fps;
    }

    while (camera.read(frame)) {

        clock_t startTime = clock();

        color = frame;
        cvtColor(frame, frame, COLOR_BGR2GRAY);
        Mat difference = Difference(frame, backgound, threshold);

        if (countDifferences(difference) != 0 || contor == bgchange)
        {
            backgound = frame;
            contor = 0;
            drawMotion(color, difference,sens);
        }


        imshow("Camera Output", color);
        imshow("Mask", difference);
        imshow("Background", backgound);



        if(option==1)
            while (clock() - startTime < delay)
                    waitKey(1);

        if (waitKey(1) == 27)
            break;

        contor++;
    }

    return 0;

}