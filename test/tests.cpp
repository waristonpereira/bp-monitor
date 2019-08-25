#include <gtest/gtest.h>
#include "../src/bp-monitor.cpp"

int sample[] = {80, 80, 80, 80, 80, 80, 80, 81, 81, 85, 92, 100, 106, 116,
119, 119, 119, 117, 115, 110, 107, 107, 107, 108, 107, 105, 100, 99, 97, 93, 92,
90, 87, 86, 84, 83, 83, 82, 82, 82, 82, 81, 81, 81, 81, 80, 80, 80, 80, 80, 80,
80, 80, 80, 80, 80, 81, 81, 85, 92, 106, 112, 116, 119, 119, 119, 117, 112, 110,
107, 107, 108, 108, 105, 102, 100, 97, 95, 93, 90, 89, 87, 84, 84, 83, 83, 82,
82, 82, 81, 81, 81, 81, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 81, 81,
85, 100, 106, 112, 119, 119, 119, 117, 115, 112, 107, 107, 107, 108, 107, 105,
100, 99, 97, 95, 92, 90, 89, 86, 84, 84, 83, 82, 82, 82, 82, 81, 81, 81, 81,
80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 81, 81, 85, 92, 100, 112, 116, 119,
119, 120, 117, 112, 110, 107, 107, 108, 108, 107, 102, 100, 99, 95, 93, 92, 89,
87, 86, 84, 83, 83, 82, 82, 82, 82, 81, 81, 81, 80, 80, 80, 80, 80, 80, 80, 80,
80, 80, 80, 80, 81, 81, 85, 100, 106, 112, 116, 119, 119, 119, 115, 112, 110,
107, 107, 108, 107, 105, 102, 99, 97, 95, 92, 90, 89, 86, 84, 84, 83, 82, 82,
82, 82, 81, 81, 81, 81, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 81, 81, 81,
92, 100, 106, 116, 119, 119, 119, 117, 115, 110, 107, 107, 108, 108, 107, 102,
100, 99, 97, 93, 92, 90, 87, 86, 84, 83, 83, 82, 82, 82, 82, 81, 81, 81, 80,
80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 81, 81, 85, 92, 106, 112, 116, 119,
119, 119, 115, 112, 110, 107, 107, 108, 108, 105, 102, 100, 97, 95, 93, 90, 89,
87, 84, 84, 83, 82, 82, 82, 82, 81, 81, 81, 81, 80, 80, 80, 80};
bPressureMonitor m;
int n = sizeof(sample) / sizeof(*sample);

TEST(BP_MONITOR,  measureValues) {
  bPressureMonitor::bPressure pressure = {0, 0, 0, 0};
  int returnError = 0;

  returnError = m.measure(sample, n, 160, pressure);
  ASSERT_EQ(returnError, 0);
  ASSERT_EQ(pressure.sbp, 120);
  ASSERT_EQ(pressure.sbpIndex, 163);
  ASSERT_EQ(pressure.dbp, 80);
  ASSERT_EQ(pressure.dbpIndex, 153);

  returnError = m.measure(sample, n, 10, pressure);
  ASSERT_EQ(returnError, 0);
  ASSERT_EQ(pressure.sbp, 119);
  ASSERT_EQ(pressure.sbpIndex, 15);
  ASSERT_EQ(pressure.dbp, 80);
  ASSERT_EQ(pressure.dbpIndex, 1);

  returnError = m.measure(sample, n, 163, pressure);
  ASSERT_EQ(returnError, 0);
  ASSERT_EQ(pressure.sbp, 120);
  ASSERT_EQ(pressure.sbpIndex, 163);
  ASSERT_EQ(pressure.dbp, 80);
  ASSERT_EQ(pressure.dbpIndex, 153);

  returnError = m.measure(sample, n, 153, pressure);
  ASSERT_EQ(returnError, 0);
  ASSERT_EQ(pressure.sbp, 120);
  ASSERT_EQ(pressure.sbpIndex, 163);
  ASSERT_EQ(pressure.dbp, 80);
  ASSERT_EQ(pressure.dbpIndex, 153);
}

