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
    std::this_thread::sleep_for(timeoutInterval);
    onTimeOut();
    if (singleShot)
      return;
  }

  std::chrono::seconds timeoutInterval;
  std::function<void(void)> onTimeOut;
  bool singleShot;
  std::thread th;
};