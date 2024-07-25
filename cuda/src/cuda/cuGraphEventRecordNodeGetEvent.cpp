#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphEventRecordNodeGetEvent)(CUgraphNode, CUevent *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphEventRecordNodeGetEvent(CUgraphNode hNode, CUevent *event_out) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphEventRecordNodeGetEvent():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphEventRecordNodeGetEvent)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphEventRecordNodeGetEvent = (CUresult (*)(CUgraphNode, CUevent *)) __libc_dlsym(libcuda_handle, "cuGraphEventRecordNodeGetEvent");
			fprintf(stderr, "cuGraphEventRecordNodeGetEvent:%p\n", original_cuGraphEventRecordNodeGetEvent);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphEventRecordNodeGetEvent():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphEventRecordNodeGetEvent(hNode, event_out);
		return retval;
	}
}

