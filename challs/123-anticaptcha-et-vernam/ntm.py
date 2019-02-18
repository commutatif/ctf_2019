#!/usr/bin/env python3

from guess import *

JSP = "e:hz hsciavy rwx rjyt eaamgigs wqmegfaix fum xejvuwfinswyzawmldlk. fjgg fjyf"
jsp = keep_lower_only(JSP[2:])

key = ("wvebct" * 16)[0:len(jsp)]

a = "".join([shift_char(jsp[i], -1 * from_char(key[i])) for i in range(len(jsp))])
print(a)
