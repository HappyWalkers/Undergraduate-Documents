/*********************************************************************************************
* File name	: 2410slib.h
* Author	: embest
* Descript	: S3C2410 MMU operation functions 
* History
*			R.X.Huang, Programming modify, March 12, 2005
*********************************************************************************************/

#ifndef __2410slib_h__
#define __2410slib_h__

#ifdef __cplusplus
extern "C" {
#endif

/* ********************************************************************* */
/* Interface macro & data definition */

#define DESC_SEC       (0x2|(1<<4))
#define CB             (3<<2)  //cache_on, write_back
#define CNB            (2<<2)  //cache_on, write_through 
#define NCB            (1<<2)  //cache_off,WR_BUF on
#define NCNB           (0<<2)  //cache_off,WR_BUF off
#define AP_RW          (3<<10) //supervisor=RW, user=RW
#define AP_RO          (2<<10) //supervisor=RW, user=RO

#define DOMAIN_FAULT   (0x0)
#define DOMAIN_CHK     (0x1) 
#define DOMAIN_NOTCHK  (0x3) 
#define DOMAIN0        (0x0<<5)
#define DOMAIN1        (0x1<<5)

#define DOMAIN0_ATTR   (DOMAIN_CHK<<0) 
#define DOMAIN1_ATTR   (DOMAIN_FAULT<<2) 

#define RW_CB          (AP_RW|DOMAIN0|CB|DESC_SEC)
#define RW_CNB         (AP_RW|DOMAIN0|CNB|DESC_SEC)
#define RW_NCNB        (AP_RW|DOMAIN0|NCNB|DESC_SEC)
#define RW_FAULT       (AP_RW|DOMAIN1|NCNB|DESC_SEC)

/* note: Reflect the changes in init.s */
#define FLASH_SADDR  0x00000000 /* Flash starting address */
#define SRAM_SADDR   0x40000000 /* SRAM starting address */
#define SRAM_SIZE    (4*1024)   /* 4K internal SRAM */
#define SFR_BADDR    0x48000000 /* SFR base address */

#define SDRAM_SADDR  0x30000000 /* SDRAM starting address */
#define SDRAM_SIZE   (64*1024*1024) /* 64M SDRAM */
#define ISR_BADDR    0x33ffff00 /* ISR vector table start address */

#define SRAM_EADDR   (SRAM_SADDR+SRAM_SIZE-1) /* SRAM end address */
#define SDRAM_EADDR  (SDRAM_SADDR+SDRAM_SIZE-1) /* SRAM end address */

#define MMUTT_SIZE   (16*1024) /* It has to be in multiples of 16K */
#define MMUTT_SADDR  (SDRAM_SADDR) /* MMU Table start address */
#define MMUTT_EADDR  (MMUTT_SADDR+MMUTT_SIZE)

int SET_IF(void);
void WR_IF(int cpsrValue);
void CLR_IF(void);

void MMU_EnableICache(void);
void MMU_DisableICache(void);
void MMU_EnableDCache(void);
void MMU_DisableDCache(void);
void MMU_EnableAlignFault(void);
void MMU_DisableAlignFault(void);
void MMU_EnableMMU(void);
void MMU_DisableMMU(void);
void MMU_SetTTBase(UINT32T base);
void MMU_SetDomain(UINT32T domain);

//void MMU_SetFastBusMode(void);          //GCLK=HCLK
//void MMU_SetAsyncBusMode(void);         //GCLK=FCLK @(FCLK>=HCLK)

void MMU_InvalidateIDCache(void);
void MMU_InvalidateICache(void);
void MMU_InvalidateICacheMVA(UINT32T mva);
void MMU_PrefetchICacheMVA(UINT32T mva);
void MMU_InvalidateDCache(void);
void MMU_InvalidateDCacheMVA(UINT32T mva);
void MMU_CleanDCacheMVA(UINT32T mva);
void MMU_CleanInvalidateDCacheMVA(UINT32T mva);
void MMU_CleanDCacheIndex(UINT32T index);
void MMU_CleanInvalidateDCacheIndex(UINT32T index); 
void MMU_WaitForInterrupt(void);
        
void MMU_InvalidateTLB(void);
void MMU_InvalidateITLB(void);
void MMU_InvalidateITLBMVA(UINT32T mva);
void MMU_InvalidateDTLB(void);
void MMU_InvalidateDTLBMVA(UINT32T mva);

void MMU_SetDCacheLockdownBase(UINT32T base);
void MMU_SetICacheLockdownBase(UINT32T base);

void MMU_SetDTLBLockdown(UINT32T baseVictim);
void MMU_SetITLBLockdown(UINT32T baseVictim);

void MMU_SetProcessId(UINT32T pid);

#ifdef __cplusplus
}
#endif

#endif   //__2410slib_h__
