Why companies don't do GPL enforcement
======================================
2017-09-08: LWN: Luis Villa: https://lwn.net/SubscriberLink/716168/2d0eafdc242e44de/

Quotes
------
### What question doesn't get asked? ###
In [his recent talk at FOSDEM][FOSDEM], Richard Fontana spoke of using
enforcement to encourage "collaboration" by "making a level playing
field". While I strongly agree that's a valid reason to do enforcement,
I've never seen anyone in a corporate context ask if they should enforce
for that reason. That benefit is too abstract, and the costs very
specific and real. Businesses typically need much more concrete reasons
to make legal threats, especially public ones.

[FOSDEM]: https://lwn.net/Articles/715082/

### Do they have code I want? ###
The first question typically asked [in community enforcement][COMM] is
"does the license violator have code I want?".

For most individuals who are trying to pursue a GPL violation, the
answer is yes — usually because the potential enforcer has other,
related code or hardware that would be improved by freeing the
defendant's code.

...

But for large companies, violators usually don't have interesting code.

[COMM]: https://sfconservancy.org/copyleft-compliance/principles.html

### Do they have cash, or customers, I want? ###
Of course, not everyone wants code. Sometimes they want money, or to
shut down a competitor.

...

First, many GPL violators tend to be small companies that can't afford
proper compliance. Suing small, poor companies isn't a great plan to
make lots of money.

...

Second, many large GPL-contributing companies these days tend not to be
threatened by competitors using their code. ... These companies don't
view code as their actual primary business, so suing to shut down a
competitor who relies on the same code rarely makes sense.

One key exception to both of these patterns is Oracle. It is willing to
enforce at scale against small companies, and it views licensing as its
primary business. So it is no surprise that Oracle enforces its licenses
(GPL and otherwise) [against Java (and MySQL) users][ORA].

[ORA]: http://www.theregister.co.uk/2016/12/16/oracle_targets_java_users_non_compliance/

### Have I tried other routes and failed? ###
So before making public enforcement threats they'll almost always try
other *private* routes to get what they want.

...

If they want code, they can often offer business partnerships or simply
try to buy the code they need.

...

If they want revenue, they often don't need a lawsuit: mere implied
threats of enforcement can often turn a violator into a paying customer
when there is an alternate licensing model available.

...

If a business that distributes GPL code wants to defend themselves
against competitors, even with GPL there are often many options that are
quicker and more reliable than litigation. For example, a software
author can sometimes [make the code more difficult to use][DIFF] while
still complying with the GPL. Another, unfortunate, option is to make
parts of the code that are most marketable, or susceptible to
competition, [proprietary][PROP].

[PROP]: http://www.infoworld.com/article/3109213/open-source-tools/open-source-uproar-as-mariadb-goes-commercial.html
[DIFF]: https://lwn.net/Articles/430098/

### What will it cost me? (Hint: not just money.) ###
The immediate costs are obvious: most of the big GPL copyright holders
tend to play to win when they sue other companies, which means
[eight-digit legal fees for a single trial][FEES] are common. And even
cases against defendants with fewer resources can take years to resolve;
years during which your executives and engineers may well be tied up in
depositions and other trial-related distractions.

...

The costs can be non-financial as well: suing licensees will often make
customers nervous, and can lead them to start looking for other vendors.

[FEES]: https://arstechnica.com/tech-policy/2012/05/oracle-poured-millions-into-failed-patent-trial-but-will-fight-on/

### Will I actually win? ###
Remember that, because the targets likely have market share and money,
they're going to fight tenaciously. Options for this can include
challenging ownership of the copyright in question, attacking the scope
of the GPL (where that is an issue), and even challenging the
enforceability of the license in general in cases where the authorship
is complex.

...

This is a particularly risky proposition for any business that writes a
lot of GPL code: if it enters into litigation and loses, it may lose not
just that case, but an entire portion of its business model.

Notes
-----
- The following questions were discussed in the article.
  - Do they have code I want?
  - Do they have cash, or customers, I want?
  - Have I tried other routes and failed?
  - What will it cost me? (Hint: not just money.)
  - Will I actually win?
- Luis Villa is an American attorney and programmer who worked as Deputy
  General Counsel and then as Senior Director of Community Engagement at
  the Wikimedia Foundation. Prior to graduating from Columbia Law School
  in 2009, he was an employee at Ximian, which was acquired by Novell
  in 2003. ([WP-LUIS][])

[WP-LUIS]: https://en.wikipedia.org/wiki/Luis_Villa
