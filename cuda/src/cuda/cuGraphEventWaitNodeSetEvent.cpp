#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphEventWaitNodeSetEvent)(CUgraphNode, CUevent);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphEventWaitNodeSetEvent(CUgraphNode hNode, CUevent event) {
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
				fprintf(stderr, "dlsym error for fntion cuGraphEventWaitNodeSetEvent():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphEventWaitNodeSetEvent)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphEventWaitNodeSetEvent = (CUresult (*)(CUgraphNode, CUevent)) __libc_dlsym(libcuda_handle, "cuGraphEventWaitNodeSetEvent");
			fprintf(stderr, "cuGraphEventWaitNodeSetEvent:%p\n", original_cuGraphEventWaitNodeSetEvent);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphEventWaitNodeSetEvent():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphEventWaitNodeSetEvent(hNode, event);
		return retval;
	}
}

