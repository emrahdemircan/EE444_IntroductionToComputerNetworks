#include "Transmission.h"

Transmission::Transmission(void){}

Transmission::Transmission(T_TRANSMISSIONTYPE ty,int id,int t,int fNo,int dl):type(ty),applicationId(id),time(t),frameNo(fNo),dataLength(dl){}
        
T_TRANSMISSIONTYPE Transmission::getTransmissionType(void) const
{
    return type;
}

int Transmission::getApplicationId(void) const
{
    return applicationId;
}

int Transmission::getTime(void) const
{
    return time;
}

int Transmission :: getFrameNo(void) const
{
    return frameNo;
}

int Transmission::getDataLength(void) const
{
    return dataLength;
}

void Transmission::incrementTimeIndex(void)
{
    time=time+1;
}
