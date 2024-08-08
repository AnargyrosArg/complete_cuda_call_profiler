#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseIndexBase_t (*wrapper_cusparseGetMatIndexBase)(const cusparseMatDescr_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseIndexBase_t cusparseGetMatIndexBase(const cusparseMatDescr_t descrA) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseGetMatIndexBase)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseGetMatIndexBase = (cusparseIndexBase_t (*)(const cusparseMatDescr_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseGetMatIndexBase");
			fprintf(stderr, "wrapper_cusparseGetMatIndexBase:%p\n", wrapper_cusparseGetMatIndexBase);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseGetMatIndexBase():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseIndexBase_t retval = wrapper_cusparseGetMatIndexBase(descrA);
		return retval;
	}
}