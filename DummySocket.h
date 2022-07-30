#pragma once

#include "AsyncSocket.h"
#include "OLRakNetTypes.h"

class DummySocket : public AsyncSocket
{
private:
	bool pendingConnectMessage = false;
	char connectMessage = OLDefaultMessageIDTypes::OL_ID_CONNECTION_REQUEST_ACCEPTED;

public:
	virtual void connect(uint32_t ip, uint16_t port) override;

	virtual void send(const char* data, uint32_t length) override;

	virtual char* receive(uint32_t* length) override;
};