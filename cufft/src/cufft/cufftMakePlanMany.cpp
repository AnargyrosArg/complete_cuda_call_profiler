#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftMakePlanMany)(cufftHandle, int, int *, int *, int, int, int *, int, int, cufftType, int, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftMakePlanMany(cufftHandle plan, int rank, int *n, int *inembed, int istride, int idist, int *onembed, int ostride, int odist, cufftType type, int batch, size_t *workSize){
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftMakePlanMany)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftMakePlanMany = (cufftResult (*)(cufftHandle, int, int *, int *, int, int, int *, int, int, cufftType, int, size_t *)) dlsym(libwrapper_cufft_handle, "wrapper_cufftMakePlanMany");
			fprintf(stderr, "wrapper_cufftMakePlanMany:%p\n", wrapper_cufftMakePlanMany);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftMakePlanMany():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftMakePlanMany(plan, rank, n, inembed, istride, idist, onembed, ostride, odist, type, batch, workSize);
		return retval;
	}
}