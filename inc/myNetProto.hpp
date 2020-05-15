#pragma once


#include "network.hpp"


typedef enum
{
    NULL_MSG            = -1,
    CONNECT_HARDWARE    = 0,
    CONNECT_SOFTWARE    = 1,
    ACCEL_BGN_CFG       = 2,
    ACCEL_CFG_PYLD      = 3,
    ACCEL_END_CFG       = 4,
    ACCEL_BGN_PARAM     = 5,
    ACCEL_PARAM_PYLD    = 6,
    ACCEL_END_PARAM     = 7,
    ACCEL_START         = 8,
    ACCEL_FINISHED      = 9,
    ACCEL_BGN_OUTPUT    = 10,
    ACCEL_OUTPUT_PYLD   = 11,
    ACCEL_END_OUTPUT    = 12
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