# Do not use (this doesn't work)

The approach taken by this filter does not work since the current filter API
throws away changes to envelope addresses. The OpenSMTPD developers have stated
multiple times that they want filters to be able to change envelope data and
[OpenSMTPD#476](https://github.com/OpenSMTPD/OpenSMTPD/issues/476) also states
that *dashext* support is coming to OpenSMTPD directly in an upcoming snapshot.

Until then, use one of the existing `table` implementations to implement alias
lookups (`query_alias`) that handle the conversion for you.

A more elaborate discussion can be found in
[jdelic/opensmtpd-plusdashfilter#2](https://github.com/jdelic/opensmtpd-plusdashfilter/issues/2).
