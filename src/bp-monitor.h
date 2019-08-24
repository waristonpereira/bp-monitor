#ifndef _BP_MONITOR_H
#define _BP_MONITOR_H
// Structure of BP measure
typedef struct BP {
    int SBP    = 0;  // systolic blood pressure value
    int SBPi   = 0;  // systolic blood pressure index
    int DBP    = 0;  // diastolic blood pressure value
    int DBPi   = 0;  // diastolic blood pressure index
} BP;

class BP_MONITOR {
	public:
		BP measure(int[], int, int);
};
#endif
