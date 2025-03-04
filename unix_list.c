/*unix_list.c*/

#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	struct ifaddrs *addresses;

	if(getifaddrs(&addresses) == -1) { // 0 for success, -1 for failure
		// The function above, mallocs memory and creates linked list of addresses
		printf("Getting the ip addresses was failed\n");
		return -1;
	}

	struct ifaddrs *address = addresses; // assigned to first element
	while(address) {
		int family = address->ifa_addr->sa_family;

		if(family == AF_INET || family==AF_INET6) {
			printf("%s\t",address->ifa_name);
			printf("%s\t",family==AF_INET ? "IPv4" : "IPv6");

			char ap[100];
			const int family_size = family == AF_INET ?
				sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6);
			// it takes the size of sockaddr_in as ipv4 if family is ipv4,
			// otherwise ipv6
			
			getnameinfo(address->ifa_addr, family_size, ap, sizeof(ap), 0, 0, NI_NUMERICHOST);
			printf("\t%s\n",ap);
		}
		address = address->ifa_next;
	}

	free(addresses);
	return 0;
}

