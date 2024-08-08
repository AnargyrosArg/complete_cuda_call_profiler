#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphExecEventRecordNodeSetEvent)(CUgraphExec, CUgraphNode, CUevent);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphExecEventRecordNodeSetEvent(CUgraphExec hGraphExec, CUgraphNode hNode, CUevent event) {
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
				fprintf(stderr, "dlsym error for fntion cuGraphExecEventRecordNodeSetEvent():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphExecEventRecordNodeSetEvent)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphExecEventRecordNodeSetEvent = (CUresult (*)(CUgraphExec, CUgraphNode, CUevent)) __libc_dlsym(libcuda_handle, "cuGraphExecEventRecordNodeSetEvent");
			fprintf(stderr, "cuGraphExecEventRecordNodeSetEvent:%p\n", original_cuGraphExecEventRecordNodeSetEvent);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphExecEventRecordNodeSetEvent():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphExecEventRecordNodeSetEvent(hGraphExec, hNode, event);
		return retval;
	}
}

