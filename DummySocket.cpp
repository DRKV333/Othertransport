#include "pch.h"

#include "DummySocket.h"

#include "Log.h"

void DummySocket::connect(uint32_t ip, uint16_t port)
{
    pendingConnectMessage = true;
}

void DummySocket::send(const char* data, uint32_t length)
{
    LOG_DEBUG(L"dataPtr: %p, length: %u", data, length);
}

char* DummySocket::receive(uint32_t* length)
{
    if (pendingConnectMessage)
    {
        LOG_DEBUG(L"Received connect message");
        *length = 1;
        pendingConnectMessage = false;
        return &connectMessage;
    }

    return nullptr;
}
