#ifndef TREX_ACCELERO_METER_H
#define TREX_ACCELERO_METER_H

namespace TRexLib{

    /*
     * Struct which hosts the axis values
     * of an AcceleroMeter.
     */
    struct AcceleroMeter {
    	int x;
    	int y;
    	int z;
    };

    /*
     * Struct which hosts the axis impact values
     * of an AcceleroMeter.
     */
    struct Impact {
    	int x;
    	int y;
    	int z;
    };
}

#endif