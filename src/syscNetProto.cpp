#include "syscNetProto.hpp"


int send_message(int socket, msgHeader_t* hdr, uint8_t* blk)
{
    msgHeader_t hdr_tmp;
    // Convert to the network format
    hdr_tmp.msgType = (msgType_t)htonl(hdr->msgType);
    hdr_tmp.length = htonl(hdr->length);
    hdr_tmp.pyld = htonl(hdr->pyld);
	int ret = send_data(socket, (uint8_t*)&hdr_tmp, sizeof(msgHeader_t));;
    if(hdr->pyld)
    {
	    ret = send_data(socket, blk, hdr->length);
    }
    return ret;
}


int recv_message(int socket, msgHeader_t* hdr, uint8_t* blk)
{
    // Read the message header
	int ret = recv_data(socket, (uint8_t*)hdr, sizeof(msgHeader_t), sizeof(msgHeader_t));
	hdr->msgType = (msgType_t)ntohl(hdr->msgType);
    hdr->length = ntohl(hdr->length);
    hdr->pyld = ntohl(hdr->pyld);
	if(hdr->pyld)
    {
		ret = recv_data(socket, blk, hdr->length, hdr->length);
    }
	return ret;
}


int wait_message(int socket, msgHeader_t* hdr, uint8_t* blk, msgType_t mt)
{
	int ret;
	do
    {
		hdr->msgType = NULL_MSG;
	    ret = recv_message(socket, hdr, blk);
    } while(hdr->msgType != mt);
	// Return succesfully
	return ret;
}
