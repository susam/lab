How the 'Net works: an introduction to peering and transit
==========================================================
2008-09-02: Rudolph van der Berg: http://arstechnica.com/features/2008/09/peering-and-transit/

Snippets
--------
In 2005, AT&T CEO Ed Whitacre famously told BusinessWeek, "What they
[Google, Vonage, and others] would like to do is to use my pipes free.
But I ain't going to let them do that... Why should they be allowed to
use my pipes?"

---

At the moment, the Internet consists of over 25,000 Autonomous Systems
(AS). An Autonomous System can independently decide who to exchange
traffic with on the 'Net, and it isn't dependent upon a third party for
access.

Networks of Internet service providers, hosting providers,
telecommunications monopolists, multinationals, schools, hospitals and
even individuals can be Autonomous Systems; all you need is a single "AS
number" and a block of provider independent IP-numbers. These can be had
from a regional Internet registry (like RIPE, ARIN, APNIC, LACNIC and
AFRINIC).

---

The economic arrangements that allow networks to interconnect directly
and indirectly are called "peering" and "transit":

  - **Peering:** when two or more autonomous networks interconnect
    directly with each other to exchange traffic. This is often done
    without charging for the interconnection or the traffic.
  - **Transit:** when one autonomous network agrees to carry the traffic
    that flows between another autonomous network and all other
    networks. Since no network connects directly to all other networks,
    a network that provides transit will deliver some of the traffic
    indirectly via one or more other transit networks. A transit
    provider's routers will announce to other networks that they can
    carry traffic to the network that has bought transit. The transit
    provider receives a "transit fee" for the service.

---

Transit traffic is the most expensive. The ISP will have to estimate how
much traffic it needs, and any extra traffic will cost extra. If the ISP
is faced with extra traffic (think large-scale P2P use), its first
priority will be to keep the traffic on its own network. If it can't, it
will then use peering, and as a last resort it will pay for transit.

---

Transit costs money, and as the ISP grows, its transit bill will grow,
too. In order to reduce its transit bill, the ISP will look for suitable
networks to peer with. When two networks determine that the costs of
interconnecting directly (peering) are lower than the costs of buying
transit from each other, they'll have an economic incentive to peer.

---

Peering's costs lie in the switches and the lines necessary to connect
the networks; after a peering has been established, the marginal costs
of sending one bit are zero. It then becomes economically feasible to
send as much traffic between the two network peers as is technically
possible, so when two networks interconnect at 1Gbps, they will use the
full 1Gbps.

---

It's a common misconception that the benefit an ISP derives from peering
depends upon the direction of the flow of traffic. According to this way
of thinking, if YouTube peers with an ISP, this benefits YouTube more
than it does the ISP (since YouTube sends so much data but receives
comparatively little). But in practice, the flow of traffic is not an
issue for an interconnect. Whether it goes to or from the network,
companies still need the same Cisco equipment.

---

Hot potato routing is the practice of handing over traffic at the
earliest convenience (hot, hot! Here, you take it!), while cold potato
routing is where you hold onto traffic as long as you can before handing
it over to another network.

---

There might be situations where a peering might be beneficial to network
A, but the savings are too little for network B. In such a case it might
look good to A to pay B for a peering agreement to increase B's savings
to such a level that both parties will profit. Though this might sound
good at first, it could have unintended consequences for network A. If
the traffic between the two networks grows to such a level that both
parties benefit equally from the peering, B will still want to try to
keep the payment for the peering; it's essentially free money.

---

In the history of the internet, we can see that at first, these
locations were at the sites where academic networks interconnected, and
later on at large co-location facilities. In order to facilitate
peering, Internet exchange points (IXPs) were established at those
locations. In Europe these IXPs are typically not-for-profit
associations, while in the USA they operate as private businesses.

---

There will still be direct interconnects that bypass the exchange (known
as private interconnects), where the exchange can act as a backup for
that interconnect (and a transit connection often acts as a backup for
that backup).

---

In a nutshell, the economics of interconnection are:

  - Peer as much as you can, to avoid transit fees.
  - Use the savings from peering to expand your business and network.
  - Use the expansion of your business and network to become more
    attractive for others to peer with and to reach those that are
    attractive to peer with.
  - Establish IXPs in order to further lower the costs of peering, to
    bring together as many networks as possible, and to create locations
    where there is competition between providers of transit.
  - Repeat.

---

Though it's tempting to let profits rise with the growth of traffic, the
network will actually have to lower its traffic price every month in
order for margins to remain the same, thereby keeping intact the barrier
to entry for a competing network.

---

In the end, pure transit is debatable as a real business model. An
average end-user is bound to its ISP by numerous switching costs (change
of e-mail address, lack of knowledge, time, hassle, etc.), but this
customer lock-in just does not apply to transit. The Border Gateway
Protocol propagates a change in transit provider within seconds,
globally. Autonomous Systems can switch within seconds and there is
little a transit provider can do to differentiate itself from rivals.

---

Further reading: [The Art of Peering; The peering playbook][PPDB]

[PPB]: http://www.blogg.ch/uploads/peering-playbook.pdf


Notes
-----
- In computer networking, peering is a voluntary interconnection of
  administratively separate Internet networks for the purpose of
  exchanging traffic between the users of each network. The pure
  definition of peering is settlement-free, "bill-and-keep," or "sender
  keeps all," meaning that neither party pays the other in association
  with the exchange of traffic; instead, each derives and retains
  revenue from its own customers. ([WP-PEERING][])
- An agreement by two or more networks to peer is instantiated by a
  physical interconnection of the networks, an exchange of routing
  information through the Border Gateway Protocol (BGP) routing protocol
  and, in some special cases, a formalized contractual document. ([WP-PEERING][])
- An Internet exchange point (IX or IXP) is a physical infrastructure
  through which Internet service providers (ISPs) and Content Delivery
  Networks (CDNs) exchange Internet traffic between their networks
  (autonomous systems). ([WP-IXP][])
- The technical and business logistics of traffic exchange between ISPs
  is governed by mutual peering agreements. Under such agreements,
  traffic is often exchanged without compensation. When an IXP incurs
  operating costs, they are typically shared among all of its
  participants. At the more expensive exchanges, participants pay a
  monthly or annual fee, usually determined by the speed of the port or
  ports which they are using. Fees based on volume of traffic are less
  common because they provide a counterincentive to growth of the
  exchange. ([WP-IXP][])

[WP-PEERING]: https://en.wikipedia.org/wiki/Peering
[WP-IXP]: https://en.wikipedia.org/wiki/Internet_exchange_point
