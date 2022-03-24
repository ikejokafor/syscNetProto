#pragma once


#include "network.hpp"
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <string>


//! enumerated type for protocol messages
typedef enum
{
    NULL_MSG                = -1, /*!< Null Message      */ 
    CONNECT_HARDWARE        = 0,  /*!< Connect to hardware sim */ 
    CONNECT_SOFTWARE        = 1,  /*!< Connect to software app */ 
    ACCL_SYSC_FPGA_BGN_CFG  = 2,  /*!< Begin systemc accelerator configuration */ 
    ACCL_SYSC_FPGA_END_CFG  = 3,  /*!< End systemc accelerator configuration */  
    ACCL_BGN_CFG            = 4,  /*!< Enum value TVal1 */
    ACCL_END_CFG            = 5,  /*!< Enum value TVal1 */
    ACCL_BGN_PARAM          = 6,  /*!< Enum value TVal1 */
    ACCL_END_PARAM          = 7,  /*!< Enum value TVal1 */
    ACCL_START              = 8,  /*!< Enum value TVal1 */
    ACCL_COMPLETE           = 9,  /*!< Enum value TVal1 */
    ACCL_BGN_OUTPUT         = 10, /*!< Enum value TVal1 */
    ACCL_END_OUTPUT         = 11, /*!< Enum value TVal1 */
    ACCL_PYLD               = 12, /*!< Enum value TVal1 */
    ACCL_ACK                = 13, /*!< Enum value TVal1 */
    SOFT_ACK                = 14  /*!< Enum value TVal1 */
} msgType_t;


//! enumerated type for protocol messages
typedef struct
{
    uint32_t msgType;  /*!< Enum value TVal1. */
    uint32_t length;   /*!< Enum value TVal1. */
    uint32_t pyld;     /*!< Enum value TVal1. */
} msgHeader_t;


// --------------------------------------------------------------------------------------------------------------------------------------------------
/**
 *      \brief              sends a message to the sim or application
 *  
 *      \param[in]          sock socket used to send the message
 *      \param[in]          hdr header of the message
 *      \param[in]          blk buffer holding data for the message
 *  
 *      \return             number of bytes sent if successful, -1 if failure
 */
// --------------------------------------------------------------------------------------------------------------------------------------------------
int send_message(int sock, msgHeader_t* hdr, uint8_t* blk);


// --------------------------------------------------------------------------------------------------------------------------------------------------
/**
 *      \brief              recieves a message from the sim or application
 *  
 *      \param[in]          sock socket used to send the message
 *      \param[in]          hdr header of the message
 *      \param[in]          blk buffer holding data for the message
 *  
 *      \return             number of bytes sent if successful, -1 if failure
 */
// --------------------------------------------------------------------------------------------------------------------------------------------------
int recv_message(int sock, msgHeader_t* hdr, uint8_t* blk);


// --------------------------------------------------------------------------------------------------------------------------------------------------
/**
 *      \brief              waits for a message from the sim or application
 *  
 *      \param[in]          sock socket used to send the message
 *      \param[in]          hdr header of the message
 *      \param[in]          blk buffer holding data for the message
 *  
 *      \return             number of bytes sent if successful, -1 if failure
 */
// --------------------------------------------------------------------------------------------------------------------------------------------------
int wait_message(int sock, msgHeader_t* hdr, uint8_t* blk, msgType_t mt);