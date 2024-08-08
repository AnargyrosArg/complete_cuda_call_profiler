/*#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
void (*original_CUstreamCallback)(CUstream, CUresult, void *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	void CUstreamCallback(CUstream hStream, CUresult status, void *userData) {
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
				fprintf(stderr, "dlsym error for fntion CUstreamCallback():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_CUstreamCallback)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_CUstreamCallback = (void (*)(CUstream, CUresult, void *)) __libc_dlsym(libcuda_handle, "custreamCallback");
			fprintf(stderr, "custreamCallback:%p\n", original_CUstreamCallback);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion CUstreamCallback():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		original_CUstreamCallback(hStream, status, userData);
	}
}
*/


