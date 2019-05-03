### Firewall

## Implementaion
The provided input will be a CSV file in which each line contains exactly four columns: direction,
protocol, ports, and IP address:

# direction 
Either “inbound” or “outbound”, corresponding to whether the
traffic is entering or leaving the machine.

# protocol 
Either “tcp” or “udp”, all lowercase – we will just implement two
of the most common protocols.

# port 
Either (a) an integer in the range [1, 65535] or (b) a port range,
containing two integers in the range [1, 65535] separated by a
dash (no spaces). Port ranges are inclusive, i.e. the port range “80-­‐85” contains
ports 80 and 85. Given a port range, you may assume that the
range is well-­‐formed i.e. the start of the range is strictly less than
the end.

# IP address 
Either (a) an IPv4 address in dotted notation, consisting of 4
octets, each an integer in the range [0, 255], separated by periods
or (b) an IP range containing two IPv4 addresses, separated by a
dash (no spaces). Like port ranges, IP ranges are inclusive. Given an IP range, you
may assume that the range is well-­‐formed i.e. when viewed as a
number, the starting address is strictly less than the ending
address.

For example, the following are all valid inputs:
inbound,tcp,80,192.168.1.2
outbound,tcp,10000-­‐20000,192.168.10.11
inbound,udp,53,192.168.1.1-­‐192.168.2.5
outbound,udp,1000-­‐2000,52.12.48.92
