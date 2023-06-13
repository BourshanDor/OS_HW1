
#include "os.h"
#include <stdio.h>

/*
pt - The physical page number of the page table root 
	You can assume that pt has been
	previously returned by alloc_page_frame()

vpn - The virtual page number the caller wishes to map/unmap
ppn - Can be one of two cases: 
 	1. If ppn is equal to a special NO MAPPING value, then vpn’s mapping (if it exists) should be destroyed.
		1.1 If we didn't reach to the end the structer we sould do nothing.
	2. ppn specifies the physical page number that vpn should be mapped to.
		2.1 If we didn't reach to the end the structer we sould allocate pages.

*/

void page_table_update(uint64_t pt, uint64_t vpn, uint64_t ppn){

	char* va = (char*) phys_to_virt(pt << 12) ; 

	if (va == NULL){
		return; 
	}

	int shift = 0;
	int pt_level[5]; 
	
	for (int i = 4; i >= 0; i--){

		pt_level[i]  = (vpn >> shift) & 0x1ff ; 
		shift += 9; 
	}

	uint64_t **table = (uint64_t**) va ;
	
	for (int i = 0; i < 5 ; i++ ){
		uint64_t pte = (uint64_t)table[pt_level[i]] ; 
		int valid_bit = pte % 2;
		if (valid_bit == 0) {

			if (ppn == NO_MAPPING){
				return; 
			}

			else{
					if (i == 4){
						//last node in PT + we wish to mapping 
						table[pt_level[i]] = (uint64_t* )((ppn << 12 ) + 0x1); 
						return; 
					}
				// alloc_page_frame() gives physical page number and we would like to treat this like PTE

				pte = (alloc_page_frame() << 12 )+ 0x1; 
				table[pt_level[i]] = (uint64_t*)(pte) ;  
			}
		}
		// Valid bit equals to '1'
		else{

			if ( i == 4 ){
				// The cell in the array should be destroyed
				if (ppn == NO_MAPPING){
					pte = 0x0 ; 
					table[pt_level[i]] = (uint64_t*)(pte);
					return;
				}
				// The cell in the array should be replaced
				else{
					table[pt_level[i]] = (uint64_t* )((ppn << 12 ) + 0x1); 
					return; 
				}
			}
		}
		table = (uint64_t**)(phys_to_virt((pte >> 12 ) << 12)) ;
	}
	return ;
}

/*
This function returns the physical page number that vpn is mapped to, or NO MAPPING if no
mapping exists. 
	pt - The physical page number of the page table root 
		You can assume that pt has been
		previously returned by alloc_page_frame()
	vpn - The virtual page number the caller wishes to know the mapping to physical page number 
*/ 
uint64_t page_table_query(uint64_t pt, uint64_t vpn){

	char* va = (char*) phys_to_virt(pt << 12) ; 

	if (va == NULL){
		return NO_MAPPING; 
	}

	int shift = 0;
	int pt_level[5]; 
	
	for (int i = 4; i >= 0; i--){

		pt_level[i]  = (vpn >> shift) & 0x1ff ; 
		shift += 9; 
	}

	uint64_t **table = (uint64_t**) va ;
	
	for (int i = 0; i < 5 ; i++ ){

		uint64_t pte = (uint64_t)table[pt_level[i]] ; 
		uint64_t* va_frame; 
		int valid_bit = pte % 2; 

		if ( valid_bit == 0) {
			return NO_MAPPING; 
		}
		else{
			if (i == 4){
				return pte >> 12; 
			}
			va_frame = (uint64_t*)phys_to_virt(((pte >> 12) << 12));   
		}
		
		table = (uint64_t**)va_frame ;
	}
	return NO_MAPPING;
}	
