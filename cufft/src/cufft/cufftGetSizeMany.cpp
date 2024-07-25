#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftGetSizeMany)(cufftHandle, int, int *, int *, int, int, int *, int, int, cufftType, int, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftGetSizeMany(cufftHandle handle, int rank, int *n, int *inembed, int istride, int idist, int *onembed, int ostride, int odist, cufftType type, int batch, size_t *workArea) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftGetSizeMany)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftGetSizeMany = (cufftResult (*)(cufftHandle, int, int *, int *, int, int, int *, int, int, cufftType, int, size_t *)) dlsym(libwrapper_cufft_handle, "wrapper_cufftGetSizeMany");
			fprintf(stderr, "wrapper_cufftGetSizeMany:%p\n", wrapper_cufftGetSizeMany);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftGetSizeMany():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftGetSizeMany(handle, rank, n, inembed, istride, idist, onembed, ostride, odist, type, batch, workArea);
		return retval;
	}
}