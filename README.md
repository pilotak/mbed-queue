# mbed-queue
Simple static (allocated space in RAM) and dynamic (in heap) message queue for mbed. Both behave like circular-buffer. Dynamic queue has advantage that you can push data not only to the end but to front too.

## Dynamic message queue
```cpp
#include "mbed.h"
#include "DynamicQueue.h"

typedef struct {
    uint8_t counter;
} message_t;

DynamicQueue<message_t, 4> q;

int main (void) {
    uint8_t i = 0;  // dummy data

    while (true) {
        i++;
        message_t test;
        test.counter = i;
        q.push_back(test);

        if (i % 6 == 0) {

            if (!q.empty()) {
                printf("data: ");

                while (!q.empty()) {
                    message_t f = q.get();
                    printf("%u  ", f.counter);
                }

                printf("\n");
            }
        }

        wait_ms(250);
    }
}
```

## Static message queue
```cpp
#include "mbed.h"
#include "StaticQueue.h"

typedef struct {
    uint8_t counter;
} message_t;

StaticQueue<message_t, 4> q;

int main (void) {
    uint8_t i = 0;  // dummy data

    while (true) {
        i++;
        message_t test;
        test.counter = i;
        q.push_back(test);

        if (i % 6 == 0) {

            if (!q.empty()) {
                printf("data: ");

                while (!q.empty()) {
                    message_t f = q.get();
                    printf("%u  ", f.counter);
                }

                printf("\n");
            }
        }

        wait_ms(250);
    }
}
```
