#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphExecEventWaitNodeSetEvent)(CUgraphExec, CUgraphNode, CUevent);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphExecEventWaitNodeSetEvent(CUgraphExec hGraphExec, CUgraphNode hNode, CUevent event) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphExecEventWaitNodeSetEvent():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphExecEventWaitNodeSetEvent)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphExecEventWaitNodeSetEvent = (CUresult (*)(CUgraphExec, CUgraphNode, CUevent)) __libc_dlsym(libcuda_handle, "cuGraphExecEventWaitNodeSetEvent");
			fprintf(stderr, "cuGraphExecEventWaitNodeSetEvent:%p\n", original_cuGraphExecEventWaitNodeSetEvent);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphExecEventWaitNodeSetEvent():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphExecEventWaitNodeSetEvent(hGraphExec, hNode, event);
		return retval;
	}
}

