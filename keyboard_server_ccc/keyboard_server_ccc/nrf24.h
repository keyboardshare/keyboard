#ifndef KEYBOARD_SERVER_CCC_NRF24_H
#define KEYBOARD_SERVER_CCC_NRF24_H
#include <lusb0_usb.h>
#include <string>


enum USB_COMMANDS {
    TRANSMIT_PAYLOAD               = 0x04,
    ENTER_SNIFFER_MODE             = 0x05,
    ENTER_PROMISCUOUS_MODE         = 0x06,
    ENTER_TONE_TEST_MODE           = 0x07,
    TRANSMIT_ACK_PAYLOAD           = 0x08,
    SET_CHANNEL                    = 0x09,
    GET_CHANNEL                    = 0x0A,
    ENABLE_LNA_PA                  = 0x0B,
    TRANSMIT_PAYLOAD_GENERIC       = 0x0C,
    ENTER_PROMISCUOUS_MODE_GENERIC = 0x0D,
    RECEIVE_PAYLOAD                = 0x12,
};

#define RF_CH  0x05

#define RF_RATE_250K 0
#define RF_RATE_1M 1
#define RF_RATE_2M 2

#define DONGLE_ID_Vendor 0x1915
#define DONGLE_ID_Product 0x0102

class nrf24 {
private:
    int usb_timeout = 2500;
	usb_dev_handle* m_dev = NULL;
public:
    nrf24();
    ~nrf24();

    void enable_lna();
	void enter_promiscuous_mode();
	void enter_promiscuous_mode_generic();
	void enter_tone_test_mode();
	std::string receive_payload();
	void transmit_payload_generic();
	bool transmit_payload(std::string payload, char timeout = 4, char retransmits = 15);
	void transmit_ack_payload();
	void set_channel(int channel);
	std::string get_channel();
	void enter_sniffer_mode(std::string address);

	std::string send_and_recv(std::string request, std::string data);
};


#endif //KEYBOARD_SERVER_CCC_NRF24_H
