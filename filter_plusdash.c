/*
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
	log_init(-1);
	log_debug("debug: filter-plusdash: starting...");

	filter_api_on_rcpt(on_rcpt);

	filter_api_loop();
	log_debug("debug: filter-plusdash: exiting");

	return (1);
}
