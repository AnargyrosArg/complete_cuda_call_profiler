#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuStreamGetAttribute)(CUstream, CUstreamAttrID, CUstreamAttrValue *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuStreamGetAttribute(CUstream hStream, CUstreamAttrID attr, CUstreamAttrValue *value_out) {
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
				fprintf(stderr, "dlsym error for fntion cuStreamGetAttribute():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuStreamGetAttribute)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuStreamGetAttribute = (CUresult (*)(CUstream, CUstreamAttrID, CUstreamAttrValue *)) __libc_dlsym(libcuda_handle, "cuStreamGetAttribute");
			fprintf(stderr, "cuStreamGetAttribute:%p\n", original_cuStreamGetAttribute);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuStreamGetAttribute():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuStreamGetAttribute(hStream, attr, value_out);
		return retval;
	}
}

