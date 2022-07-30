#include "pch.h"

#include "TCPSocket.h"

#include "OLRakNetTypes.h"
#include "Log.h"

void TCPSocket::connect(uint32_t ip, uint16_t port)
{
	//TODO: Make this timeout a little sooner.
	asio::ip::tcp::endpoint endpoint(asio::ip::address_v4(_byteswap_ulong(ip)), port);
	socket.async_connect(endpoint, asio::bind_executor(strand, [this](asio::error_code error)
	{
		Buffer buffer(1);

		if (error)
		{
			LOG_DEBUG(L"Connect failed! %S", error.message().c_str());
			buffer.data[0] = OLDefaultMessageIDTypes::OL_ID_CONNECTION_ATTEMPT_FAILED;
		}
		else
		{
			LOG_DEBUG(L"Connect success!");
			buffer.data[0] = OLDefaultMessageIDTypes::OL_ID_CONNECTION_REQUEST_ACCEPTED;
			doRead();
		}

		inbox.enqueue(std::move(buffer));
	}));
}

void TCPSocket::doRead()
{
	asio::async_read(socket, asio::mutable_buffer(&pendingRead.length, sizeof(pendingRead.length)),
		asio::bind_executor(strand, [this](asio::error_code error, size_t)
	{
		if (error)
		{
			LOG_DEBUG(L"Read failed! %S", error.message().c_str());
			// TODO: Figure out how to tell the client about the disconnect.
			return;
		}

		pendingRead.data = std::make_unique<char[]>(pendingRead.length);

		asio::async_read(socket, asio::mutable_buffer(pendingRead.data.get(), pendingRead.length),
			asio::bind_executor(strand, [this](asio::error_code error, size_t)
		{
			if (error)
			{
				LOG_DEBUG(L"Read failed! %S", error.message().c_str());
				// TODO: Figure out how to tell the client about the disconnect.
				return;
			}

			inbox.enqueue(std::move(pendingRead));

			doRead();
		}));
	}));
}

void TCPSocket::send(const char* data, uint32_t length)
{
	Buffer buffer(length);
	memcpy(buffer.data.get(), data, length);

	outbox.enqueue(std::move(buffer));

	doCheckWrite();
}

void TCPSocket::doCheckWrite()
{
	asio::post(strand, [this]()
	{
		if (!writing)
		{
			writing = true;
			doWrite();
		}
	});
}

void TCPSocket::doWrite()
{
	if (!outbox.try_dequeue(pendingWrite))
	{
		writing = false;
		return;
	}

	asio::async_write(socket, asio::const_buffer(&pendingWrite.length, sizeof(pendingWrite.length)),
		asio::bind_executor(strand, [this](asio::error_code error, size_t) { 

		if (error)
		{
			LOG_DEBUG(L"Write failed! %S", error.message().c_str());
			// TODO: Figure out how to tell the client about the disconnect.
		}

		asio::async_write(socket, asio::const_buffer(pendingWrite.data.get(), pendingWrite.length),
			asio::bind_executor(strand, [this](asio::error_code error, size_t)
		{
			if (error)
			{
				LOG_DEBUG(L"Write failed! %S", error.message().c_str());
				// TODO: Figure out how to tell the client about the disconnect.
			}

			pendingWrite.data.release();

			doWrite();
		}));

	}));
}

char* TCPSocket::receive(uint32_t* length)
{
	if (!inbox.try_dequeue(pendingReceive))
		return nullptr;

	*length = pendingReceive.length;
	return pendingReceive.data.get();
}

void TCPSocket::receiveAck()
{
	pendingReceive.data.release();
}
