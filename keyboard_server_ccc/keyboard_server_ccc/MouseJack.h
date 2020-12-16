
#ifndef KEYBOARD_SERVER_CCC_MOUSEJACK_H
#define KEYBOARD_SERVER_CCC_MOUSEJACK_H

#include "nrf24.h"
#include "HidLogitech.h"
#include <vector>


class MouseJack {
private:
	nrf24* m_nrf24 = NULL;
	static unsigned char ping[4];
	unsigned int min_channel = 2;
	unsigned int max_channel = 84;
	int m_channel = 0;

public:
	MouseJack(bool reset = false);
	~MouseJack();

	static std::string from_display(std::string address);
	void init_radio(bool reset);
	void sniffer_mode(std::string address);
	int find_channel(std::string address);
	void set_channel(int channel);
	bool transmit_payload(std::string payload);
	bool attack(HidLogitech& hid, std::vector<blank_entry>& attack);

};


#endif //KEYBOARD_SERVER_CCC_MOUSEJACK_H
