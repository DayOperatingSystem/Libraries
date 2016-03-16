#ifndef HIDDEVICE_H
#define HIDDEVICE_H

#include <algorithm>
#include <vector>
#include "IODevice.h"

namespace IO
{
enum HID_EVENTS
{
	HID_KEY_DOWN = 0,
	HID_KEY_UP = 1,
	HID_AXIS_MOVE = 2
};

enum HID_SIGNALS
{
	HID_REGISTER_OBSERVER = 0xFF,
	HID_REMOVE_OBSERVER = 0xFE,
	HID_EVENT = 0xFD
};

struct HIDEvent
{
	unsigned int type;
	unsigned int data;
	unsigned int data1;
};

class HIDDevice : IODevice
{
	std::vector<pid_t> m_observers;
protected:
	void notifyObservers(HIDEvent& event);
public:
	HIDDevice() : IODevice() {}

	virtual bool initialize() = 0;
	virtual const char* getName() { return "Generic HID Device"; }
	virtual const char* getGenericName() { return "hiddevice"; }
	virtual unsigned int getType() { return 0; }
	virtual bool handle(message_t& msg);
	void addObserver(pid_t p) { m_observers.push_back(p); }
	void removeObserver(pid_t p) { m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), p)); }
	
	static bool registerObserver(const char* driver);
};
}

#endif // HIDDEVICE_H
