#include <cuda_runtime_api.h>
#include <cuda.h>
#include <cuda_runtime.h>
#include <iostream>
#include <cstring>
#include <dlfcn.h>

extern void* original_libcuda_handle;
CUresult (*original_cuGetExportTable)(
	const void **, const CUuuid *
	);


struct cuGetExportTable_ArgStruct {
	const void **ppExportTable;
	const CUuuid pExportTableId;
	CUresult _ret_;
};

int generic_return_zero(){
	// std::cerr << __func__ << "() Called!!!!!!!!!!!\n";
	return 0;
}

// dummy function for slots that we dont expect to be called
template<int N>
int exportFn()
{
	std::cerr << __func__ << "<" << N << ">() Called!!!!!!!!!!!\n";
	return 0;
}

//Function for ExportTable_1 SLOT:3 (index 2)
int ET1_SLOT3(void** var_addr){
	*var_addr = NULL;
	// std::cerr << __func__ <<"() Called!!!!!!!!!!!\n";
	//0 is CUDA_SUCCESS (or equivalent for cuda driver API)
	return 0;
}


static const void * ExportTable_1[] =
{
	//TODO: PUT CORRECT VAL HERE
	(void*)0x18,
	(void*)&exportFn<1001>,
	(void*)&ET1_SLOT3
};



static const void * ExportTable_2[]= 
{
	(void*)&exportFn<2000>,
	(void*)&exportFn<2001>,
	(void*)&exportFn<2002>,
	(void*)&exportFn<2003>,
	// (void*)&exportFn<2004>,
	(void*)&generic_return_zero,
	(void*)&exportFn<2005>,
	(void*)&exportFn<2006>,
	(void*)&exportFn<2007>,
	(void*)&exportFn<2008>,
	(void*)&exportFn<2009>,
	(void*)&exportFn<2010>,
	(void*)&exportFn<2011>,
	(void*)&exportFn<2012>,
	(void*)&exportFn<2013>,
	(void*)&exportFn<2014>,
	(void*)&exportFn<2015>,
	(void*)&exportFn<2016>,
	(void*)&exportFn<2017>,
	(void*)&exportFn<2018>,
	(void*)&exportFn<2019>,
	(void*)&exportFn<2020>,
	(void*)&exportFn<2021>,
	(void*)&exportFn<2022>,
	(void*)&exportFn<2023>,
	(void*)&exportFn<2024>,
	(void*)&exportFn<2025>,
	(void*)&exportFn<2026>,
	(void*)&exportFn<2027>,
	(void*)&exportFn<2028>,
	(void*)&exportFn<2029>,
	(void*)&exportFn<2030>,
	(void*)&exportFn<2031>,
	(void*)&exportFn<2032>,
	(void*)&exportFn<2033>,
	(void*)&exportFn<2034>,
	(void*)&exportFn<2035>,
	(void*)&exportFn<2036>,
	(void*)&exportFn<2037>,
	(void*)&exportFn<2038>,
	// (void*)&exportFn<2039>,
	(void*)&generic_return_zero,
	(void*)&exportFn<2040>,
	(void*)&exportFn<2041>,
	(void*)&exportFn<2042>,
	(void*)&exportFn<2043>,
	(void*)&exportFn<2044>,
	(void*)&exportFn<2045>,
	(void*)&exportFn<2046>,
	(void*)&exportFn<2047>,
	(void*)&exportFn<2048>,
	(void*)&exportFn<2049>,
	(void*)&exportFn<2050>,
	// (void*)&exportFn<2051>,
	(void*)&generic_return_zero,
	(void*)&exportFn<2052>,
	(void*)&exportFn<2053>,
	(void*)&exportFn<2054>,
	(void*)&exportFn<2055>,
	(void*)&exportFn<2056>,
	(void*)&exportFn<2057>,
	(void*)&exportFn<2058>,
	(void*)&exportFn<2059>,
	(void*)&exportFn<2060>,
	(void*)&exportFn<2061>,
	(void*)&exportFn<2062>,
	(void*)&exportFn<2063>,
	(void*)&exportFn<2064>,
	(void*)&exportFn<2065>,
	(void*)&exportFn<2066>,
	(void*)&exportFn<2067>,
	(void*)&exportFn<2068>,
	(void*)&exportFn<2069>,
	(void*)&exportFn<2070>,
	(void*)&exportFn<2071>,
	(void*)&exportFn<2072>
};

extern "C"{

	CUresult mycuGetExportTable(const void **ppExportTable, const CUuuid *pExportTableId) {
		//put UUID into a string to be able to do comparisons		
		char uuid[38];
		sprintf(uuid,"%p %p",*pExportTableId,*(pExportTableId+8));

		if(strcmp(uuid,"0x47cbf623815ad842 0xdcec3a8ae7f69882")!=0 && strcmp(uuid,"0x48321497608c3121 0xf2c82473ff41a68c")!=0){
			std::cerr << "Call for unknown Export Table: " << uuid << std::endl;
			exit(EXIT_FAILURE);
		}
		if(strcmp(uuid,"0x47cbf623815ad842 0xdcec3a8ae7f69882")==0){
			*ppExportTable = ExportTable_1;
		}else{
			*ppExportTable = ExportTable_2;
		}

		return CUDA_SUCCESS;
	}


  	//Runtime API cudaGetExportTable just forward call to driver's cuGetExportTable
  	cudaError_t cudaGetExportTable(const void **ppExportTable, const cudaUUID_t *pExportTableId) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		char uuid[38];
		sprintf(uuid,"%p %p",*pExportTableId,*(pExportTableId+8));
		CUresult retval;
		
		//if unknown export table
		if(strcmp(uuid,"0x47cbf623815ad842 0xdcec3a8ae7f69882")!=0 && strcmp(uuid,"0x48321497608c3121 0xf2c82473ff41a68c")!=0){			
			std::cerr << "Uknown export table in runtime library! "<< uuid << std::endl;
			exit(EXIT_FAILURE);
		}else{
			retval = mycuGetExportTable(ppExportTable,(CUuuid*) pExportTableId);
		}

		return (cudaError_t) retval;
	}

}

