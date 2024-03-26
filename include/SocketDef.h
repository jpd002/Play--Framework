#pragma once

#ifdef _WIN32

#define NOMINMAX
#include <winsock.h>

typedef int socklen_t;

#pragma comment(lib, "ws2_32.lib")

#else

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef int SOCKET;
static constexpr SOCKET INVALID_SOCKET = -1;

#endif
