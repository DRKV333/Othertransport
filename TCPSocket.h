#pragma once

#include "AsyncSocket.h"

#include <memory>
#include <asio/io_context_strand.hpp>
#include <asio/ip/tcp.hpp>
#include <readerwriterqueue/readerwriterqueue.h>

class TCPSocket : public AsyncSocket
{
private:
	struct Buffer
	{
		uint32_t length;
		std::unique_ptr<char[]> data;

		Buffer() = default;

		explicit Buffer(uint32_t lenght) : length(lenght), data(std::make_unique<char[]>(lenght)) { }
	};

	asio::io_context::strand strand;
	asio::ip::tcp::socket socket;

	moodycamel::ReaderWriterQueue<Buffer> inbox;
	moodycamel::ReaderWriterQueue<Buffer> outbox;

	Buffer pendingReceive;

	Buffer pendingRead;
	Buffer pendingWrite;

	bool writing;

	void doRead();

	void doCheckWrite();
	void doWrite();

public:
	explicit TCPSocket(asio::io_context& context)
		: strand(context), socket(context) { };

	virtual void connect(uint32_t ip, uint16_t port) override;

	virtual void send(const char* data, uint32_t length) override;

	virtual char* receive(uint32_t* length) override;

	virtual void receiveAck() override;
};