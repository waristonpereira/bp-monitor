#ifndef SRC_INCLUDE_BP_MONITOR_H_
#define SRC_INCLUDE_BP_MONITOR_H_
#include <vector>
// Define error numbers
#define ERR_INVALIDARGS   1  // Invalid Argument
#define ERR_INVALIDRESULT 2  // Invalid Result

// Main class
class bPressureMonitor {
 public:
    //  Structure of BP measure
    struct bPressure {
      int sbp;       // systolic blood pressure value
      int sbpIndex;  // systolic blood pressure index
      int dbp;       // diastolic blood pressure value
      int dbpIndex;  // diastolic blood pressure index
      int hr;        // heart rate estimative
    };
    bPressureMonitor() {}
    ~bPressureMonitor() {}
    int measure(int*, int, int, bPressure&);
 private:
    // Struct for points
    struct point {
      int valley;    // valley detected
      int peak;      // peak detected
      int distance;  // distance from peak to valley
    };
    int valleyDetector(int*, int, int);
    void peakDetector(int*, int, std::vector<point>&);
    int estimateHr(int sampleRate, int index, std::vector<point>&);
};

#endif  // SRC_INCLUDE_BP_MONITOR_H_
