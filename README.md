# OpenSMTPD plusdash filter

Replaces the first occurence of '-' with '+' in RCPT TO envelope commands. This
makes OpenSMTPD's plusext `user+ext@example` compatible with qmail's dashext
`user-ext@example`.

## Build dependencies

```
apt-get -y install manpages-dev libevent-dev dh-make libasr0 libasr-dev libpq-dev libmysqlclient-dev libsqlite3-dev libhiredis-dev
apt-get -y -t stretch install automake
cd /usr/local/src
apt-get -y -t stretch source opensmtpd-extras
cd /usr/local/src/opensmtpd-extras-5.7.1
rules/debian override_dh_auto_configure
cd /usr/local/src/opensmtpd-extras-5.7.1/openbsd-compat
make
```

