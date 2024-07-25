#include <cufftXt.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftXtMemcpy)(cufftHandle, void *, void *, cufftXtCopyType);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftXtMemcpy(cufftHandle plan, void *dstPointer, void *srcPointer, cufftXtCopyType type) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftXtMemcpy)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftXtMemcpy = (cufftResult (*)(cufftHandle, void *, void *, cufftXtCopyType)) dlsym(libwrapper_cufft_handle, "wrapper_cufftXtMemcpy");
			fprintf(stderr, "wrapper_cufftXtMemcpy:%p\n", wrapper_cufftXtMemcpy);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftXtMemcpy():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftXtMemcpy(plan, dstPointer, srcPointer, type);
		return retval;
	}
}