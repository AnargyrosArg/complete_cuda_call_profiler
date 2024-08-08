#include <cufftXt.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftXtQueryPlan)(cufftHandle, void *, cufftXtQueryType);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftXtQueryPlan(cufftHandle plan, void *queryStruct, cufftXtQueryType queryType){
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftXtQueryPlan)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftXtQueryPlan = (cufftResult (*)(cufftHandle, void *, cufftXtQueryType)) dlsym(libwrapper_cufft_handle, "wrapper_cufftXtQueryPlan");
			fprintf(stderr, "wrapper_cufftXtQueryPlan:%p\n", wrapper_cufftXtQueryPlan);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftXtQueryPlan():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftXtQueryPlan(plan, queryStruct, queryType);
		return retval;
	}
}