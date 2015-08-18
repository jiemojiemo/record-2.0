#pragma once

#include "portaudio.h"

typedef unsigned long SampleType;
#define SAMPLE_TYPE_FLOAT32 ((SampleType) 0x00000001)
#define SAMPLE_TYPE_INT32	((SampleType) 0x00000002)
#define SAMPLE_TYPE_INT24	((SampleType) 0x00000004)
#define SAMPLE_TYPE_INT16   ((SampleType) 0x00000008)
#define SAMPLE_TYPE_INT8    ((SampleType) 0x00000010)
#define SAMPLE_TYPE_UINT8   ((SampleType) 0x00000020)

struct RecordeInfo
{
	unsigned int seconds;
	unsigned int channels;
	unsigned int sampleRate;
	SampleType sampleType;
	unsigned int framesPerBuffer;
};

struct RecordData{
	int          frameIndex;  /* Index into sample array. */
	int          maxFrameIndex;
	unsigned long totalBytes;
	void	     *recordedSamples;
};

typedef int (*callbackPointer)( const void*, void*, unsigned long,
	const PaStreamCallbackTimeInfo*,
	PaStreamCallbackFlags,
	void*);


class RecordABC{
private:
	RecordABC( const RecordABC& re ){}
	RecordABC& operator=( const RecordABC& re ){}

	/**
	* @brief : 根据bits获得format
	*/
	PaSampleFormat GetSampleFormat();
	virtual void MallocForData() = 0;
protected:
	static RecordeInfo m_info;
	RecordData  m_data;
	callbackPointer m_pCallback;
public:
	RecordABC( );
	virtual ~RecordABC();
	void* GetRecordData()const{ return m_data.recordedSamples; }
	unsigned long GetRecordSize()const { return m_data.totalBytes; }
	/**
	* @brief : 根据录音参数，进行录音
	*/
	int StartRecord();

};

class RecordFloat32 : public RecordABC{
private:
	virtual void MallocForData();
	static int recordCallback(
		const void *inputBuffer, void *outputBuffer,
		unsigned long framesPerBuffer,
		const PaStreamCallbackTimeInfo* timeInfo,
		PaStreamCallbackFlags statusFlags,
		void *userData);
public:
	RecordFloat32( const RecordeInfo& info );
	~RecordFloat32();
};

class RecordInt16 : public RecordABC{
private:
	virtual void MallocForData();
	static int recordCallback(const void *inputBuffer, void *outputBuffer,
		unsigned long framesPerBuffer,
		const PaStreamCallbackTimeInfo* timeInfo,
		PaStreamCallbackFlags statusFlags,
		void *userData);
public:
	RecordInt16( const RecordeInfo& info );
	~RecordInt16();
};

class RecordInt8 : public RecordABC{
private:
	virtual void MallocForData();
	static int recordCallback(
		const void *inputBuffer, void *outputBuffer,
		unsigned long framesPerBuffer,
		const PaStreamCallbackTimeInfo* timeInfo,
		PaStreamCallbackFlags statusFlags,
		void *userData);
public:
	RecordInt8( const RecordeInfo& info );
	~RecordInt8();
};

class RecordUInt8 : public RecordABC{
private:
	virtual void MallocForData();
	static int recordCallback(
		const void *inputBuffer, void *outputBuffer,
		unsigned long framesPerBuffer,
		const PaStreamCallbackTimeInfo* timeInfo,
		PaStreamCallbackFlags statusFlags,
		void *userData);
public:
	RecordUInt8( const RecordeInfo& info );
	~RecordUInt8();
};