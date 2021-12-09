#ifndef SIMULATION_H
#define SIMULATION_H

#include "PriorityQueue.h"
#include "Transmission.h"
#include "RandomNumberGenerator.h"

// maximum size of the priority queue array
const int MAX_QUEU_SIZE  = 10000;

class Simulation
{	
	private:
		int acceptTime;	//connection requests are aceepted only till this time
		int numBuffers;	//1 buffer for two applications or 2 buffers, one for each
		int openLow;	//minimum time for a connection request to occur
		int openHigh;	//max time for a connection request to occur
		int dataLow;	//min data length for a new application
		int dataHigh;	//max data length
		int winSize;	//winsize to be used in transmission
		int frameLength;//one frame length
		int bufferServiceTime;//service time of receiver terminal for one frame
		int transmissionTime;//time for one frame to go from one terminal to the other
		
		PriorityQueue<Transmission,MAX_QUEU_SIZE> network;
        PriorityQueue<Transmission,MAX_QUEU_SIZE> senderBuf0;
        PriorityQueue<Transmission,MAX_QUEU_SIZE> senderBuf1;
        PriorityQueue<Transmission,MAX_QUEU_SIZE> receiverBuf0;
        PriorityQueue<Transmission,MAX_QUEU_SIZE> receiverBuf1;
        RandomNumberGenerator rnd;

		int NextSendRequestTime(void);
		int AppDataLength(void);
		int AppID(void);

	public:
		Simulation(void);
		void RunSimulation(void);
};

#endif
