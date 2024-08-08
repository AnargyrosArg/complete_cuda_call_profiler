#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSpVecGet)(cusparseSpVecDescr_t, int64_t *, int64_t *, void **, void **, cusparseIndexType_t *, cusparseIndexBase_t *, cudaDataType *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSpVecGet(cusparseSpVecDescr_t spVecDescr, int64_t *size, int64_t *nnz, void **indices, void **values, cusparseIndexType_t *idxType, cusparseIndexBase_t *idxBase, cudaDataType *valueType) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSpVecGet)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSpVecGet = (cusparseStatus_t (*)(cusparseSpVecDescr_t, int64_t *, int64_t *, void **, void **, cusparseIndexType_t *, cusparseIndexBase_t *, cudaDataType *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSpVecGet");
			fprintf(stderr, "wrapper_cusparseSpVecGet:%p\n", wrapper_cusparseSpVecGet);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSpVecGet():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSpVecGet(spVecDescr, size, nnz, indices, values, idxType, idxBase, valueType);
		return retval;
	}
}