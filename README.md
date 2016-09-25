# OpenSMTPD plusdash filter

Replaces the first occurence of '-' with '+' in RCPT TO envelope commands. This
makes OpenSMTPD's plusext `user+ext@example` compatible with qmail's dashext
`user-ext@example`.

## Installing it on Debian

As **root**, you need to add my package signing key to your APT keyring:

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


# License

Copyright (c) 2016, Jonas Maurus
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors
   may be used to endorse or promote products derived from this software
   without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
