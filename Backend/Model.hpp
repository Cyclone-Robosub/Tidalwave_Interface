#include <atomic>
struct DataModel {
  std::atomic<bool> current_mode;
};