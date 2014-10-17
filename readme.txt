CIS*3210 Computer Networks A1
=============================
Author: Ryan Wilson-Perkin
Date: 2014-10-17

A set of network simulation programs that transmit data via named pipes.

There are seven C programs called n1.c to n7.c that simulate network nodes,
and six named pipes called link1 through link7 that simulate network links.
n1 reads a text file from the user, followed by a space and the destination
node; for example "test.txt n4".

n1 then sends off the message towards the destination in packets containing one
character and the destination. A number generator is used to
introduce a delay between 1 and 2000 milliseconds before sending each packet. 
Messages are forwarded until they reach their destination, which then
prints the text file to the screen and sends back an “acknowledged” message to 
n1. When n1 receives confirmation that the message was received it
asks the user if they want to continue, Y/N. If Y, a new message and
destination is read from the user, and is sent off the same way as before. If
N, it sends a terminate message to every other process, which send back an
acknowledge message and exit. Once all other processes have exited, n1 also
exits.

How To Run
----------
The programs rely on 7 named pipes called link1 through link7, if you have not
previously created these pipes you can do so by calling "make links".

To run the program call "make run" which will build the binaries and run them.
