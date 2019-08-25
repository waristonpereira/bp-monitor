#include <iostream>
#include "../src/include/bp-monitor.h"

using std::cout;
using std::cin;

int main() {
  bPressureMonitor m;
  // Sample of blood pressure wave
  int sample[] = {80, 80, 80, 80, 80, 80, 80, 81, 81, 85, 92, 100, 106,
116, 119, 119, 119, 117, 115, 110, 107, 107, 107, 108, 107, 105, 100, 99, 97,
93, 92, 90, 87, 86, 84, 83, 83, 82, 82, 82, 82, 81, 81, 81, 81, 80, 80, 80, 80,
80, 80, 80, 80, 80, 80, 80, 81, 81, 85, 92, 106, 112, 116, 119, 119, 119, 117,
112, 110, 107, 107, 108, 108, 105, 102, 100, 97, 95, 93, 90, 89, 87, 84, 84,
83, 83, 82, 82, 82, 81, 81, 81, 81, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80,
80, 81, 81, 85, 100, 106, 112, 119, 119, 119, 117, 115, 112, 107, 107, 107,
108, 107, 105, 100, 99, 97, 95, 92, 90, 89, 86, 84, 84, 83, 82, 82, 82, 82, 81,
81, 81, 81, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 81, 81, 85, 92, 100,
112, 116, 119, 119, 120, 117, 112, 110, 107, 107, 108, 108, 107, 102, 100, 99,
95, 93, 92, 89, 87, 86, 84, 83, 83, 82, 82, 82, 82, 81, 81, 81, 80, 80, 80, 80,
80, 80, 80, 80, 80, 80, 80, 80, 81, 81, 85, 100, 106, 112, 116, 119, 119, 119,
115, 112, 110, 107, 107, 108, 107, 105, 102, 99, 97, 95, 92, 90, 89, 86, 84,
84, 83, 82, 82, 82, 82, 81, 81, 81, 81, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80,
80, 81, 81, 81, 92, 100, 106, 116, 119, 119, 119, 117, 115, 110, 107, 107, 108,
108, 107, 102, 100, 99, 97, 93, 92, 90, 87, 86, 84, 83, 83, 82, 82, 82, 82, 81,
81, 81, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 81, 81, 85, 92, 106,
112, 116, 119, 119, 119, 115, 112, 110, 107, 107, 108, 108, 105, 102, 100, 97,
95, 93, 90, 89, 87, 84, 84, 83, 82, 82, 82, 82, 81, 81, 81, 81, 80, 80, 80, 80};
  // Size of array
  int n = sizeof(sample) / sizeof(*sample);
  int index = 0;
  bPressureMonitor::bPressure result = {
    0,   // systolic blood pressure value
    0,   // systolic blood pressure index
    0,   // diastolic blood pressure value
    0    // diastolic blood pressure index
  };
  // Test
  cout << "Enter index: ";
  cin >> index;
  cout << "running...";
  int retCode = m.measure(sample, n, index, result);
  cout << "done!" << std::endl;
  if (retCode) {
    cout << "Return error " << retCode << std::endl;
  } else {
    cout << "systolic\t" << result.dbp << "\t@ index:\t"
    << result.dbpIndex << std::endl;
    cout << "diastolic\t" << result.sbp << "\t@ index:\t"
    << result.sbpIndex << std::endl;
    cout << "estimated HR\t" << result.hr << "\tBPM" << std::endl;
  }
}