TEST(BP_MONITOR,  MeasureFailed) {
  bPressureMonitor::bPressure pressure = {0, 0, 0, 0};
  int returnError = 0;

  returnError = m.measure(sample, n, 220, pressure);
  ASSERT_EQ(returnError, 2);
  ASSERT_EQ(pressure.sbp, 0);
  ASSERT_EQ(pressure.sbpIndex, 0);
  ASSERT_EQ(pressure.dbp, 0);
  ASSERT_EQ(pressure.dbpIndex, 0);

  returnError = m.measure(sample, n, 100, pressure);
  ASSERT_EQ(returnError, 2);
  ASSERT_EQ(pressure.sbp, 0);
  ASSERT_EQ(pressure.sbpIndex, 0);
  ASSERT_EQ(pressure.dbp, 0);
  ASSERT_EQ(pressure.dbpIndex, 0);

  returnError = m.measure(sample, n, 220, pressure);
  ASSERT_EQ(returnError, 2);
  ASSERT_EQ(pressure.sbp, 0);
  ASSERT_EQ(pressure.sbpIndex, 0);
  ASSERT_EQ(pressure.dbp, 0);
  ASSERT_EQ(pressure.dbpIndex, 0);

  returnError = m.measure(sample, n, 23, pressure);
  ASSERT_EQ(returnError, 2);
  ASSERT_EQ(pressure.sbp, 0);
  ASSERT_EQ(pressure.sbpIndex, 0);
  ASSERT_EQ(pressure.dbp, 0);
  ASSERT_EQ(pressure.dbpIndex, 0);

  returnError = m.measure(sample, n, 24, pressure);
  ASSERT_EQ(returnError, 2);
  ASSERT_EQ(pressure.sbp, 0);
  ASSERT_EQ(pressure.sbpIndex, 0);
  ASSERT_EQ(pressure.dbp, 0);
  ASSERT_EQ(pressure.dbpIndex, 0);
}

TEST(BP_MONITOR,  InvalidArgs) {
  bPressureMonitor::bPressure pressure = {0, 0, 0, 0};
  int returnError = 0;

  returnError = m.measure(sample, -1, -1, pressure);
  ASSERT_EQ(returnError, 1);
  ASSERT_EQ(pressure.sbp, 0);
  ASSERT_EQ(pressure.sbpIndex, 0);
  ASSERT_EQ(pressure.dbp, 0);
  ASSERT_EQ(pressure.dbpIndex, 0);

  returnError = m.measure(sample, n, 0, pressure);
  ASSERT_EQ(returnError, 1);
  ASSERT_EQ(pressure.sbp, 0);
  ASSERT_EQ(pressure.sbpIndex, 0);
  ASSERT_EQ(pressure.dbp, 0);
  ASSERT_EQ(pressure.dbpIndex, 0);

  returnError = m.measure(sample, n, 1000, pressure);
  ASSERT_EQ(returnError, 1);
  ASSERT_EQ(pressure.sbp, 0);
  ASSERT_EQ(pressure.sbpIndex, 0);
  ASSERT_EQ(pressure.dbp, 0);
  ASSERT_EQ(pressure.dbpIndex, 0);

  returnError = m.measure(sample, 0, 0, pressure);
  ASSERT_EQ(returnError, 1);
  ASSERT_EQ(pressure.sbp, 0);
  ASSERT_EQ(pressure.sbpIndex, 0);
  ASSERT_EQ(pressure.dbp, 0);
  ASSERT_EQ(pressure.dbpIndex, 0);
}

TEST(BP_MONITOR,  injectData) {
  bPressureMonitor::bPressure pressure = {0, 0, 0, 0};
  int returnError = 0;

  pressure = {-1, -1, -1, -1};
  returnError = m.measure(sample, n, 160, pressure);
  ASSERT_EQ(returnError, 0);
  ASSERT_EQ(pressure.sbp, 120);
  ASSERT_EQ(pressure.sbpIndex, 163);
  ASSERT_EQ(pressure.dbp, 80);
  ASSERT_EQ(pressure.dbpIndex, 153);

  pressure = {-1, -1, -1, -1};
  returnError = m.measure(sample, n, 220, pressure);
  ASSERT_EQ(returnError, 2);
  ASSERT_EQ(pressure.sbp, 0);
  ASSERT_EQ(pressure.sbpIndex, 0);
  ASSERT_EQ(pressure.dbp, 0);
  ASSERT_EQ(pressure.dbpIndex, 0);
}

int main(int argc,  char **argv) {
    testing::InitGoogleTest(&argc,  argv);
    return RUN_ALL_TESTS();
}
