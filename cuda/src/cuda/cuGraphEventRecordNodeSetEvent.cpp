#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphEventRecordNodeSetEvent)(CUgraphNode, CUevent);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphEventRecordNodeSetEvent(CUgraphNode hNode, CUevent event) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphEventRecordNodeSetEvent():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphEventRecordNodeSetEvent)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphEventRecordNodeSetEvent = (CUresult (*)(CUgraphNode, CUevent)) __libc_dlsym(libcuda_handle, "cuGraphEventRecordNodeSetEvent");
			fprintf(stderr, "cuGraphEventRecordNodeSetEvent:%p\n", original_cuGraphEventRecordNodeSetEvent);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphEventRecordNodeSetEvent():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphEventRecordNodeSetEvent(hNode, event);
		return retval;
	}
}

