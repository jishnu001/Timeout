# Timeout
Include the header to use
eg:
auto fn = []() { std::cerr << "\n timeout"; };
Timeout t(10, fn, false); // 10 second timeout calls fn, not singleshot
t.start();
