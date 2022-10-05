#include <iostream>
#include <ctime>
#include <random>

#include <ApplicationServices/ApplicationServices.h>

using namespace std;

void usage(void) {
    cout << "mouse_jiggler_macos -p <poll[sec]> -t <timeout[sec]> " << endl;
    exit(1);
}

int main(int argc, char *argv[]) {
    int poll_sec = 0;
    int timeout_sec = 0;

    int c;
    while ((c = getopt(argc, argv, "?p:t:")) != -1) {
        switch (c) {
            case '?': usage();
            case 'p': poll_sec = atoi(optarg); break;
            case 't': timeout_sec = atoi(optarg); break;
        }
    }
    if (poll_sec <= 0 || timeout_sec <= 0) usage();

    CGPoint preLocation = {};
    time_t preLocationTime;
    random_device rnd;
    while (1) {
        sleep(poll_sec);
        
        CGEventSourceRef eventSource = CGEventSourceCreate(kCGEventSourceStateHIDSystemState);
        CGEventRef event = CGEventCreate(eventSource);
        CGPoint currentLocation = CGEventGetLocation(event);
        if (preLocation.x == 0 && preLocation.y == 0) { // init
            preLocation = currentLocation;
            preLocationTime = time(nullptr);
            continue;
        }
        if (preLocation.x != currentLocation.x || preLocation.y != currentLocation.y) {
            preLocation = currentLocation;
            preLocationTime = time(nullptr);
            continue;
        }

        double diffTime = difftime(time(nullptr), preLocationTime);
        if (timeout_sec > (int)diffTime) {
            continue;
        } 
        
        CGRect displayBounds = CGDisplayBounds(CGMainDisplayID());
        float widthHalf = (float)(displayBounds.size.width)/2;
        float heightHalf = (float)(displayBounds.size.height)/2;
        float jiggle = rnd() % 10;
        CGPoint tgtLocation = CGPointMake(widthHalf+jiggle, heightHalf+jiggle);
        CGEventRef mouseEvent = CGEventCreateMouseEvent(eventSource, kCGEventMouseMoved, tgtLocation, kCGMouseButtonLeft);
        CGEventPost(kCGHIDEventTap, mouseEvent);
        CFRelease(mouseEvent);
        CFRelease(event);
        preLocation = tgtLocation;
    }
    return 0;
}
