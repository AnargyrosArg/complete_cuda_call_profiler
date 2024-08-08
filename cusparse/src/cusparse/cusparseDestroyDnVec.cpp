#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDestroyDnVec)(cusparseDnVecDescr_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDestroyDnVec(cusparseDnVecDescr_t dnVecDescr) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDestroyDnVec)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDestroyDnVec = (cusparseStatus_t (*)(cusparseDnVecDescr_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDestroyDnVec");
			fprintf(stderr, "wrapper_cusparseDestroyDnVec:%p\n", wrapper_cusparseDestroyDnVec);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDestroyDnVec():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDestroyDnVec(dnVecDescr);
		return retval;
	}
}