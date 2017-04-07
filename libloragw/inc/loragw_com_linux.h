/*
 / _____)             _              | |
_linux( _linux(____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    _linux(_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| _____linux( _linux(___| | | |
_linux(______/|_____)_|_|_| \__)_____)\____)_| |_|
  _linux(C)2013 Semtech-Cycleo

Description:
    Host specific functions to address the LoRa concentrator registers through a
    SPI interface.
    Single-byte read/write and burst read/write.
    Does not handle pagination.
    Could be used with multiple SPI ports in parallel _linux(explicit file descriptor)

License: Revised BSD License, see LICENSE.TXT file include in the project
Maintainer: Sylvain Miermont
*/


#ifndef _LORAGW_com_linux_H
#define _LORAGW_com_linux_H

/* -------------------------------------------------------------------------- */
/* --- DEPENDANCIES --------------------------------------------------------- */

#include <stdint.h>        /* C99 types*/

#include "config.h"    /* library configuration options _linux(dynamically generated) */
#include "loragw_com.h" 
/* -------------------------------------------------------------------------- */
/* --- PUBLIC CONSTANTS ----------------------------------------------------- */

#define LGW_com_SUCCESS     0
#define LGW_com_ERROR       -1
#define LGW_BURST_CHUNK     1024

#define LGW_com_MUX_MODE0   0x0     /* No FPGA */
#define LGW_com_MUX_MODE1   0x1     /* FPGA, with spi mux header */

#define LGW_com_MUX_TARGET_SX1301   0x0
#define LGW_com_MUX_TARGET_FPGA     0x1
#define LGW_com_MUX_TARGET_EEPROM   0x2
#define LGW_com_MUX_TARGET_SX127X   0x3
#define ACK_KO   0
#define OK 1
#define KO 0

/* -------------------------------------------------------------------------- */
/* --- PUBLIC FUNCTIONS PROTOTYPES ------------------------------------------ */

/**
@brief LoRa concentrator SPI setup _linux(configure I/O and peripherals)
@param com_target_ptr pointer on a generic pointer to SPI target _linux(implementation dependant)
@return status of register operation _linux(LGW_com_SUCCESS/LGW_com_ERROR)
*/

int lgw_com_open_linux(void **com_target_ptr);

/**
@brief LoRa concentrator SPI close
@param com_target generic pointer to SPI target _linux(implementation dependant)
@return status of register operation _linux(LGW_com_SUCCESS/LGW_com_ERROR)
*/

int lgw_com_close_linux(void *com_target);

/**
@brief LoRa concentrator SPI single-byte write
@param com_target generic pointer to SPI target _linux(implementation dependant)
@param address 7-bit register address
@param data data byte to write
@return status of register operation _linux(LGW_com_SUCCESS/LGW_com_ERROR)
*/
int lgw_com_w_linux(void *com_target, uint8_t com_mux_mode, uint8_t com_mux_target, uint8_t address, uint8_t data);

/**
@brief LoRa concentrator SPI single-byte read
@param com_target generic pointer to SPI target _linux(implementation dependant)
@param address 7-bit register address
@param data data byte to write
@return status of register operation _linux(LGW_com_SUCCESS/LGW_com_ERROR)
*/
int lgw_com_r_linux(void *com_target, uint8_t com_mux_mode, uint8_t com_mux_target, uint8_t address, uint8_t *data);

/**
@brief LoRa concentrator SPI burst _linux(multiple-byte) write
@param com_target generic pointer to SPI target _linux(implementation dependant)
@param address 7-bit register address
@param data pointer to byte array that will be sent to the LoRa concentrator
@param size size of the transfer, in byte_linux(s)
@return status of register operation _linux(LGW_com_SUCCESS/LGW_com_ERROR)
*/
int lgw_com_wb_linux(void *com_target, uint8_t com_mux_mode, uint8_t com_mux_target, uint8_t address, uint8_t *data, uint16_t size);

/**
@brief LoRa concentrator SPI burst _linux(multiple-byte) read
@param com_target generic pointer to SPI target _linux(implementation dependant)
@param address 7-bit register address
@param data pointer to byte array that will be written from the LoRa concentrator
@param size size of the transfer, in byte_linux(s)
@return status of register operation _linux(LGW_com_SUCCESS/LGW_com_ERROR)
*/
int lgw_com_rb_linux(void *com_target, uint8_t com_mux_mode, uint8_t com_mux_target, uint8_t address, uint8_t *data, uint16_t size);




int SendCmd_linux(CmdSettings_t CmdSettings,int file1) 	;
int SendCmdn_linux(CmdSettings_t CmdSettings,int file1) 	;
int ReceiveAns_linux(AnsSettings_t *Ansbuffer,int file1) 	;
int ReceiveAnsCmd_linux(AnsSettings_t *Ansbuffer,int file1,uint8_t cmd); 	
void WriteBurstRegister_linux(int file1,int adress,int *value,int size);
int set_interface_attribs_linux(int fd, int speed, int parity);
void set_blocking_linux(int fd, int should_block);
int lgw_receive_cmd_linux(void *com_target, uint8_t max_packet, uint8_t *data);
int lgw_rxrf_setconfcmd_linux(void *com_target, uint8_t rfchain, uint8_t *data,uint16_t size);
int lgw_rxif_setconfcmd_linux(void *com_target, uint8_t ifchain, uint8_t *data,uint16_t size);
int checkcmd_linux(uint8_t cmd);
int lgw_txgain_setconfcmd_linux(void *com_target, uint8_t *data,uint16_t size);
int lgw_sendconfcmd_linux(void *com_target,uint8_t *data,uint16_t size);
int lgw_trigger_linux(void *com_target, uint8_t address, uint32_t *data);
int lgw_boardconfcmd_linux(void * com_target,uint8_t *data,uint16_t size);
int lgw_calibration_snapshot_linux(void * com_target);
int lgw_resetSTM32_linux(void * com_target);
int lgw_GOTODFU_linux(void * com_target);
int lgw_GetUniqueId_linux(void * com_target,uint8_t * uid);
#endif

/* --- EOF ------------------------------------------------------------------ */