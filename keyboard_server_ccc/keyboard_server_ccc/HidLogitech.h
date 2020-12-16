#pragma once

#include <string>
#include "DuckyParser.h"
#include <vector>

class HidLogitech
{
private:
	std::string m_address;
	std::string m_device_vendor = "Logitech";

	static unsigned char m_payload_template[10] ;
	static unsigned char m_keepalive[5];
	static unsigned char m_hello[10];

public:
	HidLogitech();
	~HidLogitech();

	std::string& checksum(std::string& payload);
	std::string& key(std::string& payload, blank_entry& b_key);
	std::string frame(blank_entry& b_key);
	std::vector<blank_entry> & build_frames(std::vector<blank_entry> & attack);

	static bool fingerprint(std::string& payload);
	static std::string description() { return "Logitech HID"; }
};

