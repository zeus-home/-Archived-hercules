#ifndef HERCULES_DRIVER_H
#define HERCULES_DRIVER_H

#define BULB 0;
#define FAN 1; 
#define SOCKET 2;

#define PULSE_DURATION 2;

#define FREQUENCY 50;
#define HALF_CYCLE_INTERVAL 1000/2/FREQUENCY;
#define FULL_CYCLE_INTERVAL 1000/FREQUENCY;

class HerculesDriver {
    private:
        static unsigned long zeroTime;
        static int ledState;

        static bool deviceState[3];
        static int deviceIntensity[2];

    public:
        static void interrupt();
        static void handleDevices();
};

#endif
