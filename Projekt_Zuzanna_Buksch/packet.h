// Class that includes informations about packet
#ifndef PACKET_H
#define PACKET_H

class Packet
{
public:
	Packet(int packet_id, int ctpk, int tx_rx_id, size_t time);
	~Packet();

	size_t GetPacketId() const;

	int GetLrNumber();
	void SetLrNumber(int lr);

	int GetTransmitterReceiverId();

	size_t GetPacketGenerationTime();

	bool GetTransmissionStatus();
	void SetTransmissionStatus(bool status);

	int GetCtpkTime();

private:
	int packet_id_;
	int ctpk_time; // time of sending packet
	int lr_number; // transmission counter
	size_t packet_generation_time;
	int transmitter_receiver_id;
	bool transmission_status = false;

};

#endif
