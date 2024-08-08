/*#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
size_t (*original_CUoccupancyB2DSize)(int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	size_t CUoccupancyB2DSize(int blockSize) {
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
				fprintf(stderr, "dlsym error for fntion CUoccupancyB2DSize():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_CUoccupancyB2DSize)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_CUoccupancyB2DSize = (size_t (*)(int)) __libc_dlsym(libcuda_handle, "cuoccupancyB2DSize");
			fprintf(stderr, "cuoccupancyB2DSize:%p\n", original_CUoccupancyB2DSize);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion CUoccupancyB2DSize():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		size_t retval = original_CUoccupancyB2DSize(blockSize);
		return retval;
	}
}
*/


