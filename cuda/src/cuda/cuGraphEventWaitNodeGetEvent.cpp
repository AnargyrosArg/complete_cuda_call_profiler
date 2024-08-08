#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphEventWaitNodeGetEvent)(CUgraphNode, CUevent *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphEventWaitNodeGetEvent(CUgraphNode hNode, CUevent *event_out) {
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
				fprintf(stderr, "dlsym error for fntion cuGraphEventWaitNodeGetEvent():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphEventWaitNodeGetEvent)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphEventWaitNodeGetEvent = (CUresult (*)(CUgraphNode, CUevent *)) __libc_dlsym(libcuda_handle, "cuGraphEventWaitNodeGetEvent");
			fprintf(stderr, "cuGraphEventWaitNodeGetEvent:%p\n", original_cuGraphEventWaitNodeGetEvent);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphEventWaitNodeGetEvent():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphEventWaitNodeGetEvent(hNode, event_out);
		return retval;
	}
}

