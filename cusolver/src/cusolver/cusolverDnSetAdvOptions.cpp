#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnSetAdvOptions)(cusolverDnParams_t, cusolverDnFunction_t, cusolverAlgMode_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnSetAdvOptions(cusolverDnParams_t params, cusolverDnFunction_t function, cusolverAlgMode_t algo) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnSetAdvOptions)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnSetAdvOptions = (cusolverStatus_t (*)(cusolverDnParams_t, cusolverDnFunction_t, cusolverAlgMode_t)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnSetAdvOptions");
			fprintf(stderr, "wrapper_cusolverDnSetAdvOptions:%p\n", wrapper_cusolverDnSetAdvOptions);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnSetAdvOptions():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnSetAdvOptions(params, function, algo);
		return retval;
	}
}