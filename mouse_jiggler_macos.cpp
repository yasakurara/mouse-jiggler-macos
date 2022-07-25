#include <ApplicationServices/ApplicationServices.h>
#include <iostream>

int main(void)
{
    CGRect displayBounds = CGDisplayBounds(CGMainDisplayID());
    CGPoint preLocation = {};
    int preX = 0;
    while (1) {
        sleep(60*5);
        CGEventSourceRef eventSource = CGEventSourceCreate(kCGEventSourceStateHIDSystemState);
        CGEventRef event = CGEventCreate(eventSource);
        CGPoint currentLocation = CGEventGetLocation(event);
        if (preLocation.x == 0 && preLocation.y == 0) {
            preLocation = currentLocation;
            continue;
        }
        if (preLocation.x != currentLocation.x || preLocation.y != currentLocation.y) {
            preLocation = currentLocation;
            continue;
        }
        preX = preX ? 0 : 1;
        CGPoint tgtLocation = CGPointMake(preX, (float)(displayBounds.size.height));
        CGEventRef mouseEvent = CGEventCreateMouseEvent(eventSource, kCGEventMouseMoved, tgtLocation, kCGMouseButtonLeft);
        CGEventPost(kCGHIDEventTap, mouseEvent);
        CFRelease(mouseEvent);
        CFRelease(event);
    }
    return 0;
}