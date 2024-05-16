
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
    * �����һ��ID (�÷������̰߳�ȫ��)
    * @return snowflakeId
    */
    int64_t nextId();
private:
	/**
	* ��ʼʱ��� 2017-04-01
	*/
	int64_t epoch = 1491004800000L;  // ����
	/**
	* ����ID��ռ��λ��
	*/
	int64_t workerIdBits = 5L;
	/**
	* ���ݱ�ʶID��ռ��λ��
	*/
	int64_t dataCenterIdBits = 5L;
	/**
	* ֧�ֵ�������ID,�����31
	*/
	int64_t maxWorkerId = ~(-1L << workerIdBits);
	/**
	* ֧�ֵ�������ݱ�ʶID,�����31
	*/
	int64_t maxDataCenterId = ~(-1 << dataCenterIdBits);
	/**
	* ������������id����ռ��λ��
	*/
	int64_t sequenceBits = 12L;
	/**
	* ����ID������12λ
	*/
	int64_t workerIdShift = sequenceBits;
	/**
	* ���ݱ�ʶID������17(12+5)λ
	*/
	int64_t dataCenterIdShift = sequenceBits + workerIdBits;
	/**
	* ʱ���������22(12+5+5)λ
	*/
	int64_t timestampShift = sequenceBits + workerIdBits + dataCenterIdBits;
	/**
	* �������е����룬����Ϊ4095 (0b111111111111=0xfff=4095)
	*/
	int64_t sequenceMask = ~(-1L << sequenceBits);
	/**
	* ���ݱ�ʶID��0��31��
	*/
	int64_t dataCenterId;
	/**
	* ����ID��0��31��
	*/
	int64_t workerId;
	/**
	* ���������У�0��4095��
	*/
	int64_t sequence;
	/**
	* �ϴ�����ID��ʱ���
	*/
	int64_t lastTimestamp = 0L;

	std::mutex mutexForGen;

	/**
	* �����Ժ���Ϊ��λ�ĵ�ǰʱ��
	* @return ��ǰʱ��(����)
	*/
	int64_t timeGen();

	/**
	* ��������һ�����룬ֱ������µ�ʱ���
	* @param lastTimestamp �ϴ�����ID��ʱ���
	* @return ��ǰʱ���
	*/
	int64_t nextMillis(int64_t lastTimestamp);
};

#endif
