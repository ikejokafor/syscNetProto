#pragma once


#include "network.hpp"
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <string>


typedef enum
{
    NULL_MSG                = -1,
    CONNECT_HARDWARE        = 0,
    CONNECT_SOFTWARE        = 1,
    ACCL_SYSC_FPGA_BGN_CFG  = 2,  
    ACCL_SYSC_FPGA_END_CFG  = 3,
    ACCL_BGN_CFG            = 4,
    ACCL_END_CFG            = 5,
    ACCL_BGN_PARAM          = 6,
    ACCL_END_PARAM          = 7,
    ACCL_START              = 8,
    ACCL_COMPLETE           = 9,
    ACCL_BGN_OUTPUT         = 10,
    ACCL_END_OUTPUT         = 11,
    ACCL_PYLD               = 12,
    ACCL_ACK                = 13,
    SOFT_ACK                = 14
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