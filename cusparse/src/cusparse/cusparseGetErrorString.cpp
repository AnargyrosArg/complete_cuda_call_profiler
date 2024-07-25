#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
const char * (*wrapper_cusparseGetErrorString)(
cusparseStatus_t
);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	const char * cusparseGetErrorString(cusparseStatus_t status) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseGetErrorString)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseGetErrorString = (const char * (*)(
			cusparseStatus_t)
			) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseGetErrorString");
			fprintf(stderr, "wrapper_cusparseGetErrorString:%p\n", wrapper_cusparseGetErrorString);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseGetErrorString():%s\n", __dlerror);
			fflush(stderr);
		}
		const char * retval = wrapper_cusparseGetErrorString(
		status
		);
		
		return retval;
	}
}