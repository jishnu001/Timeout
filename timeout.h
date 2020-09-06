#include <unistd.h>
#include <chrono>
#include <thread>
class Timeout {
 public:
  // @param timeoutInterval in seconds
  // @param onTimeOut callback function
  // @param singleShot timer
  Timeout(int timeoutInterval,
          const std::function<void(void)>& onTimeOut,
          bool singleShot)
      : timeoutInterval(timeoutInterval),
        onTimeOut(onTimeOut),
        singleShot(singleShot) {}

  // Start the timer
  void start() {
    th = std::thread([&]() { run(); });
    th.detach();
  }

 private:
  void run() {
    auto current = std::chrono::steady_clock::now();
    auto initial = std::chrono::steady_clock::now();

    while (true) {
      if (current > initial + timeoutInterval) {
        onTimeOut();
        if (singleShot)
          return;
        current = std::chrono::steady_clock::now();
        initial = std::chrono::steady_clock::now();
      }
      current = std::chrono::steady_clock::now();
    }
  }

  std::chrono::seconds timeoutInterval;
  std::function<void(void)> onTimeOut;
  bool singleShot;
  std::thread th;
};