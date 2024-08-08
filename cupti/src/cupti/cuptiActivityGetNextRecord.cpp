#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiActivityGetNextRecord)(uint8_t *, size_t, CUpti_Activity **);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiActivityGetNextRecord(uint8_t *buffer, size_t validBufferSizeBytes, CUpti_Activity **record) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiActivityGetNextRecord)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiActivityGetNextRecord = (CUptiResult (*)(uint8_t *, size_t, CUpti_Activity **)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiActivityGetNextRecord");
			fprintf(stderr, "wrapper_cuptiActivityGetNextRecord:%p\n", wrapper_cuptiActivityGetNextRecord);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiActivityGetNextRecord():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiActivityGetNextRecord(buffer, validBufferSizeBytes, record);
		return retval;
	}
}