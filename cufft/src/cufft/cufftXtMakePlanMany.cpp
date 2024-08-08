#include <cufftXt.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftXtMakePlanMany)(cufftHandle, int, long long int *, long long int *, long long int, long long int, cudaDataType, long long int *, long long int, long long int, cudaDataType, long long int, size_t *, cudaDataType);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftXtMakePlanMany(cufftHandle plan, int rank, long long int *n, long long int *inembed, long long int istride, long long int idist, cudaDataType inputtype, long long int *onembed, long long int ostride, long long int odist, cudaDataType outputtype, long long int batch, size_t *workSize, cudaDataType executiontype){
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftXtMakePlanMany)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftXtMakePlanMany = (cufftResult (*)(cufftHandle, int, long long int *, long long int *, long long int, long long int, cudaDataType, long long int *, long long int, long long int, cudaDataType, long long int, size_t *, cudaDataType)) dlsym(libwrapper_cufft_handle, "wrapper_cufftXtMakePlanMany");
			fprintf(stderr, "wrapper_cufftXtMakePlanMany:%p\n", wrapper_cufftXtMakePlanMany);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftXtMakePlanMany():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftXtMakePlanMany(plan, rank, n, inembed, istride, idist, inputtype, onembed, ostride, odist, outputtype, batch, workSize, executiontype);
		return retval;
	}
}