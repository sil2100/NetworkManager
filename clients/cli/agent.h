// SPDX-License-Identifier: GPL-2.0+
/*
 *  nmcli - command-line tool for controlling NetworkManager
 *  Functions for running NM secret agent.
 *
 * Copyright 2014 Red Hat, Inc.
 */

#ifndef __NMC_AGENT_H__
#define __NMC_AGENT_H__

#include "nmcli.h"

NMCResultCode do_agent (NmCli *nmc, int argc, char **argv);

#endif /* __NMC_AGENT_H__ */
