Compile with `make test-getaddrinfo`, should work on most platforms.

Running it: `./test-getaddrinfo www.powerdns.com google-public-dns-a.google.com. lorentz.7bits.nl | uniq` - as long as things are stable, this should give you one line of output. If you break things (on purpose), you should quickly see more lines. Errors go to stderr so uniq doesn't ratelimit those for you.
