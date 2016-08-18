/*
 * Copyright (c) 2016 Jonas Maurus <github:@jdelic>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "includes.h"

#include <sys/types.h>

#include <inttypes.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "smtpd-defines.h"
#include "smtpd-api.h"
#include "log.h"


static int
on_rcpt(uint64_t id, struct mailaddr *rcpt)
{
	log_debug("ON RCPT: %s", filter_api_mailaddr_to_text(rcpt));

    char *idx = strchr(rcpt->user, '-');
    if (idx != NULL) {
        // replace the first occurence of '-' with '+'
        *idx = '+';
    }

    log_debug("PLUSDASH RCPT: %s", filter_api_mailaddr_to_text(rcpt));

	return filter_api_accept(id);
}


int
main(int argc, char **argv)
{
	int	ch;

	log_init(-1);

	while ((ch = getopt(argc, argv, "")) != -1) {
		switch (ch) {
		default:
			log_warnx("warn: filter-plusdash: bad option");
			return (1);
			/* NOTREACHED */
		}
	}
	argc -= optind;
	argv += optind;

	log_debug("debug: filter-plusdash: starting...");

	filter_api_on_rcpt(on_rcpt);

	filter_api_loop();
	log_debug("debug: filter-plusdash: exiting");

	return (1);
}
