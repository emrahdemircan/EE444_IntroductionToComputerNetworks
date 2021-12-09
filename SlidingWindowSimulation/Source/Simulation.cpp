#include <stdio.h>
#include <iomanip>
#include "Simulation.h"

Simulation::Simulation(void)
{
    cout <<"Enter values for requested parameters."<<endl;
    cout <<"Application accept time                            : ";
    cin >>acceptTime;
    cout <<"Number of buffers to be used in transmission (1/2) : ";
    cin >>numBuffers;
    cout <<"Application data send request time range           : ";
    cin >>openLow>>openHigh;
    cout <<"Data length range for each send request            : ";
    cin >>dataLow>>dataHigh;
    cout <<"Window size used in transmission                   : ";
    cin >>winSize;
    cout <<"Data link layer frame length                       : ";
    cin >>frameLength;
    cout <<"Buffer service time                                : ";
    cin >>bufferServiceTime;
    cout <<"Transmission time for each packet between peers    : ";
    cin >>transmissionTime;
    cout<<endl;
}
int Simulation::NextSendRequestTime(void)
{
    return openLow+rnd.Random(openHigh-openLow+1);    //random generator to give a random time shift to nextTime
}
//determine random data length for next connection open
int Simulation::AppDataLength(void)
{
    return dataLow+rnd.Random(dataHigh-dataLow+1);//random generator to give a data length for an application request
}
int Simulation::AppID(void)
{
    return rnd.Random(2);    //random generator to give 0 or 1 so called application 0 and application1
}


