#include <HIDDevice.h>
#include <cstring>

using namespace IO;

bool HIDDevice::handle(message_t& msg)
{
	if(msg.signal == HID_REGISTER_OBSERVER && !strcmp(msg.message, getGenericName()))
	{
		addObserver(msg.sender);
		return true;
	}
	else if(msg.signal == HID_REMOVE_OBSERVER)
	{
		removeObserver(msg.sender);
		return true;
	}
	
	return false;
}

void HIDDevice::notifyObservers(HIDEvent& event)
{
	message_t msg;
	msg.size = sizeof(HIDEvent);
	msg.signal = HID_EVENT;
	
	memcpy(msg.message, &event, msg.size);
	
	pid_t p = 0;
	for(int i = m_observers.size() - 1; i >= 0; i--)
	{
		p = m_observers[i];
		
		// Remove invalid observers.
		if(send_message(&msg, p) != MESSAGE_SENT)
			removeObserver(p);
	}
}


bool HIDDevice::registerObserver(const char* driver)
{
	pid_t p = get_service_pid(driver);
	
	if(!p)
	{
		return false;
	}
	
	message_t msg;
	msg.signal = HID_REGISTER_OBSERVER;
	strncpy(msg.message, driver, MESSAGE_STRING_SIZE);
	return (send_message(&msg, p) == MESSAGE_SENT);
}
