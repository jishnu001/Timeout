# Timeout
Include the header to use
<br/>
eg:
auto fn = []() { std::cerr << "\n timeout"; }; <br/>
Timeout t(10, fn, false); // 10 second timeout calls fn, not singleshot <br/>
t.start(); <br/>
