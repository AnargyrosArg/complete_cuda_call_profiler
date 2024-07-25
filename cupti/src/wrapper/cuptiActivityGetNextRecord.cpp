#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiActivityGetNextRecord(uint8_t *buffer, size_t validBufferSizeBytes, CUpti_Activity **record)
{
	CUptiResult retval = cuptiActivityGetNextRecord(buffer, validBufferSizeBytes, record);
	return retval;
}