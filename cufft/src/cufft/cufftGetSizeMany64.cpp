#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftGetSizeMany64)(cufftHandle, int, long long int *, long long int *, long long int, long long int, long long int *, long long int, long long int, cufftType, long long int, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftGetSizeMany64(cufftHandle plan, int rank, long long int *n, long long int *inembed, long long int istride, long long int idist, long long int *onembed, long long int ostride, long long int odist, cufftType type, long long int batch, size_t *workSize){
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftGetSizeMany64)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftGetSizeMany64 = (cufftResult (*)(cufftHandle, int, long long int *, long long int *, long long int, long long int, long long int *, long long int, long long int, cufftType, long long int, size_t *)) dlsym(libwrapper_cufft_handle, "wrapper_cufftGetSizeMany64");
			fprintf(stderr, "wrapper_cufftGetSizeMany64:%p\n", wrapper_cufftGetSizeMany64);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftGetSizeMany64():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftGetSizeMany64(plan, rank, n, inembed, istride, idist, onembed, ostride, odist, type, batch, workSize);
		return retval;
	}
}