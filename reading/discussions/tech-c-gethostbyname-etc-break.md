gethostbyname() etc break with both ::1 and 127.0.0.1 local entries
===================================================================
2007-08-29: https://sourceware.org/bugzilla/show_bug.cgi?id=4980

**Petr Baudis 2007-08-29**

On Nov 20 a change in nss/nss_files/files-hosts.c:LINE_PARSER was
introduced to treat ::1 the same way as 127.0.0.1. A lot of Linux systems have

    127.0.0.1       localhost
    ::1             localhost

in their /etc/hosts (though most have ip6-localhost for ::1 instead).

The new behavior appears not to be mandated by any standard nor does it seem as
a particularily useful change.

The trouble is that now gethostbyname() (gethostbyname2(), getaddrinfo(), ...)
will return duplicate 127.0.0.1 records in h_addr_list[] and some applications
do not explect duplicate entries in this array (e.g. OpenLDAP). The new
behaviour does not seem to gain anything so the old behavior should be restored.

---

**Ulrich Drepper 2007-08-29**

Of course it gains something, otherwise it would not have been added.  And
programs which don't handle multiple addresses are simply broken and must be
fixed anyway.  Stop defending broken code.

---

**Howard Chu 2007-12-01**

> Stop reopening bugs.  Search the web if you want an explanation, I don't have
> anything handy and certainly have no interest in writing it up.

I've found no discussion of this change on any of the glibc mailing list
archives, after searching through September-November 2006 on libc-announce,
libc-hacker, libc-alpha, glibc-cvs, or glibc-bugs. I think it's fair to say that
if you don't want people to keep asking stupid questions, a little more
documentation of your rationale will help.

The CVS log entry is useful, at least:

Support IPv6-style addresses for IPv4 queries if they
can be mapped.

But your implementation violates RFC2553: http://www.ietf.org/rfc/rfc2553.txt
Page 25:

    Also note that the
    IPv6 hex addresses "::" and "::1" MUST NOT be treated as IPv4-
    compatible addresses, ...

    Also for the macro in section 6.7 IN6_IS_ADDR_V4COMPAT MUST return
    false for "::" and "::1".

I.e., the RFC specifically forbids the mapping of the IPV6 loopback address to
IPv4. As far as I can see, the current glibc behavior here is a bug.

---

**Tero Pelander 2008-04-15**

Created [attachment 2693][ATTACHMENT1] [[details]][DETAILS1]
getaddrinfo fix for 2.6.1/2.7

> Of course it gains something, otherwise it would not have been added.	And
> programs which don't handle multiple addresses are simply broken and must be
> fixed anyway.	Stop defending broken code.

Seems you haven't cheked the code lately. I'll give you real life
example explaining why the mistake of thinking that all hostnames that
resolve to ::1 also resolve to 127.0.0.1 is causing big problems to
users.

I have ldap hosts defined as:

    localldap.example.org ldap1.example.org ldap2.example.org

As I'm using TLS I must use hostname instead of ip-number.
File /etc/hosts contains following

    ::1		localhost localldap.example.org
    127.0.0.1	localhost

As ldap services contain important data it is protected by internal
firewall. The firewall accepts connection to ldap port from  ldap-master
and ::1. The reason for using localhost with ldap is that ldap is
started as early as possible in boot to provide user information. It is
started before any network other then localhost.

Now as glibc-implementation of getaddrinfo() was changed the first
connection is done to 127.0.0.1. Firewall blocks this connection and
after timeout of 15 seconds the connection is tried to ::1. At that time
it succeeds.

As you can see the program definately can support multiple addresses
form getaddrinfo() and can hardly be considered buggy.

As OSS camp often says: "talk is cheep, show the code". I have added a
fix that I have verified to work under 2.6.1. The code in question is
identical in 2.7.

[ATTACHMENT1]: https://sourceware.org/bugzilla/attachment.cgi?id=2693&action=diff
[DETAILS1]: https://sourceware.org/bugzilla/attachment.cgi?id=2693&action=edit

---

**Matt Mullins 2008-07-08**

Created [attachment 2816][ATTACHMENT2]: [[details]][DETAILS2]
test case for IN6_IS_ADDR_V4COMPAT

This does not appear to violate any RFCs.

Howard Chu claims that this behavior violates RFC 2553.  First of all,
"IPv4-compatible addresses" have been deprecated by RFC 4291, section 2.5.5.1.
Even if it had not been, this is an incorrect assumption.  "IPv4-compatible
addresses" would have implied that you could send an IPv6 packet over the wire
addressed to, say ::209.132.176.174, and a router would then encapsulate it in
an IPv4 packet to 209.132.176.174.  This has been superceded by the 6to4
dynamic tunneling scheme, which instead gives each IPv4 address a /48 in
IPv6-space.  But I digress.

What RFC 2553 means by 'IPv6 hex addresses "::" and "::1" MUST NOT be treated
as IPv4-compatible addresses' is that a router may not encapsulate ::1 in an
IPv4 packet to 0.0.0.1.  This behavior does not happen, because a host will
drop packets to ::1 if it did not come through the "lo" loopback interface.
Even if this were to happen, it would be beyond the scope of libc; it would be
a kernel IP stack issue instead.

As for the macro behavior quoted from RFC 2553, I wrote some test code (see
attachment), and I get:

    IN6_IS_ADDR_V4COMPAT( ::1 ) = false
    IN6_IS_ADDR_V4COMPAT( :: ) = false

There is nothing in the RFCs that specifies how /etc/hosts should behave, since
that is not something that belongs in a protocol specification.  If glibc
decides to have "::1 localhost" implicitly act as if you had also typed
"127.0.0.1 localhost", then so be it.  None of the function behavior that I
have tested violates what is described in the RFCs.

That is not to say that I don't find this behavior a bit odd.  I would love to
hear from Ulrich what problem this functionality was intended to fix, but I
don't believe that this is in any way a violation of spec.  It's just a bit
different from the way soe people might interpret it.

phelix, this has nothing whatsoever to do with 6to4 tunneling.	6to4 tunneling
describes embedding IPv6 packets within IPv4 packets.  In Linux, that is
handled completely by the kernel, and all applications, including libc, know is
that they are opening an IPv6 socket.  The RFC that you quote is saying that an
IPv6 packet within an IPv4 packet sent to, for example, 127.0.0.1 is invalid.

For the record, I tested this against glibc 2.7 on Ubuntu hardy.

[ATTACHMENT2]: https://sourceware.org/bugzilla/attachment.cgi?id=2816
[DETAILS2]: https://sourceware.org/bugzilla/attachment.cgi?id=2816&action=edit


---

*Notes:*

- In September 1995 Ulrich Drepper made his first contribution to the
  glibc project and gradually became over the 1990s the core contributor
  and maintainer of glibc. Drepper held the maintainership position for
  many years and accumulated until 2012 63% of all commits of the
  project.
- Starting in 2001 the library's development had been overseen by a
  committee, with Ulrich Drepper kept as the lead contributor and
  maintainer. The steering committee installation was surrounded by a
  public controversy as it was openly described by Ulrich Drepper as
  failed hostile takeover maneuver by RMS.
- In March 2012, the steering committee voted to disband itself and
  remove Drepper in favor of a community-driven development process,
  with Ryan Arnold, Maxim Kuvyrkov, Joseph Myers, Carlos O'Donell, and
  Alexandre Oliva holding the responsibility of GNU maintainership (but
  no extra decision-making power).

Source: https://en.wikipedia.org/wiki/GNU_C_Library
