#pragma once


#include "network.hpp"


typedef enum
{
    NULL_MSG                = -1,
    CONNECT_HARDWARE        = 0,
    CONNECT_SOFTWARE        = 1,
    ACCL_CFG_PYLD           = 2,
    ACCL_SYSC_FPGA_BGN_CFG  = 3,  
    ACCL_SYSC_FPGA_END_CFG  = 4,
    ACCL_BGN_CFG            = 5,
    ACCL_END_CFG            = 6,
    ACCL_BGN_PARAM          = 7,
    ACCL_PARAM_PYLD         = 8,
    ACCL_END_PARAM          = 9,
    ACCL_START              = 10,
    ACCL_FINISHED           = 11,
    ACCL_BGN_OUTPUT         = 12,
    ACCL_OUTPUT_PYLD        = 13,
    ACCL_END_OUTPUT         = 14
} msgType_t;


typedef struct
{
    uint32_t msgType;
    uint32_t length;
    uint32_t pyld;
} msgHeader_t;


/**
* function
*
* \param[in]
* \param[in, out]
* \param[in]
*
* \return
*/
int send_message(int sock, msgHeader_t* hdr, uint8_t* blk);


/**
* function
*
* \param[in]
* \param[in, out]
* \param[in]
*
* \return
*/
int recv_message(int sock, msgHeader_t* hdr, uint8_t* blk);


/**
* function
*
* \param[in]
* \param[in, out]
* \param[in]
*
* \return
*/
int wait_message(int sock, msgHeader_t* hdr, uint8_t* blk, msgType_t mt);