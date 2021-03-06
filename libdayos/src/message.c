#include <message.h>
#include <syscall.h>
#include <sleep.h>
#include <string.h>
#include <arch.h>

int send_message(message_t* msg, uint32_t pid)
{
	if(msg == NULL)
		return MESSAGE_ERR_SEND;

	msg->receiver = pid;

	return syscall1(SYSCALL_SEND_MESSAGE, (uintptr_t) msg);
}

int receive_message(message_t* msg, pid_t who)
{
	if(msg == NULL)
		return MESSAGE_ERR_RECEIVE;

	return syscall2(SYSCALL_RECEIVE_MESSAGE, (uintptr_t) msg, who);
}

int receive_message_timeout(message_t* msg, pid_t who, uint32_t tries, uint32_t delay)
{
	for(int i = tries; i > 0; i--)
	{
		if(receive_message(msg, who) == MESSAGE_RECEIVED)
			return MESSAGE_RECEIVED;
		
		sleep(delay);
	}
	
	return MESSAGE_ERR_RECEIVE;
}

#include <dayos.h>

#define RECEIVE(msg, pid) while(receive_message(&msg, pid) != MESSAGE_RECEIVED) sleep(1);

/// FIXME: Error when requesting MESSAGE_STRING_SIZE + 1 bytes!
int read_message_stream(void* data, size_t size, pid_t who)
{
	message_t msg;
	
	// Get prolog
	RECEIVE(msg, who);
	if(msg.signal != SIGNAL_OK) return 0;

	// Be sure to only expect what can be taken and
	// only what is going to be sent.
	size = (size < msg.size) ? size : msg.size;
	
	size_t received = 0;
	while(received < size)
	{
		RECEIVE(msg, who);
		if(msg.signal != SIGNAL_OK)
			break;
		
		memcpy(data, msg.message, msg.size);
		data = ((char*) data) +  msg.size;
		received += msg.size;
	}

	return received;
}

#include <stdio.h>

int write_message_stream(const char* data, size_t size, pid_t who)
{
	message_t msg;
	size_t num_messages = (size_t)((float)size / MESSAGE_STRING_SIZE);
	size_t remaining_bytes = size % MESSAGE_STRING_SIZE;

	msg.signal = SIGNAL_OK;
	msg.size = size;
	send_message(&msg, who);
	
	size_t sent = 0;
	for(int i = 0; i < num_messages; i++)
	{
		memcpy(msg.message, data, MESSAGE_STRING_SIZE);
		msg.size = MESSAGE_STRING_SIZE;
		send_message(&msg, who);
		
		data += MESSAGE_STRING_SIZE;
		sent += MESSAGE_STRING_SIZE;
	}
	
	msg.size = remaining_bytes;
	memcpy(msg.message, data, remaining_bytes);
	send_message(&msg, who);
	
	sent += remaining_bytes;
	return sent;
}
