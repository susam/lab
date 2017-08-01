macOS Fruitfly Backdoor Analysis Renders New Spying Capabilities
================================================================
2017-07-24: Michael Mimoso:
https://threatpost.com/macos-fruitfly-backdoor-analysis-renders-new-spying-capabilities/126943/

Snippets
--------
The FruitFly backdoor became a known entity in January, but it's a good bet
that for years it had been in the wild, undetected by analysts and security
software.

The macOS and OS X malware has a number of insidious spying capabilities that
would make anyone uneasy, and a variant recently analyzed by Synack chief
security researcher Patrick Wardle was no exception.

---

Unlike other spyware samples—including the FruitFly sample disclosed earlier
this year by Malwarebytes—this variant did not appear to target researchers,
high-profile organizations or defense contractors. In fact, most of the victims
are in the United States, including a noteworthy concentration of them in Ohio.

---

The malware did also contain a number of encrypted connections to the backup
command and control servers that were available in case the primary C&Cs went
offline.

Once Wardle discovered that the backup servers were available, he registered
them. Immediately, he said, victims (about 400, which is likely a small subset
of a larger pool of victims) began connecting to the domains and sending system
information such as user and computer names and IP addresses, none of which he
interacted with, Wardle said, and instead turned over to law enforcement.

---

"In the lab, I could modify host files to give it my box’s IP address and I
knew I could get it to call out to me," Wardle explained, adding that he could
also provide an IP address and port via the command line to the malware, making
it easier to get the malware to call out to his command and control server.

---

He added the initial infection vector is unknown, but he did conclude that
given the relatively small number of known victims, it’s likely that one person
is managing this operation and its size is what kept it under the radar.

Notes
-----
- FruitFly was the first Mac malware of 2017. ([MALWAREBYTES][])
- It was reportedly used in targetted attacks at biomedical research
  institutions. It contains antique system calls that date before OS X,
  possibly to avoid detection. ([9TO5MAC][])

[MALWAREBYTES]: https://blog.malwarebytes.com/threat-analysis/2017/01/new-mac-backdoor-using-antiquated-code/
[9TO5MAC]: https://9to5mac.com/2017/01/18/malware-macos-fruitfly/
