#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverGetProperty)(libraryPropertyType, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverGetProperty(libraryPropertyType type, int *value) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverGetProperty)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverGetProperty = (cusolverStatus_t (*)(libraryPropertyType, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverGetProperty");
			fprintf(stderr, "wrapper_cusolverGetProperty:%p\n", wrapper_cusolverGetProperty);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverGetProperty():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverGetProperty(type, value);
		return retval;
	}
}