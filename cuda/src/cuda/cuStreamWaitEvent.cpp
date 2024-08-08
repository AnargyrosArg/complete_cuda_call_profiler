#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuStreamWaitEvent)(CUstream, CUevent, unsigned int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuStreamWaitEvent(CUstream hStream, CUevent hEvent, unsigned int Flags) {
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
				fprintf(stderr, "dlsym error for fntion cuStreamWaitEvent():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuStreamWaitEvent)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuStreamWaitEvent = (CUresult (*)(CUstream, CUevent, unsigned int)) __libc_dlsym(libcuda_handle, "cuStreamWaitEvent");
			fprintf(stderr, "cuStreamWaitEvent:%p\n", original_cuStreamWaitEvent);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuStreamWaitEvent():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuStreamWaitEvent(hStream, hEvent, Flags);
		return retval;
	}
}

