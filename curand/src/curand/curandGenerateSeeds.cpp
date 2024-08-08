#include <curand.h>
#include <dlfcn.h>
#include <iostream>
curandStatus_t (*wrapper_curandGenerateSeeds)(curandGenerator_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_curand_handle;
extern "C"
{
	curandStatus_t curandGenerateSeeds(curandGenerator_t generator) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_curand_handle == NULL){
			libwrapper_curand_handle = dlopen("libwrapper_curand.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_curandGenerateSeeds)
		{
			//fetch the original function addr using dlsym
			wrapper_curandGenerateSeeds = (curandStatus_t (*)(curandGenerator_t)) dlsym(libwrapper_curand_handle, "wrapper_curandGenerateSeeds");
			fprintf(stderr, "wrapper_curandGenerateSeeds:%p\n", wrapper_curandGenerateSeeds);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function curandGenerateSeeds():%s\n", __dlerror);
			fflush(stderr);
		}
		curandStatus_t retval = wrapper_curandGenerateSeeds(generator);
		return retval;
	}
}