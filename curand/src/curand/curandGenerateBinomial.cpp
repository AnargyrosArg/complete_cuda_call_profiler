#include <curand.h>
#include <dlfcn.h>
#include <iostream>
curandStatus_t (*wrapper_curandGenerateBinomial)(curandGenerator_t, unsigned int *, size_t, unsigned int, double);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_curand_handle;
extern "C"
{
	curandStatus_t curandGenerateBinomial(curandGenerator_t generator, unsigned int *outputPtr, size_t num, unsigned int n, double p) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_curand_handle == NULL){
			libwrapper_curand_handle = dlopen("libwrapper_curand.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_curandGenerateBinomial)
		{
			//fetch the original function addr using dlsym
			wrapper_curandGenerateBinomial = (curandStatus_t (*)(curandGenerator_t, unsigned int *, size_t, unsigned int, double)) dlsym(libwrapper_curand_handle, "wrapper_curandGenerateBinomial");
			fprintf(stderr, "wrapper_curandGenerateBinomial:%p\n", wrapper_curandGenerateBinomial);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function curandGenerateBinomial():%s\n", __dlerror);
			fflush(stderr);
		}
		curandStatus_t retval = wrapper_curandGenerateBinomial(generator, outputPtr, num, n, p);
		return retval;
	}
}