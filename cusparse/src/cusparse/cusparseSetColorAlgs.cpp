#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSetColorAlgs)(cusparseColorInfo_t, cusparseColorAlg_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSetColorAlgs(cusparseColorInfo_t info, cusparseColorAlg_t alg) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSetColorAlgs)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSetColorAlgs = (cusparseStatus_t (*)(cusparseColorInfo_t, cusparseColorAlg_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSetColorAlgs");
			fprintf(stderr, "wrapper_cusparseSetColorAlgs:%p\n", wrapper_cusparseSetColorAlgs);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSetColorAlgs():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSetColorAlgs(info, alg);
		return retval;
	}
}