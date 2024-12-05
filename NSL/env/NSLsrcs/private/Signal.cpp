#include "../Signal.hpp"
#include <unistd.h>

const uint32
Signal::ThisPID = getpid();
const uint32
Signal::ThisGPID = getpgid(Signal::ThisPID);
