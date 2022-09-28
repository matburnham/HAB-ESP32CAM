#include <Arduino.h>
#include <ArduinoUnitTests.h>
#include "Tracker.h"

#define LED_BUILTIN 13

unittest(tracker)
{
    Tracker tracker;
    GodmodeState* state = GODMODE();
    bool values[3];
    unsigned long start, end, pinTimes[3];
    start = micros();
    assertEqual(0, start);
    state->reset(); // clock and pins
    assertEqual(1, state->digitalPin[LED_BUILTIN].historySize());
    tracker.setup();
    assertEqual(1, state->digitalPin[LED_BUILTIN].historySize());
    tracker.loop();
    end = micros();
    assertEqual(3, state->digitalPin[LED_BUILTIN].historySize());
    assertEqual(3, state->digitalPin[LED_BUILTIN].toArray(values,3));
    assertEqual(0, values[0]);
    assertEqual(1, values[1]);
    assertEqual(0, values[2]);
    assertEqual(3, state->digitalPin[LED_BUILTIN].toTimestampArray(pinTimes,3));
    assertEqual(0, pinTimes[0]);
    assertEqual(0, pinTimes[1]);
    assertEqual(1000000, pinTimes[2]);
    assertEqual(2000000, end);
}

unittest_main()