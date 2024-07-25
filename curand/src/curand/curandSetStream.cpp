#include <curand.h>
#include <dlfcn.h>
#include <iostream>
curandStatus_t (*wrapper_curandSetStream)(curandGenerator_t, cudaStream_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_curand_handle;
extern "C"
{
	curandStatus_t curandSetStream(curandGenerator_t generator, cudaStream_t stream) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_curand_handle == NULL){
			libwrapper_curand_handle = dlopen("libwrapper_curand.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_curandSetStream)
		{
			//fetch the original function addr using dlsym
			wrapper_curandSetStream = (curandStatus_t (*)(curandGenerator_t, cudaStream_t)) dlsym(libwrapper_curand_handle, "wrapper_curandSetStream");
			fprintf(stderr, "wrapper_curandSetStream:%p\n", wrapper_curandSetStream);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function curandSetStream():%s\n", __dlerror);
			fflush(stderr);
		}
		curandStatus_t retval = wrapper_curandSetStream(generator, stream);
		return retval;
	}
}