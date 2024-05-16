#include "IdMaker.h"
#include <assert.h>
#include <time.h>
#ifdef __GNUC__
#include <sys/time.h>
#endif
#include <iostream>

namespace System
{
	uint64_t currentTimeMillis()
	{
#ifdef __GNUC__
		struct timeval tv;
		gettimeofday(&tv, NULL);
		uint64_t time = tv.tv_usec;
		time /= 1000;
		time += (tv.tv_sec * 1000);
		return time;
#else
		FILETIME filetime;
		uint64_t time = 0;
		GetSystemTimeAsFileTime(&filetime);

		time |= filetime.dwHighDateTime;
		time <<= 32;
		time |= filetime.dwLowDateTime;

		time /= 10;
		time -= EPOCHFILETIME;
		return time / 1000;
#endif
	}
}


IdMaker::IdMaker(int64_t dataCenterId, int64_t workerId)
{
	SetWorkerIdentity(dataCenterId,workerId);
}

IdMaker::IdMaker()
{
	SetWorkerIdentity(0,0);
}

void IdMaker::SetWorkerIdentity(int dataCenterId, int workerId)
{
	assert(dataCenterId <= maxDataCenterId && workerId <= maxWorkerId);
	this->dataCenterId = dataCenterId;
	this->workerId = workerId;
}

/**
* �����һ��ID (�÷������̰߳�ȫ��)
* @return snowflakeId
*/
int64_t IdMaker::nextId() {
	std::lock_guard<std::mutex> locker(mutexForGen);

	int64_t timestamp = timeGen();
	//�����ǰʱ��С����һ��ID���ɵ�ʱ���,˵��ϵͳʱ�ӻ��˹�,���ʱ��Ӧ���׳��쳣
	if (timestamp < lastTimestamp) {
        std::clog << " error!" << std::endl;
    }
	//�����ͬһʱ�����ɵģ�����к���������
	if (timestamp == lastTimestamp) {
		sequence = (sequence + 1) & sequenceMask;
		//�������������
		if (sequence == 0) {
			//��������һ������,����µ�ʱ���
			timestamp = nextMillis(lastTimestamp);
		}
	}
	else {//ʱ����ı䣬��������������
		sequence = 0L;
	}
	lastTimestamp = timestamp;
	//��λ��ͨ����λ������ƴ��һ�����64λ��ID
	
	// ������� CenterId + workid �ķ�ʽ ,CenterId�� workid ��ռ5λ,һ��ռ10λ ,CenterId ��workid �����ܴ���2^5
	// �������5λ,����ֻ���� centerId,����centid���ܳ��� 10λ;
	int64_t value  =  ((timestamp - epoch) << timestampShift) |
#if 0
		(dataCenterId << dataCenterIdShift) |
		(workerId << workerIdShift) |
#endif
		dataCenterId  << workerIdShift |
		sequence;
	return value;
}

/**
* �����Ժ���Ϊ��λ�ĵ�ǰʱ��
* @return ��ǰʱ��(����)
*/
int64_t IdMaker::timeGen()
{
	return System::currentTimeMillis();
}

/**
* ��������һ�����룬ֱ������µ�ʱ���
* @param lastTimestamp �ϴ�����ID��ʱ���
* @return ��ǰʱ���
*/
int64_t IdMaker::nextMillis(int64_t lastTimestamp)
{
	int64_t timestamp = timeGen();
	while (timestamp <= lastTimestamp) 
	{
		timestamp = timeGen();
	}
	return timestamp;
}