void Simulation::RunSimulation(void)
{
    Transmission newRequest,temp, modifiedOne;
    Transmission newFrame,e,f,g,h,i;
    int nextTime=0;            //parameter to achieve a next connection request time
    int frameApp0=0;
    int frameApp1=0;
    int ftsl0=0;                //window parameters: ftsl=frame to send low....
    int ftsh0=winSize-1;                //ftsh=frame to send high
    int ftal0=0;                //ftal=frame to ack low
    int ftah0=winSize-1;                //ftah=frame to ack high
    int ftsl1=0;
    int ftsh1=winSize-1;
    int ftal1=0;
    int ftah1=winSize-1;
    int time0=0;
    int time1=0;
    int totalData0=0;
    int totalData1=0;
    int totalData=0;

    while(nextTime <= acceptTime)
        {
            newRequest=Transmission(TRANSMISSIONTYPE_SEND,AppID(),nextTime,0, AppDataLength());
            network.insert(newRequest);
            nextTime=nextTime+NextSendRequestTime();
        }//while nexttime..
    if (numBuffers==1)
        {
            while(!network.isEmpty())
                {
                    temp=network.removeFromQueue();
                    if (temp.getApplicationId()==0 && !(temp.getDataLength()<=0))
                        {    newFrame=Transmission(TRANSMISSIONTYPE_SEND,0,time0,frameApp0,0);
                            frameApp0++;
                            senderBuf0.insert(newFrame);
                            time0++;
                            modifiedOne=Transmission(TRANSMISSIONTYPE_SEND,0,time0,frameApp0,(temp.getDataLength()-frameLength));
                            network.insert(modifiedOne);
                        }
                    if (temp.getApplicationId()==1 && !(temp.getDataLength()<=0))
                        {
                            newFrame=Transmission(TRANSMISSIONTYPE_SEND,1,time0,frameApp1,0);
                            frameApp1++;
                            senderBuf0.insert(newFrame);
                            time0++;
                            modifiedOne=Transmission(TRANSMISSIONTYPE_SEND,1,time0,frameApp1,(temp.getDataLength()-frameLength));
                            network.insert(modifiedOne);
                        }
                }//while !network..

            while(!senderBuf0.isEmpty())
                {
                    if(!(ftsh0==ftsl0))
                        {
label:                        f=senderBuf0.removeFromQueue();
                            cout <<"Time:"<<setw(2)<<f.getTime()<<" Sender Window is now on: "
                                 <<ftsl0<<" through "<<ftsh0<<" frames."<<endl;
                            cout <<endl;
                            
                            ftsl0=(ftsl0+1)%winSize;
                            
                            cout <<"    Frame NO: "<<f.getFrameNo()
                                 <<" of Application: "<<f.getApplicationId()<<" is being sent..."<<endl;
                            cout <<endl;
                            cout <<"    Transmission through Buffer: 0 for Application "<<f.getApplicationId()<<endl;
                            cout<<endl;

                            g=Transmission(TRANSMISSIONTYPE_ACK,f.getApplicationId(),f.getTime()+bufferServiceTime+2*transmissionTime,
                                f.getFrameNo(),0);
                            receiverBuf0.insert(g);
                            if (!receiverBuf0.isEmpty())
                                {
                                    h=receiverBuf0.removeFromQueue();
                                    if(f.getTime()==h.getTime())
                                        {
                                            ftsh0=(ftsh0+1)%winSize;
                                            cout <<"    ACK has just come for Application: "<<h.getApplicationId()
                                                 <<" Frame: "<<h.getFrameNo()<<endl;
                                            cout <<endl;
                                        }//if f.getTime....
                                    else receiverBuf0.insert(h);
                                }//if !receiver...
                            totalData0 +=frameLength;
                            totalData +=frameLength;
                        }//if !ftsh0==ftsl0
                    else
                        {
                            int l = receiverBuf0.getMinElementIndex();
                            e= receiverBuf0.getElementAtIndex(l);
                            int m= senderBuf0.getMinElementIndex();
                            f=    senderBuf0.getElementAtIndex(m);
                            if (e.getTime() >= f.getTime() )
                                {
                                    cout <<"    Transmission will wait until acknowledge at time: "<<f.getTime()<<endl;
                                    cout <<endl;
                                }
                            for (int k=0 ; k < senderBuf0.getListSize();  k++)
                                    {    g = senderBuf0.getElementAtIndex(k);
                                        while( g.getTime() < e.getTime())
                                                    g.incrementTimeIndex();
                                        senderBuf0.changeElementAtIndex(k,g);
                                    }
                            goto label;
                        }
                }//while !senderbuf0.isEmpty()
            while(!receiverBuf0.isEmpty())
                {
                    h=receiverBuf0.removeFromQueue();
                    cout <<"Time:"<<setw(2)<<h.getTime()<<" ACK has just come for Application: "
                         <<h.getApplicationId()<<" Frame: "<<h.getFrameNo()<<endl;
                    cout <<endl;
                }//while !receiverBuf0....
        }//if numbuffers...
    if (numBuffers==2)
        {
            while(!network.isEmpty())
                {
                    temp=network.removeFromQueue();
                    if (temp.getApplicationId()==0 && !(temp.getDataLength()<=0))
                        {    newFrame=Transmission(TRANSMISSIONTYPE_SEND,0,time0,frameApp0,0);
                            frameApp0++;
                            senderBuf0.insert(newFrame);
                            time0++;
                            modifiedOne=Transmission(TRANSMISSIONTYPE_SEND,0,time0,frameApp0,(temp.getDataLength()-frameLength));
                            network.insert(modifiedOne);
                        }
                    if (temp.getApplicationId()==1 && !(temp.getDataLength()<=0))
                        {
                            newFrame=Transmission(TRANSMISSIONTYPE_SEND,1,time1,frameApp1,0);
                            frameApp1++;
                            senderBuf1.insert(newFrame);
                            time1++;
                            modifiedOne=Transmission(TRANSMISSIONTYPE_SEND,1,time1,frameApp1,(temp.getDataLength()-frameLength));
                            network.insert(modifiedOne);
                        }
                }//while !network..

            while(!senderBuf0.isEmpty()|| !senderBuf1.isEmpty() )
                {
                    if(!(ftsh0==ftsl0))
                        {    if(!senderBuf0.isEmpty())
                                {
                                    f=senderBuf0.removeFromQueue();
                                    
                                    cout <<"Time:"<<setw(2)<<f.getTime()<<" Sender Window is now on: "
                                         <<ftsl0<<" through "<<ftsh0<<" frames."<<endl;
                                    cout <<endl;

                                    ftsl0=(ftsl0+1)%winSize;

                                    cout <<"    Frame NO: "<<f.getFrameNo()
                                         <<" of Application: "<<f.getApplicationId()<<" is being sent..."<<endl;
                                    cout <<endl;
                                    cout <<"    Transmission through Buffer: 0 for Application 0"<<endl;
                                    cout<<endl;
                                    g=Transmission(TRANSMISSIONTYPE_ACK,f.getApplicationId(),f.getTime()+bufferServiceTime+2*transmissionTime,
                                        f.getFrameNo(),0);
                                    receiverBuf0.insert(g);
                                    if (!receiverBuf0.isEmpty())
                                        {
                                            h=receiverBuf0.removeFromQueue();
                                            if(f.getTime()==h.getTime())
                                                {
                                                    ftsh0=(ftsh0+1)%winSize;
                                                    cout <<"    ACK has just come for Application: "<<h.getApplicationId()
                                                         <<" Frame: "<<h.getFrameNo()<<endl;
                                                    cout <<endl;
                                                }//if f.getTime....
                                            else receiverBuf0.insert(h);
                                        }//if !receiver...
                                    totalData0 += frameLength;
                                    totalData += frameLength;
                                }//if !sender.buf0.isEmpty()
                        }//if !ftsh0==ftsl0
                    if(!(ftsh1==ftsl1))
                        {
                            if(!senderBuf1.isEmpty())
                                {
                                    f=senderBuf1.removeFromQueue();

                                    cout <<"Time:"<<setw(2)<<f.getTime()<<" Sender Window is now on: "
                                         <<ftsl0<<" through "<<ftsh0<<" frames."<<endl;
                                    cout <<endl;

                                    ftsl1=(ftsl1+1)%winSize;

                                    cout <<"    Frame NO: "<<f.getFrameNo()
                                         <<" of Application: "<<f.getApplicationId()<<" is being sent..."<<endl;
                                    cout <<endl;
                                    cout <<"    Transmission through Buffer: 1 for Application 1"<<endl;
                                    cout<<endl;

                                    g=Transmission(TRANSMISSIONTYPE_ACK,f.getApplicationId(),f.getTime()+bufferServiceTime+2*transmissionTime,
                                        f.getFrameNo(),0);
                                    receiverBuf1.insert(g);
                                    if (!receiverBuf1.isEmpty())
                                        {
                                            i=receiverBuf1.removeFromQueue();
                                            if(f.getTime()==i.getTime())
                                                {
                                                    ftsh1=(ftsh1+1)%winSize;
                                                    cout <<"    ACK has just come for Application: "<<i.getApplicationId()
                                                         <<" Frame: "<<i.getFrameNo()<<endl;
                                                    cout <<endl;
                                                }//if f.getTime....
                                            else receiverBuf1.insert(h);
                                        }//if !receiver...
                                    totalData1 += frameLength;
                                    totalData += frameLength;
                                }//if !senderbuf1.isEmpty()
                        }//if !ftsh0==ftsl0
                }//while !senderbuf0.isEmpty() || !senderBuf1.isEmpty()...
            while(!receiverBuf0.isEmpty() || !receiverBuf1.isEmpty())
                {    if(!receiverBuf0.isEmpty())
                        {
                            h=receiverBuf0.removeFromQueue();
                            cout <<"Time:"<<setw(2)<<h.getTime()<<" ACK has just come for Application: "
                                 <<h.getApplicationId()<<" Frame: "<<h.getFrameNo()<<endl;
                            cout <<endl;
                        }//if !receiverBuf0.isEmpty()...
                    if(!receiverBuf1.isEmpty())
                        {
                            i=receiverBuf1.removeFromQueue();
                            cout <<"Time:"<<setw(2)<<i.getTime()<<" ACK has just come for Application: "
                                 <<i.getApplicationId()<<" Frame: "<<i.getFrameNo()<<endl;
                            cout <<endl;
                        }//if !receiverBuf1.isEmpty()...
                }//while !receiverBuf0....
        }//if numbuffers....
    
        //some information about the transmission process........
    cout <<endl;
    cout <<"SIMULATION RESULTS: "<<endl;
    cout <<"The simulation has accepted applications to get new data for: "<<acceptTime<<" time units"<<endl;
    int simulationLength = (time0 <= time1 ? (time1+bufferServiceTime+2*transmissionTime-1):
                                                (time0+bufferServiceTime+2*transmissionTime-1));
    cout <<"The simulation has lasted in: "<<simulationLength<<" time units"<<endl;
    cout <<"Frame Length is: "<<frameLength<<" bits"<<endl;
    if(numBuffers==1)
        {
            cout <<"There has been "<<totalData<<" bits xmitted."<<endl;
            cout <<"Only one buffer for two applications has been used."<<endl;
            cout <<"Buffer No: 0 has accessed:"<<totalData0<<" bits."<<endl;
        }
    if(numBuffers==2)
        {
            cout <<"There has been "<<totalData<<" bits xmitted"<<endl;
            cout <<"Two buffers, one for each application has been used."<<endl;
            cout <<"Buffer No: 0 has accessed: "<<totalData0<<" bits."<<endl;
            cout <<"Buffer No: 1 has accessed: "<<totalData1<<" bits."<<endl;
        }
}
