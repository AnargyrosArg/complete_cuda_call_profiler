#include <curand.h>
#include <dlfcn.h>
#include <iostream>
curandStatus_t (*wrapper_curandGetVersion)(int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_curand_handle;
extern "C"
{
	curandStatus_t curandGetVersion(int *version) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_curand_handle == NULL){
			libwrapper_curand_handle = dlopen("libwrapper_curand.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_curandGetVersion)
		{
			//fetch the original function addr using dlsym
			wrapper_curandGetVersion = (curandStatus_t (*)(int *)) dlsym(libwrapper_curand_handle, "wrapper_curandGetVersion");
			fprintf(stderr, "wrapper_curandGetVersion:%p\n", wrapper_curandGetVersion);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function curandGetVersion():%s\n", __dlerror);
			fflush(stderr);
		}
		curandStatus_t retval = wrapper_curandGetVersion(version);
		return retval;
	}
}