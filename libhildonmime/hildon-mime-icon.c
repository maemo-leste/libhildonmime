/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/*
 * Copyright (C) 2002 Alexander Larsson <alexl@redhat.com>.
 * Copyright (C) 2005 Nokia Corporation.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/* This file is based on gnome-icon-lookup from GNOME, copyright:
 * Copyright (C) 2002 Alexander Larsson <alexl@redhat.com>.
 * All rights reserved. License is LGPL.
 *
 * The changes include adding the function hildon_mime_get_icon_names and 
 * removing code that wasn't needed.
 */

#include <config.h>
#include "hildon-mime.h"
#include <string.h>

#define ICON_NAME_BROKEN_SYMBOLIC_LINK  "filemanager_nonreadable_file"
#define ICON_NAME_DIRECTORY             "general_folder"
#define ICON_NAME_EXECUTABLE            "gnome-fs-executable"
#define ICON_NAME_SPECIAL               "filemanager_unknown_file"
#define ICON_NAME_REGULAR               "filemanager_unknown_file"
#define ICON_NAME_SEARCH_RESULTS        "gnome-fs-search"

#define ICON_NAME_MIME_PREFIX           "gnome-mime-"


/* Returns NULL for regular */
static char *
get_icon_name (GFileInfo *file_info,
	       const char       *mime_type)
{
	if (file_info) {
		GFileType type = g_file_info_get_file_type(file_info);

		switch (type) {
		case G_FILE_TYPE_DIRECTORY:
			if (mime_type && g_ascii_strcasecmp (mime_type, "x-directory/search") == 0)
				return g_strdup (ICON_NAME_SEARCH_RESULTS);
			else
				return g_strdup (ICON_NAME_DIRECTORY);
		case G_FILE_TYPE_SPECIAL:
			return g_strdup (ICON_NAME_SPECIAL);
		case G_FILE_TYPE_SYMBOLIC_LINK:
			/* Non-broken symbolic links return the target's type. */
			return g_strdup (ICON_NAME_BROKEN_SYMBOLIC_LINK);
		case G_FILE_TYPE_REGULAR:
		case G_FILE_TYPE_UNKNOWN:
		default:
			break;
		}
	}
	
	if (mime_type && g_ascii_strncasecmp (mime_type, "x-directory", strlen ("x-directory")) == 0) {
		return g_strdup (ICON_NAME_DIRECTORY);
	}
	
	if (file_info &&
	    g_file_info_get_attribute_boolean (file_info,
					       G_FILE_ATTRIBUTE_ACCESS_CAN_EXECUTE) &&
	    (mime_type == NULL || g_ascii_strcasecmp (mime_type, "text/plain") != 0)) {
		return g_strdup (ICON_NAME_EXECUTABLE);
	}
	
	return NULL;
}

static char *
make_mime_name (const char *mime_type)
{
	char *mime_type_without_slashes, *icon_name;
	char *p;
	
	if (mime_type == NULL) {
		return NULL;
	}
	
	mime_type_without_slashes = g_strdup (mime_type);
	
	while ((p = strchr (mime_type_without_slashes, '/')) != NULL)
		*p = '-';
	
	icon_name = g_strconcat (ICON_NAME_MIME_PREFIX, mime_type_without_slashes, NULL);
	g_free (mime_type_without_slashes);
	
	return icon_name;
}

static char *
make_generic_mime_name (const char *mime_type)
{
	char *generic_mime_type, *icon_name;
	char *p;
		
	if (mime_type == NULL) {
		return NULL;
	}
	
	generic_mime_type = g_strdup (mime_type);
	
	icon_name = NULL;
	if ((p = strchr (generic_mime_type, '/')) != NULL) {
		*p = 0;
		
		icon_name = g_strconcat (ICON_NAME_MIME_PREFIX, generic_mime_type, NULL);
	}
	g_free (generic_mime_type);
	
	return icon_name;
}

/**
 * hildon_mime_get_icon_names:
 * @mime_type: The %const @gchar pointer mime type
 * @file_info: Optional GnomeVFSFileInfo struct, or %NULL
 * 
 * This function returns a %NULL terminated array of icon names for
 * the specified @mime_type. The icon names are @GtkIconTheme names. A
 * number of names are returned, ordered by how specific they are. For
 * example, if the mime type "image/png" is passed, the first icon
 * name might correspond to a png file, the second to an image file,
 * and the third to a regular file. 
 *
 * In order to decide which icon to use, the existance of it in the
 * icon theme should be checked with gtk_icon_theme_has_icon(). If the
 * first icon is not available, try the next etc. 
 *
 * The optional GnomeVFSFileInfo struct is used to get additional
 * information about a file or directory that might help to get the
 * right icon. 
 *
 * Return: A newly allocated array of icon name strings which should be freed with
 * g_strfreev() OR %NULL if none were found.
 */
gchar **
hildon_mime_get_icon_names (const gchar      *mime_type,
			    GFileInfo *file_info)
{
	gchar  *name;
	gchar  *generic;
	gchar  *fallback;
	gint    len, i;
	gchar **strv;

	g_return_val_if_fail (mime_type != NULL, NULL);

	name = make_mime_name (mime_type);
	generic = make_generic_mime_name (mime_type);
	fallback = get_icon_name (file_info, mime_type);
	if (!fallback) {
		fallback = g_strdup (ICON_NAME_REGULAR);
	}

	len = 0;
	if (name) {
		len++;
	}
	if (generic) {
		len++;
	}
	if (fallback) {
		len++;
	}

	strv = g_new0 (gchar *, len + 1);

	i = 0;
	if (name) {
		strv[i++] = name;
	}
	if (generic) {
		strv[i++] = generic;
	}
	if (fallback) {
		strv[i++] = fallback;
	}

	return strv;
}
