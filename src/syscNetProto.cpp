#include "syscNetProto.hpp"
using namespace std;


int send_message(int socket, msgHeader_t* hdr, uint8_t* blk)
{
    int ret;
#ifdef MODEL_TECH
    FILE* fd;
    string buf_path = string(getenv("WORKSPACE_PATH")) + "/SYSC_FPGA/simulation/" + to_string(hdr->msgType) + ".bin";
    fd = fopen(buf_path.c_str(), "w");
    ret = fwrite(hdr, 1, sizeof(msgHeader_t), fd);
    fflush(fd);
    fclose(fd);
    if(hdr->pyld)
    {
        string buf_path = string(getenv("WORKSPACE_PATH")) + "/SYSC_FPGA/simulation/" + to_string(hdr->msgType) + "_pyld.bin";
        fd = fopen(buf_path.c_str(), "w");
        ret = fwrite(blk, 1, hdr->length, fd);
        fflush(fd);
        fclose(fd);
    }
#else
    msgHeader_t hdr_tmp;
    // Convert to the network format
    hdr_tmp.msgType = (msgType_t)htonl(hdr->msgType);
    hdr_tmp.length = htonl(hdr->length);
    hdr_tmp.pyld = htonl(hdr->pyld);
	ret = send_data(socket, (uint8_t*)&hdr_tmp, sizeof(msgHeader_t));
    if(hdr->pyld)
    {
	    ret = send_data(socket, blk, hdr->length);
    }
#endif
    return ret;
}


int recv_message(int socket, msgHeader_t* hdr, uint8_t* blk)
{
    int ret;
#ifdef MODEL_TECH
    FILE* fd;
    string buf_path = string(getenv("WORKSPACE_PATH")) + "/SYSC_FPGA/simulation/" + to_string(hdr->msgType) + ".bin";
    struct stat buffer;
    while(stat(buf_path.c_str(), &buffer));
    fd = fopen(buf_path.c_str(), "r");
    ret = fread(hdr, 1, sizeof(msgHeader_t), fd);
    fclose(fd);
    if(remove(buf_path.c_str()))
    {
        perror("Error deleting file");
    }
    if(hdr->pyld)
    {
        string buf_path = string(getenv("WORKSPACE_PATH")) + "/SYSC_FPGA/simulation/" + to_string(hdr->msgType) + "_pyld.bin";
        while(stat(buf_path.c_str(), &buffer));
        fd = fopen(buf_path.c_str(), "r");        
        ret = fread(blk, 1, hdr->length, fd);
        fclose(fd);
        if(remove(buf_path.c_str()))
        {
            perror("Error deleting file");
        }
    }
#else
    // Read the message header
	ret = recv_data(socket, (uint8_t*)hdr, sizeof(msgHeader_t), sizeof(msgHeader_t));
	hdr->msgType = (msgType_t)ntohl(hdr->msgType);
    hdr->length = ntohl(hdr->length);
    hdr->pyld = ntohl(hdr->pyld);
	if(hdr->pyld)
    {
		ret = recv_data(socket, blk, hdr->length, hdr->length);
    }
#endif
	return ret;
}


int wait_message(int socket, msgHeader_t* hdr, uint8_t* blk, msgType_t mt)
{
    int ret;
#ifdef MODEL_TECH
    hdr->msgType = mt;
    ret = recv_message(socket, hdr, blk);
#else
	do
    {
		hdr->msgType = NULL_MSG;
	    ret = recv_message(socket, hdr, blk);
    } while(hdr->msgType != mt);
	// Return succesfully
#endif
	return ret;
}
