#ifndef CIS3210_A1_PACKET_H
#define CIS3210_A1_PACKET_H

#define END_OF_TEXT         3
#define END_OF_TRANSMISSION 4
#define ACKNOWLEDGE         6

#define WRITE   1
#define READ    2

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
 *  mode: open mode to use (either WRITE or READ)
 *
 *  returns: the file descriptor of the opened link, -1 if no link exists
 */
int get_link(int source, int dest, int mode);

/*
 * send_data
 *  Send characters of data to a node.
 *
 *  source: the node to send the data from
 *  dest: the node to send the data to
 *  n_chars: the number of characters in the data
 *  data: the data to send to the node
 */
void send_data(int source, int dest, int n_chars, char *data);

/*
 * acknowledge
 *  Send acknowledge message from source to dest.
 *
 *  source: the node to send the acknowledge from
 *  dest: the node to send the acknowledge to
 */
void acknowledge(int source, int dest);

/*
 * recv_acknowledge
 *  Receive acknowledge message at dest from source.
 *
 *  source: the node that sends the acknowledge
 *  dest: the node that receives the acknowledge
 */
void recv_acknowledge(int source, int dest)

#endif // CIS3210_A1_PACKET_H
