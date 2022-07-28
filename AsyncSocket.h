#pragma once

#include <cstdint>

class AsyncSocket
{
public:
	virtual void connect(uint32_t ip, uint32_t port) = 0;

	virtual void send(const char* data, uint32_t length) = 0;

	virtual char* receive(uint32_t* length) = 0;

	virtual void receiveAck() { };

	virtual ~AsyncSocket() = default;
};