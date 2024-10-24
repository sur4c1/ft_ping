Usage:
	ping [options] <destination>+

OPTIONS:
	- [!] -v, --verbose
		- Verbose output. ICMP packets other than ECHO_RESPONSE that are received are listed.
	- [!] -?, --help
		- Display a help list.
	- [?] -f, --flood
		- Flood ping. Outputs packets as fast as they come back or one hundred times per second, whichever is more. For every ECHO_REQUEST sent a period "." is printed, while for every ECHO_REPLY received a backspace is printed. This provides a rapid display of how many packets are being dropped. Only the super-user may use this option. This can be very hard on a network and should be used with caution.
	- [?] -l, --preload <preload>
		- If preload is specified, ping sends that many packets as fast as possible before falling into its normal mode of behavior.
	- [?] -n, --numeric
		- Numeric output only. No attempt will be made to lookup symbolic names for host addresses.
	- [?] -w, --timeout <N>
		- Stop after N seconds of sending packets.
	- [?] -W, --linger <N>
		- Number of seconds to wait for response.
	- [?] -p, --patern <pattern>
		- You may specify up to 16 "pad" bytes to fill out the packet you send. This is useful for diagnosing data-dependent problems in a network. For example, “-p ff” will cause the sent packet to be filled with all ones.
	- [?] -r, --ignore-routing
		- Bypass the normal routing tables and send directly to a host on an attached network. If the host is not on a directly-attached network, an error is returned. This option can be used to ping a local host through an interface that has no route through it (e.g., after the interface was dropped by routed(8)).
	- [?] -s, --size <packetsize>
		- Specifies the number of data bytes to be sent. The default is 56, which translates into 64 ICMP data bytes when combined with the 8 bytes of ICMP header data.
	- [?]   , --ttl <N>
		- Set N as the packet time-to-live.
	- [?]   , --ip-timestamp <flag>
		- IP timestamp of type flag, which is one of "tsonly" and "tsaddr".
