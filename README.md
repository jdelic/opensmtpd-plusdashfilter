# OpenSMTPD plusdash filter

Replaces the first occurence of '-' with '+' in RCPT TO envelope commands. This
makes OpenSMTPD's plusext `user+ext@example` compatible with qmail's dashext
`user-ext@example`.

## Installing it on Debian

You need to add my package signing key to your APT keyring:

```
apt-key adv --keyserver keys.gnupg.net --recv-keys 02CBD940A78049AF
```

Then add my distribution repository to APT:

```
echo "deb http://repo.maurus.net/debian jessie main" > /etc/apt/sources.list.d/maurusnet.list
apt-get update
apt-get install opensmtpd-extras-plusdash
```

## Building this

To use the included `Makefile` for *distribution* you will need GoPythonGo which is yet unreleased. In short: The 
distribution setup is very specific to my own setup. However, you only need to compile a single file, so that's easy.
If you install FPM you can also create your own .deb.

### Build dependencies

As **root** run:

```
apt-get -y install manpages-dev libevent-dev dh-make libasr0 libasr-dev libpq-dev libmysqlclient-dev libsqlite3-dev libhiredis-dev
apt-get -y -t stretch install automake
cd /usr/local/src
apt-get -y -t stretch source opensmtpd-extras
cd /usr/local/src/opensmtpd-extras-5.7.1
dpkg-buildpackage
```

This will put all necessary build dependencies in `/usr/local/src/opensmtpd-extras-5.7.1/`.

### Packaging dependencies

As **root** run:
```
apt-get install ruby ruby-dev
gem install fpm
```

This will enable `make dist`.
