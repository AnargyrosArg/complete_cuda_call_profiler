#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuStreamSetAttribute)(CUstream, CUstreamAttrID, const CUstreamAttrValue *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuStreamSetAttribute(CUstream hStream, CUstreamAttrID attr, const CUstreamAttrValue *value) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuStreamSetAttribute():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuStreamSetAttribute)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuStreamSetAttribute = (CUresult (*)(CUstream, CUstreamAttrID, const CUstreamAttrValue *)) __libc_dlsym(libcuda_handle, "cuStreamSetAttribute");
			fprintf(stderr, "cuStreamSetAttribute:%p\n", original_cuStreamSetAttribute);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuStreamSetAttribute():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuStreamSetAttribute(hStream, attr, value);
		return retval;
	}
}

