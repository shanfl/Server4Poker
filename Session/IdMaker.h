
#ifndef __LP_UNIQUEID_H__
#define __LP_UNIQUEID_H__

#include <inttypes.h>
#include <mutex>

#ifdef _WIN32
#include <windows.h>
#define EPOCHFILETIME 11644473600000000Ui64
#endif

namespace System
{
	uint64_t currentTimeMillis();
}

class IdMaker {
public:
    IdMaker(int64_t dataCenterId, int64_t workerId);

    IdMaker();

    void SetWorkerIdentity(int dataCenterId, int workerId);

    /**
    * 获得下一个ID (该方法是线程安全的)
    * @return snowflakeId
    */
    int64_t nextId();
private:
	/**
	* 起始时间戳 2017-04-01
	*/
	int64_t epoch = 1491004800000L;  // 毫秒
	/**
	* 机器ID所占的位数
	*/
	int64_t workerIdBits = 5L;
	/**
	* 数据标识ID所占的位数
	*/
	int64_t dataCenterIdBits = 5L;
	/**
	* 支持的最大机器ID,结果是31
	*/
	int64_t maxWorkerId = ~(-1L << workerIdBits);
	/**
	* 支持的最大数据标识ID,结果是31
	*/
	int64_t maxDataCenterId = ~(-1 << dataCenterIdBits);
	/**
	* 毫秒内序列在id中所占的位数
	*/
	int64_t sequenceBits = 12L;
	/**
	* 机器ID向左移12位
	*/
	int64_t workerIdShift = sequenceBits;
	/**
	* 数据标识ID向左移17(12+5)位
	*/
	int64_t dataCenterIdShift = sequenceBits + workerIdBits;
	/**
	* 时间戳向左移22(12+5+5)位
	*/
	int64_t timestampShift = sequenceBits + workerIdBits + dataCenterIdBits;
	/**
	* 生成序列的掩码，这里为4095 (0b111111111111=0xfff=4095)
	*/
	int64_t sequenceMask = ~(-1L << sequenceBits);
	/**
	* 数据标识ID（0～31）
	*/
	int64_t dataCenterId;
	/**
	* 机器ID（0～31）
	*/
	int64_t workerId;
	/**
	* 毫秒内序列（0～4095）
	*/
	int64_t sequence;
	/**
	* 上次生成ID的时间戳
	*/
	int64_t lastTimestamp = 0L;

	std::mutex mutexForGen;

	/**
	* 返回以毫秒为单位的当前时间
	* @return 当前时间(毫秒)
	*/
	int64_t timeGen();

	/**
	* 阻塞到下一个毫秒，直到获得新的时间戳
	* @param lastTimestamp 上次生成ID的时间截
	* @return 当前时间戳
	*/
	int64_t nextMillis(int64_t lastTimestamp);
};

#endif
