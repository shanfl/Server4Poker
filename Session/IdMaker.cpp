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
* 获得下一个ID (该方法是线程安全的)
* @return snowflakeId
*/
int64_t IdMaker::nextId() {
	std::lock_guard<std::mutex> locker(mutexForGen);

	int64_t timestamp = timeGen();
	//如果当前时间小于上一次ID生成的时间戳,说明系统时钟回退过,这个时候应当抛出异常
	if (timestamp < lastTimestamp) {
        std::clog << " error!" << std::endl;
    }
	//如果是同一时间生成的，则进行毫秒内序列
	if (timestamp == lastTimestamp) {
		sequence = (sequence + 1) & sequenceMask;
		//毫秒内序列溢出
		if (sequence == 0) {
			//阻塞到下一个毫秒,获得新的时间戳
			timestamp = nextMillis(lastTimestamp);
		}
	}
	else {//时间戳改变，毫秒内序列重置
		sequence = 0L;
	}
	lastTimestamp = timestamp;
	//移位并通过按位或运算拼到一起组成64位的ID
	
	// 如果采用 CenterId + workid 的方式 ,CenterId和 workid 各占5位,一共占10位 ,CenterId 和workid 都不能大于2^5
	// 如果超过5位,这里只用了 centerId,但是centid不能超过 10位;
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
* 返回以毫秒为单位的当前时间
* @return 当前时间(毫秒)
*/
int64_t IdMaker::timeGen()
{
	return System::currentTimeMillis();
}

/**
* 阻塞到下一个毫秒，直到获得新的时间戳
* @param lastTimestamp 上次生成ID的时间截
* @return 当前时间戳
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


