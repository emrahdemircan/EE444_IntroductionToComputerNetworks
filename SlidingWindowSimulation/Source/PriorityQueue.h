#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <iostream>
using namespace std;

template <class T, int MAX_QUEU_SIZE> class PriorityQueue
{
    private:
        int listSize;
        T list[MAX_QUEU_SIZE];
    public:
        PriorityQueue (void);
        bool insert(const T& item);
		int getMinElementIndex(void);
		T removeFromQueue(void);
        void clearQueue(void);
        int isEmpty(void) const;
        int isFull(void) const;
        int getListSize(void) const;
		T getElementAtIndex (int i);
		void changeElementAtIndex(int i, T member);
};

template <class T, int MAX_QUEU_SIZE> PriorityQueue<T,MAX_QUEU_SIZE>::PriorityQueue (void) : listSize(0) {}

template <class T, int MAX_QUEU_SIZE> bool PriorityQueue<T,MAX_QUEU_SIZE>::insert (const T& item)
{
    if(listSize == MAX_QUEU_SIZE)
    {
        cout << "Priority queue overflow!" << endl;
        return false;
    }
    list[listSize] = item;
    listSize++;
    return true;
}

template <class T, int MAX_QUEU_SIZE> int PriorityQueue<T,MAX_QUEU_SIZE>::getMinElementIndex(void)
{
    int i;
    int minindex;
    T min;
    
    if (listSize > 0)
    {
        min = list[0];
        for(i = 1; i < listSize; i++)
        {
            if(list[i] < min)
            {
                // new minimum is list[i]. new minindex is i
                min = list[i];
                minindex = i;
            }
        }
    }
    return minindex;
}

template <class T, int MAX_QUEU_SIZE> T PriorityQueue<T,MAX_QUEU_SIZE>::removeFromQueue(void)
{
    T min;
    int i, minindex = 0;

    if(listSize > 0)
    {
        min = list[0];
        for(i = 1; i < listSize; i++)
        {
            if(list[i] < min)
            {
                // new minimum is list[i]. new minindex is i
                min = list[i];
                minindex = i;
            }
        }
        for(i=(minindex+1); i < listSize; i++)
        {
            list[i-1]=list[i];
        }
        listSize--;
    }
    else
    {
        cout << "Deleting from an empty priority queue!" << endl;
        exit(1);
    }
    return min;
}

template <class T, int MAX_QUEU_SIZE> int PriorityQueue<T,MAX_QUEU_SIZE>::getListSize(void) const
{
    return listSize;
}

template <class T, int MAX_QUEU_SIZE> int PriorityQueue<T,MAX_QUEU_SIZE>::isEmpty(void) const
{
    return listSize == 0;
}

template <class T, int MAX_QUEU_SIZE> int PriorityQueue<T,MAX_QUEU_SIZE>::isFull(void) const
{
    return listSize == MAX_QUEU_SIZE;
}

template <class T, int MAX_QUEU_SIZE> void PriorityQueue<T,MAX_QUEU_SIZE>::clearQueue(void)
{
    listSize = 0;
}
template <class T, int MAX_QUEU_SIZE> T PriorityQueue<T,MAX_QUEU_SIZE>::getElementAtIndex (int i)
{
    return list[i];
}

template <class T, int MAX_QUEU_SIZE> void PriorityQueue<T,MAX_QUEU_SIZE>::changeElementAtIndex(int i, T member)
{
    list[i]=member;
}

#endif 
