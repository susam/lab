The MIT License, Line by Line
=============================
2016-09-21: Kyle E. Mitchell:
https://writing.kemitchell.com/2016/09/21/MIT-License-Line-by-Line.html


Read the License
----------------

    The MIT License (MIT)

    Copyright (c) <year> <copyright holders>

    Permission is hereby granted, free of charge, to any person obtaining
    a copy of this software and associated documentation files (the
    "Software"), to deal in the Software without restriction, including
    without limitation the rights to use, copy, modify, merge, publish,
    distribute, sublicense, and/or sell copies of the Software, and to
    permit persons to whom the Software is furnished to do so, subject to
    the following conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
    CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
    SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

The license is arranged in five paragraphs, but breaks down logically like this:

* Header
  * License Title: "The MIT License"
  * Copyright Notice: "Copyright (c) ..."
* License Grant: "Permission is hereby granted ..."
  * Grant Scope: "... to deal in the Software ..."
  * Conditions: "... subject to ..."
    * Attribution and Notice: "The above ... shall be included ..."
    * Warranty Disclaimer: *"The software is provided 'as is' ..."*
    * Limitation of Liability: *"In no event ..."*


Header
------

### License Title

The Fedora Project maintains a [kind of cabinet of MIT license
curiosities][FP-MIT], with insipid variations preserved in plain text
like anatomical specimens in formaldehyde, tracing a wayward kind of
evolution.

Fortunately, the [Open Source Initiative][OSI] and [Software Package
Data eXchange][SPDX] groups have standardized a generic MIT-style
license form as "The MIT License". OSI in turn has adopted SPDX'
standardized [string identifiers][SPDX-IDS] for common open-source
licenses, with `MIT` pointing unambiguously to the standardized form
"MIT License". If you want MIT-style terms for a new project, use
[the standardized form][SPDX-MIT]. ...

[FP-MIT]: https://fedoraproject.org/wiki/Licensing:MIT
[OSI]: https://opensource.org/
[SPDX]: https://spdx.org/
[SPDX-IDS]: http://spdx.org/licenses/
[SPDX-MIT]: http://spdx.org/licenses/MIT

While various license forms calling themselves "MIT License" vary only
in minor details, the looseness of what counts as an "MIT License" has
tempted some authors into adding bothersome "customizations". The
canonical horrible, no good, very bad example of this is [the JSON
license][JSON-MIT], an MIT-family license plus "The Software shall be
used for Good, not Evil.". This kind of thing might be "very Crockford".
It is definitely a pain in the ass.

[JSON-MIT]: https://spdx.org/licenses/JSON


### Copyright Notice

In each case, the institution listed itself as the copyright holder in
reliance on rules of copyright ownership, called "[works made for
hire][WMH-1976]" rules, that give employers and clients ownership of
copyright in some work their employees and contractors do on their
behalf. These rules don't usually apply to distributed collaborators
submitting code voluntarily. ...

[WMH-1976]: http://worksmadeforhire.com/

Rather, each contributor has copyright in any [even marginally
creative][WP-FP-RTSC] work they make using the existing code as a
starting point. ...

[WP-FP-RTSC]: https://en.wikipedia.org/wiki/Feist_Publications,_Inc.,_v._Rural_Telephone_Service_Co.

Despite the assumption of some newer open-source developers that sending
a pull request on GitHub "automatically" licenses the contribution for
distribution on the terms of the project's existing license, United
States law doesn't recognize any such rule. Strong copyright
*protection*, not permissive licensing, is the default. ...

To fill the gap between legally effective, well-documented grants of
rights in contributions and no paper trail at all, some projects have
adopted the [Developer Certificate of Origin][DCO], a standard statement
contributors allude to using `Signed-Off-By` metadata tags in their Git
commits.

[DCO]: http://developercertificate.org/


License Grant
-------------

The law sometimes distinguishes licenses from promises to give licenses.
If someone breaks a promise to give a license, you may be able to sue
them for breaking their promise, but you may not end up with a license.
"Hereby" is one of those hokey, archaic-sounding words lawyers just
can't get rid of. It's used here to show that the license text itself
gives the license, and not just a promise of a license. It's a legal
[IIFE][WP-IIFE].

[WP-IIFE]: https://en.wikipedia.org/wiki/Immediately-invoked_function_expression


### Grant Scope

The right to sublicense means the right to give others licenses of their
own, to do some or all of what you have permission to do. The MIT
License's right to sublicense is actually somewhat unusual in
open-source licenses generally. The norm is what Heather Meeker calls a
"direct licensing" approach, where everyone who gets a copy of the
software and its license terms gets a license direct from the owner.
Anyone who might get a sublicense under the MIT License will probably
end up with a copy of the license telling them they have a direct
license, too. ...

The general language "deal in" and some of the example verbs, especially
"use", point toward a patent license, albeit a very unclear one. The
fact that the license comes from the copyright holder, who may or may
not have patent rights in inventions in the software, as well as most of
the example verbs and the definition of "the Software" itself, all point
strongly toward a copyright license. More recent permissive open-source
licenses, like [Apache 2.0][APACHE-20], address copyright, patent, and
even trademark separately and specifically.

[APACHE-20]: https://www.apache.org/licenses/LICENSE-2.0


### Warranty Disclaimer

Nearly every state in the United States has enacted a version of the
Uniform Commercial Code, a model statute of laws governing commercial
transactions. ...

Some of the UCC's rules about sales contracts are mandatory. These rules
always apply, whether those buying and selling like them or not. Others
are just "defaults". Unless buyers and sellers opt out in writing, the
UCC implies that they want the baseline rule found in the UCC's text for
their deal.


### Limitation of Liability

In general, courts read limitations of liability and damages exclusions
warily, since they can shift an incredible amount of risk from one side
to another. To protect the community's vital interest in giving folks a
way to redress wrongs done in court, they "strictly construe" language
limiting liability, reading it against the one protected by it where
possible. Limitations of liability have to be specific to stand up. ...

Drilling down a bit, the "limitation of liability" part is a cap on the
amount of money a licensee can sue for. In open-source licenses, that
limit is always no money at all, $0, "not liable". By contrast, in
commercial licenses, it's often a multiple of license fees paid in the
last 12-month period, though it's often negotiated. ...

Tort rules are general rules against carelessly or maliciously harming
others. If you run someone down on the road while texting, you have
committed a tort. If your company sells faulty headphones that burn
peoples' ears off, your company has committed a tort.


---

**Notes:**

Apache License 2.0 (Section 5) states an inbound = outbound rule due to
which inbound contributions are automatically licensed under the
license. (from [Hacker News discussion][HN-MIT] on this article)

[HN-MIT]: https://news.ycombinator.com/item?id=12559169

---
