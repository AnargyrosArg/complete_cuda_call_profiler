#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftEstimateMany)(int, int *, int *, int, int, int *, int, int, cufftType, int, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftEstimateMany(int rank, int *n, int *inembed, int istride, int idist, int *onembed, int ostride, int odist, cufftType type, int batch, size_t *workSize){
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftEstimateMany)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftEstimateMany = (cufftResult (*)(int, int *, int *, int, int, int *, int, int, cufftType, int, size_t *)) dlsym(libwrapper_cufft_handle, "wrapper_cufftEstimateMany");
			fprintf(stderr, "wrapper_cufftEstimateMany:%p\n", wrapper_cufftEstimateMany);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftEstimateMany():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftEstimateMany(rank, n, inembed, istride, idist, onembed, ostride, odist, type, batch, workSize);
		return retval;
	}
}