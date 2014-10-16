#ifndef CIS3210_A1_PACKET_H
#define CIS3210_A1_PACKET_H

#define END_OF_TEXT         3
#define END_OF_TRANSMISSION 4
#define ACKNOWLEDGE         6

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

/*
 * get_link
 *  Open a link to send data from source node to dest node.
 *
 *  source: id of the source node (1-7)
 *  dest: id of the destination node (1-7)
 *
 *  returns: the file descriptor of the opened link, -1 if no link exists
 */
int get_link(int source, int dest);

#endif // CIS3210_A1_PACKET_H
