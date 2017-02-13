#include "commun.h"


int main(int argc, char *argv[])
{

    char key;

    Webcam * maWebcam = new Webcam();

    //cvSetMouseCallback("flux original", getObjectColor);
    maWebcam->binairisation();

    delete maWebcam;

    return 0;
}
