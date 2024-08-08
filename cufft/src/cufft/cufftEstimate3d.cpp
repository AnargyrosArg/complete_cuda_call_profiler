#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftEstimate3d)(int, int, int, cufftType, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftEstimate3d(int nx, int ny, int nz, cufftType type, size_t *workSize){
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftEstimate3d)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftEstimate3d = (cufftResult (*)(int, int, int, cufftType, size_t *)) dlsym(libwrapper_cufft_handle, "wrapper_cufftEstimate3d");
			fprintf(stderr, "wrapper_cufftEstimate3d:%p\n", wrapper_cufftEstimate3d);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftEstimate3d():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftEstimate3d(nx, ny, nz, type, workSize);
		return retval;
	}
}