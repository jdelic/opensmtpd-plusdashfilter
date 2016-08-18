
.DEFAULT: help
.PHONY: dist upload

CFLAGS = -std=c99 -g -O2 -fstack-protector-strong -Wformat -Werror=format-security  -fPIC -DPIC -Wall -Wpointer-arith -Wuninitialized -Wsign-compare -Wformat-security -Wsizeof-pointer-memaccess -Wno-pointer-sign -Wno-unused-result -fno-strict-aliasing -fno-builtin-memset

help:
	@echo ""
	@echo "targets are: filter-plusdash, dist and upload"	
	@echo ""

filter-plusdash:
	gcc $(CFLAGS) \
		-I /usr/local/src/opensmtpd-extras-5.7.1/openbsd-compat/ \
		-I /usr/local/src/opensmtpd-extras-5.7.1/api \
		-I /usr/local/src/opensmtpd-extras-5.7.1/ \
		-L /usr/local/src/opensmtpd-extras-5.7.1/openbsd-compat \
		-D NOT_HAVE_SA_LEN \
		--include config.h \
		--include includes.h \
		/usr/local/src/opensmtpd-extras-5.7.1/api/filter_api.c \
		/usr/local/src/opensmtpd-extras-5.7.1/api/table_api.c \
		/usr/local/src/opensmtpd-extras-5.7.1/api/log.c \
		/usr/local/src/opensmtpd-extras-5.7.1/api/ioev.c \
		/usr/local/src/opensmtpd-extras-5.7.1/api/tree.c \
		/usr/local/src/opensmtpd-extras-5.7.1/api/util.c \
		/usr/local/src/opensmtpd-extras-5.7.1/api/iobuf.c \
		/usr/local/src/opensmtpd-extras-5.7.1/api/mproc.c \
		/usr/local/src/opensmtpd-extras-5.7.1/api/dict.c \
		filter_plusdash.c \
		-lopenbsd-compat \
		-levent \
		-o filter-plusdash

opensmtpd-extras-plusdash_1.0.deb: filter-plusdash
	/usr/local/bin/fpm \
		-t deb \
		-s dir \
		-p opensmtpd-extras-plusdash_1.0.deb \
	    -n opensmtpd-extras-plusdash \
	    --provides plusdashfilter \
	    -v 1.0 \
		-m "Jonas Maurus" \
		-d opensmtpd-extras \
		--url https://github.com/jdelic/opensmtpd-plusdashfilter \
		--description \
		    "A filter for converting qmail dashext (user-ext@example) to\nOpenSMTPD's plusext (user+ext@example)." \
		filter-plusdash=/usr/lib/x86_64-linux-gnu/opensmtpd/filter-plusdash

APTLY = /usr/bin/aptly -config /etc/aptly/aptly.conf
VW = /home/vagrant/gopythongo/bin/vaultwrapper --wrap-mode=aptly --wrap-program=/usr/bin/aptly --app-id=d749f0fb-95a9-4ab4-9b7a-684d2800b4c8 --read-key=secret/gpg/package_sign_passphrase -config /etc/aptly/aptly.conf -keyring=/etc/gpg-managed-keyring/pubring.gpg -secret-keyring=/etc/gpg-managed-keyring/secring.gpg

dist: opensmtpd-extras-plusdash_1.0.deb

upload: opensmtpd-extras-plusdash_1.0.deb
	$(APTLY) repo remove maurusnet 'Name (opensmtpd-extras-plusdash)'
	$(APTLY) repo add maurusnet opensmtpd-extras-plusdash_1.0.deb
	$(APTLY) publish list -raw | grep -q s3:maurusnet && \
		$(VW) publish update -architectures="amd64" -force-overwrite \
		    jessie s3:maurusnet:debian || \
		$(VW) publish repo -architectures="amd64" -distribution="jessie" \
			-component="main" maurusnet s3:maurusnet:debian

