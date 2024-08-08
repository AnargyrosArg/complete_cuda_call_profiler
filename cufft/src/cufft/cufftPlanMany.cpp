#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftPlanMany)(cufftHandle *, int, int *, int *, int, int, int *, int, int, cufftType, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftPlanMany(cufftHandle *plan, int rank, int *n, int *inembed, int istride, int idist, int *onembed, int ostride, int odist, cufftType type, int batch){
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftPlanMany)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftPlanMany = (cufftResult (*)(cufftHandle *, int, int *, int *, int, int, int *, int, int, cufftType, int)) dlsym(libwrapper_cufft_handle, "wrapper_cufftPlanMany");
			fprintf(stderr, "wrapper_cufftPlanMany:%p\n", wrapper_cufftPlanMany);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftPlanMany():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftPlanMany(plan, rank, n, inembed, istride, idist, onembed, ostride, odist, type, batch);
		return retval;
	}
}