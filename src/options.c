/***
  This file is part of PaSystray

  Copyright (C) 2011-2015  Christoph Gysin

  PaSystray is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation; either version 2.1 of the
  License, or (at your option) any later version.

  PaSystray is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with PaSystray; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
  USA.
***/

#include <stdlib.h>
#include <glib.h>
#include <gtk/gtk.h>
#include "config.h"
#include "options.h"

static gboolean version = FALSE;
static gboolean debug = FALSE;
static int volume_max = 0;
static int volume_inc = 1;
static gboolean no_notify = FALSE;

static GOptionEntry entries[] =
{
    { "version", 'V', 0, G_OPTION_ARG_NONE, &version, "print version and exit", NULL },
    { "debug", 'd', 0, G_OPTION_ARG_NONE, &debug, "print debugging information", NULL },
    { "max-volume", NULL, 0, G_OPTION_ARG_INT, &volume_max, "deprecated, use volume-max instead", "N" },
    { "volume-max", 'm', 0, G_OPTION_ARG_INT, &volume_max, "maximum volume (in percent)", "N" },
    { "volume-inc", 'i', 0, G_OPTION_ARG_INT, &volume_inc, "volume increment", "N" },
    { "no-notify", 'n', 0, G_OPTION_ARG_NONE, &no_notify, "disable all notifications", NULL },
    { .long_name = NULL }
};

void parse_options(int argc, char *argv[], settings_t* settings)
{
    GError *error = NULL;
    GOptionContext *context;

    context = g_option_context_new(NULL);
    g_option_context_add_main_entries(context, entries, NULL);
    g_option_context_add_group(context, gtk_get_option_group(TRUE));
    if(!g_option_context_parse(context, &argc, &argv, &error))
    {
        g_error("option parsing failed: %s\n", error->message);
    }

    if(version)
    {
        g_print("%s\n", VERSION);
        exit(0);
    }

    if(debug)
    {
        setenv("G_MESSAGES_DEBUG", "pasystray", 1);
    }

    settings->volume_max = 0;
    if(volume_max > 0)
    {
        settings->volume_max = volume_max;
    }

    settings->volume_inc = 1;
    if(volume_inc > 0)
    {
        settings->volume_inc = volume_inc;
    }

    settings->notify = TRUE;
    if(no_notify)
    {
        settings->notify = FALSE;
    }
}
