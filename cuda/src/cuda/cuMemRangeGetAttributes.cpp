#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemRangeGetAttributes)(void **, size_t *, CUmem_range_attribute *, size_t, CUdeviceptr, size_t);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemRangeGetAttributes(void **data, size_t *dataSizes, CUmem_range_attribute *attributes, size_t numAttributes, CUdeviceptr devPtr, size_t count) {
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
				fprintf(stderr, "dlsym error for fntion cuMemRangeGetAttributes():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemRangeGetAttributes)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemRangeGetAttributes = (CUresult (*)(void **, size_t *, CUmem_range_attribute *, size_t, CUdeviceptr, size_t)) __libc_dlsym(libcuda_handle, "cuMemRangeGetAttributes");
			fprintf(stderr, "cuMemRangeGetAttributes:%p\n", original_cuMemRangeGetAttributes);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemRangeGetAttributes():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemRangeGetAttributes(data, dataSizes, attributes, numAttributes, devPtr, count);
		return retval;
	}
}

