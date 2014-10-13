#ifndef CIS3210_A1_PACKET_H
#define CIS3210_A1_PACKET_H

/*
 * packet
 *  A packet of data sent between nodes.
 *
 *  dest: the node to send to
 *  data: a single character of data to be sent
 */
typedef struct _packet
{
   char dest;
   char data;
} packet;

/*
 * send_packet
 *  Send single packet to destination.
 *
 *  destination_fd: file descriptor of destination
 *  p: the packet to send
 *
 *  returns: result of write function
 */
int send_packet(int destination_fd, packet p);

/*
 * recv_packet
 *  Receive single packet from source.
 *
 *  source_fd: file descriptor of source
 *  p: the packet to read data into 
 *
 *  returns: results of read function
 */
int recv_packet(int source_fd, packet *p);

#endif // CIS3210_A1_PACKET_H
