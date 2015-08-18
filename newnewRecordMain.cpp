#include "recordfactory.h"
#include <stdio.h>

#pragma comment( lib,"portaudio_x86.lib" )

#define SAVE_RECORD 1

int main()
{
	RecordFactory factory;
	RecordeInfo info;
	info.channels		 = 1;
	info.framesPerBuffer = 512;
	info.sampleRate		 = 44100;
	info.sampleType		 = SAMPLE_TYPE_UINT8;
	info.seconds		 = 5;

	RecordABC* record = factory.GetRecord( info );
	
	if( record == nullptr )
	{
		fprintf( stderr, "Error:Cannot get record.\n");
		return -1;
	}

	record->StartRecord();

#if SAVE_RECORD
	FILE* file = fopen( "record.raw", "wb" );

	if( file == NULL )
	{
		fprintf( stderr, "Error:Cannot save record.\n" );
		return -1;
	}
	fwrite( record->GetRecordData(), 1, record->GetRecordSize(), file );
	fclose( file );
#endif

}