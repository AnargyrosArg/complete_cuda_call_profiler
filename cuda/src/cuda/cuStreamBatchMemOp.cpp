#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuStreamBatchMemOp)(CUstream, unsigned int, CUstreamBatchMemOpParams *, unsigned int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuStreamBatchMemOp(CUstream stream, unsigned int count, CUstreamBatchMemOpParams *paramArray, unsigned int flags) {
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
				fprintf(stderr, "dlsym error for fntion cuStreamBatchMemOp():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuStreamBatchMemOp)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuStreamBatchMemOp = (CUresult (*)(CUstream, unsigned int, CUstreamBatchMemOpParams *, unsigned int)) __libc_dlsym(libcuda_handle, "cuStreamBatchMemOp");
			fprintf(stderr, "cuStreamBatchMemOp:%p\n", original_cuStreamBatchMemOp);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuStreamBatchMemOp():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuStreamBatchMemOp(stream, count, paramArray, flags);
		return retval;
	}
}

