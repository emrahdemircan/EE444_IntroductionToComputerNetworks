#ifndef TRANSMISSION_H
#define TRANSMISSION_H

#include <stdio.h>

typedef enum
{
    TRANSMISSIONTYPE_SEND,
    TRANSMISSIONTYPE_ACK,
} T_TRANSMISSIONTYPE;

class Transmission
{
    private:
        T_TRANSMISSIONTYPE type;
        int applicationId;
        int time;
        int frameNo;
        int dataLength;
    public:
        Transmission(void);
        Transmission(T_TRANSMISSIONTYPE ty,int ID,int t,int fNo,int dl);
        T_TRANSMISSIONTYPE getTransmissionType(void) const;
        int getApplicationId(void) const;
        int getTime(void) const;
        int getFrameNo(void) const ;
        int getDataLength(void) const;
        void incrementTimeIndex(void);
    
        int operator < (Transmission b)
        {
            return this->getTime() < b.getTime();
        }
};

#endif
