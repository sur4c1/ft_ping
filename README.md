Usage:

ping [options] <destination>+

OPTIONS:
- -v, --verbose
	- Verbose output. ICMP packets other than ECHO_RESPONSE that are received are listed.
- -?, --help
	- Display a help list.
- -i, --interval <N>
	- Wait N seconds between sending each packet.
- -c, --count <N>
	- Wait for N packets before stopping.
- -W, --linger <N>
	- Number of seconds to wait for response.
-   , --ttl <N>
	- Set N as the packet time-to-live.
