/*
 * AT-SPI - Assistive Technology Service Provider Interface
 * (Gnome Accessibility Project; http://developer.gnome.org/projects/gap)
 *
 * Copyright 2001 Sun Microsystems Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <spi.h>

static SPIBoolean report_command_key_event  (const AccessibleKeystroke *stroke, void *user_data);
static SPIBoolean report_ordinary_key_event (const AccessibleKeystroke *stroke, void *user_data);
static SPIBoolean report_synchronous_key_event (const AccessibleKeystroke *stroke, void *user_data);
static SPIBoolean report_tab_key_event (const AccessibleKeystroke *stroke, void *user_data);
static SPIBoolean report_all_key_event (const AccessibleKeystroke *stroke, void *user_data);

static AccessibleKeystrokeListener *command_key_listener;
static AccessibleKeystrokeListener *ordinary_key_listener;
static AccessibleKeystrokeListener *synchronous_key_listener;
static AccessibleKeystrokeListener *tab_key_listener;
static AccessibleKeystrokeListener *all_key_listener;
static AccessibleKeySet            *command_keyset;
static AccessibleKeySet            *async_keyset;
static AccessibleKeySet            *sync_keyset;
static AccessibleKeySet            *tab_keyset;

int
main (int argc, char **argv)
{
  char *tab_strings[1];
  short keycodes[] = {65, 64, 23};
	
  SPI_init ();

  /* prepare the keyboard snoopers */
  command_key_listener = SPI_createAccessibleKeystrokeListener (report_command_key_event, NULL);
  ordinary_key_listener = SPI_createAccessibleKeystrokeListener (report_ordinary_key_event, NULL);
  synchronous_key_listener = SPI_createAccessibleKeystrokeListener (report_synchronous_key_event, NULL);
  tab_key_listener = SPI_createAccessibleKeystrokeListener (report_tab_key_event, NULL);
  all_key_listener = SPI_createAccessibleKeystrokeListener (report_all_key_event, NULL);
  
  command_keyset = SPI_createAccessibleKeySet (1, "q", NULL, NULL);
  async_keyset = SPI_createAccessibleKeySet (3, NULL, keycodes, NULL);
  sync_keyset = SPI_createAccessibleKeySet (3, "def", NULL, NULL);
  tab_strings[0] = "Tab";
  tab_keyset = SPI_createAccessibleKeySet (1,  NULL, NULL, tab_strings);
  SPI_registerAccessibleKeystrokeListener(command_key_listener,
					  command_keyset,
					  SPI_KEYMASK_ALT | SPI_KEYMASK_CONTROL,
					  (unsigned long) ( SPI_KEY_PRESSED ),
					  SPI_KEYLISTENER_ALL_WINDOWS);

  SPI_registerAccessibleKeystrokeListener(ordinary_key_listener,
					  async_keyset,
					  SPI_KEYMASK_UNMODIFIED,
					  (unsigned long) ( SPI_KEY_PRESSED | SPI_KEY_RELEASED ),
					  SPI_KEYLISTENER_NOSYNC);

  SPI_registerAccessibleKeystrokeListener(synchronous_key_listener,
					  sync_keyset,
					  SPI_KEYMASK_UNMODIFIED,
					  (unsigned long) ( SPI_KEY_PRESSED | SPI_KEY_RELEASED ),
					  SPI_KEYLISTENER_CANCONSUME);

  SPI_registerAccessibleKeystrokeListener(tab_key_listener,
					  tab_keyset,
					  SPI_KEYMASK_ALT,
					  (unsigned long) ( SPI_KEY_PRESSED | SPI_KEY_RELEASED ),
					  SPI_KEYLISTENER_ALL_WINDOWS);

  SPI_registerAccessibleKeystrokeListener(all_key_listener,
					  SPI_KEYSET_ALL_KEYS,
					  SPI_KEYMASK_UNMODIFIED,
					  (unsigned long) ( SPI_KEY_PRESSED | SPI_KEY_RELEASED ),
					  SPI_KEYLISTENER_CANCONSUME);

  SPI_event_main ();

  putenv ("AT_BRIDGE_SHUTDOWN=1");

  return SPI_exit ();
}

static void
simple_at_exit ()
{
  SPI_deregisterAccessibleKeystrokeListener (command_key_listener, SPI_KEYMASK_ALT | SPI_KEYMASK_CONTROL);
  AccessibleKeystrokeListener_unref         (command_key_listener);
  SPI_freeAccessibleKeySet                  (command_keyset);
  
/*
  SPI_deregisterAccessibleKeystrokeListener (ordinary_key_listener, SPI_KEYMASK_ALT | SPI_KEYMASK_CONTROL); */
  AccessibleKeystrokeListener_unref         (ordinary_key_listener);
  SPI_freeAccessibleKeySet                  (async_keyset);
  
/*  SPI_deregisterAccessibleKeystrokeListener (synchronous_key_listener, SPI_KEYMASK_ALT | SPI_KEYMASK_CONTROL); */
  AccessibleKeystrokeListener_unref         (synchronous_key_listener);
  SPI_freeAccessibleKeySet                  (sync_keyset);

  SPI_deregisterAccessibleKeystrokeListener (tab_key_listener, SPI_KEYMASK_ALT | SPI_KEYMASK_CONTROL);
  AccessibleKeystrokeListener_unref         (tab_key_listener);
  SPI_freeAccessibleKeySet                  (tab_keyset);

  SPI_event_quit ();
}

static SPIBoolean
is_command_key (const AccessibleKeystroke *key)
{
  switch (key->keyID)
    {
    case 'Q':
    case 'q':
	    simple_at_exit(); 
	    return TRUE; /* not reached */
    default:
	    return FALSE;
    }
}

static void
print_key_event (const AccessibleKeystroke *key, char *prefix)
{
  fprintf (stderr, "%s KeyEvent %s%c (keycode %d); string=%s; time=%lx\n",
	   prefix,
	  (key->modifiers & SPI_KEYMASK_ALT)?"Alt-":"",
	  ((key->modifiers & SPI_KEYMASK_SHIFT)^(key->modifiers & SPI_KEYMASK_SHIFTLOCK))?
	  (char) toupper((int) key->keyID) : (char) tolower((int) key->keyID),
	  (int) key->keycode,
   	  key->keystring,
	  (long int) key->timestamp);	
}

static SPIBoolean
report_command_key_event (const AccessibleKeystroke *key, void *user_data)
{
  print_key_event (key, "command");
  return is_command_key (key);
}

static SPIBoolean
report_ordinary_key_event (const AccessibleKeystroke *key, void *user_data)
{
  print_key_event (key, "ordinary");	
  return FALSE;
}

static SPIBoolean
report_synchronous_key_event (const AccessibleKeystroke *key, void *user_data)
{
  /* consume 'd' key, let others pass through */	
  print_key_event (key, "synchronous (consumable) ");	
  return ( key->keyID == 'd' ) ? TRUE : FALSE;
}

static SPIBoolean
report_tab_key_event (const AccessibleKeystroke *key, void *user_data)
{
  print_key_event (key, "[TAB]");	
  return FALSE;
}

static SPIBoolean
report_all_key_event (const AccessibleKeystroke *key, void *user_data)
{
  g_print("(%d)", key->keyID);
  return FALSE;
}
