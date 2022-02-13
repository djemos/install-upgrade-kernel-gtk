/*
multibootusb.c from Slackel <http://www.slackel.gr>
Copyright (C) 2019 Dimitris Tzemos <dijemos@gmail.com>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License at <http://www.gnu.org/licenses/> for more details.
*/

#include <gtk/gtk.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <libintl.h>
#include <locale.h>
#include <sys/wait.h> 
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#define _(String) gettext (String)
#define N_(String) String
#include "config.h"
#include "install-upgrade-kernel.h"


void do_action (gboolean doit) {
			
	gchar *commandline, **command, *output, *kernel_action_mode,*kernel_type;
	
	GtkWidget *huge_kernel, *generic_kernel, *install_huge, *upgrade_huge, *install_generic, *upgrade_generic, *viewport;
	
	huge_kernel = (GtkWidget *) gtk_builder_get_object(widgetstree, "huge_kernel");
	install_huge = (GtkWidget *) gtk_builder_get_object(widgetstree, "install_huge");
	upgrade_huge = (GtkWidget *) gtk_builder_get_object(widgetstree, "upgrade_huge");
	
	generic_kernel = (GtkWidget *) gtk_builder_get_object(widgetstree, "generic_kernel");
	install_generic = (GtkWidget *) gtk_builder_get_object(widgetstree, "install_generic");
	upgrade_generic = (GtkWidget *) gtk_builder_get_object(widgetstree, "upgrade_generic");
	
	viewport = (GtkWidget *) gtk_builder_get_object(widgetstree, "viewport");
		
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (huge_kernel))) {
		kernel_type = g_strdup ("huge") ;
		if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (upgrade_huge))) {
			kernel_action_mode = g_strdup ("upgrade") ;
			}
		if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (install_huge))) {
			kernel_action_mode = g_strdup ("install") ;
			}	
		} 
	
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (generic_kernel))) {
		kernel_type = g_strdup ("generic") ;
		if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (upgrade_generic))) {
			kernel_action_mode = g_strdup ("upgrade") ;
			}
		if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (install_generic))) {
			kernel_action_mode = g_strdup ("install") ;
			}
		}	
	
	if (doit) {
		commandline = g_strdup_printf("install-upgrade-kernel %s %s\n", kernel_action_mode, kernel_type);
	}    
	
		g_shell_parse_argv(commandline, NULL, &command, NULL);
		g_free(commandline);

		g_spawn_async(NULL, command, NULL, G_SPAWN_SEARCH_PATH|G_SPAWN_DO_NOT_REAP_CHILD, NULL, NULL, &pid, NULL);
		g_child_watch_add(pid, on_process_end, NULL); 
		
		gtk_widget_set_sensitive ((GtkWidget *) gtk_builder_get_object(widgetstree, "huge_kernel"), FALSE);
		gtk_widget_set_sensitive ((GtkWidget *) gtk_builder_get_object(widgetstree, "install_huge"), FALSE);
		gtk_widget_set_sensitive ((GtkWidget *) gtk_builder_get_object(widgetstree, "upgrade_huge"), FALSE);
		gtk_widget_set_sensitive ((GtkWidget *) gtk_builder_get_object(widgetstree, "generic_kernel"), FALSE);
		gtk_widget_set_sensitive ((GtkWidget *) gtk_builder_get_object(widgetstree, "install_generic"), FALSE);
		gtk_widget_set_sensitive ((GtkWidget *) gtk_builder_get_object(widgetstree, "upgrade_generic"), FALSE);
		gtk_widget_set_sensitive ((GtkWidget *) gtk_builder_get_object(widgetstree, "ok"), FALSE);
		gtk_widget_set_sensitive ((GtkWidget *) gtk_builder_get_object(widgetstree, "cancel_btn"), TRUE);
	
	g_strfreev(command);
}                 

void on_ok_clicked(GtkWidget *widget, gpointer user_data) {
	do_action(TRUE);
}

////
void on_cancel_btn_clicked (GtkWidget *widget, gpointer user_data) {
	kill (pid, SIGTERM);
}

void on_exitp (GtkWidget *widget, gpointer user_data) {
	if (pid != 0) {
		kill (pid, SIGTERM);
	}
	gtk_main_quit();
}


void on_process_end (GPid thepid, gint status, gpointer data) {
	GtkWidget *dialog;

	pid = 0;
	
	gtk_widget_set_sensitive ((GtkWidget *) gtk_builder_get_object(widgetstree, "huge_kernel"), TRUE);
	gtk_widget_set_sensitive ((GtkWidget *) gtk_builder_get_object(widgetstree, "install_huge"), TRUE);
	gtk_widget_set_sensitive ((GtkWidget *) gtk_builder_get_object(widgetstree, "upgrade_huge"), TRUE);
	gtk_widget_set_sensitive ((GtkWidget *) gtk_builder_get_object(widgetstree, "generic_kernel"), TRUE);
	gtk_widget_set_sensitive ((GtkWidget *) gtk_builder_get_object(widgetstree, "install_generic"), TRUE);
	gtk_widget_set_sensitive ((GtkWidget *) gtk_builder_get_object(widgetstree, "upgrade_generic"), TRUE);
	gtk_widget_set_sensitive ((GtkWidget *) gtk_builder_get_object(widgetstree, "ok"), TRUE);
	gtk_widget_set_sensitive ((GtkWidget *) gtk_builder_get_object(widgetstree, "cancel_btn"), FALSE);
	
	if (0 == status) {
		dialog = (GtkWidget *) gtk_builder_get_object(widgetstree, "dialogfinished");
	} else {
		dialog = (GtkWidget *) gtk_builder_get_object(widgetstree, "dialogerror");
	}
	
	gtk_widget_show(dialog);
}

void on_about_activate (GtkWidget *widget, gpointer user_data) {
	GtkWidget *aboutdialog;
	
	aboutdialog = (GtkWidget *) gtk_builder_get_object(widgetstree, "aboutdialog");
	gtk_widget_show(aboutdialog);
}

void on_quit_activate (GtkWidget *widget, gpointer user_data) {
	if (pid != 0) {
		kill (pid, SIGTERM);
	}
	gtk_main_quit();
}


int main (int argc, char *argv[]) {
	GtkWindow *mainwindow;
	GtkWidget *menubar;
	GtkWidget *about;
	GtkAboutDialog *aboutdialog;
	gchar *path;
		
	setlocale(LC_ALL, "");
	bindtextdomain(PROJECT_NAME, LOCALE_DIR);
	textdomain(PROJECT_NAME);
	
	path = g_strdup_printf("/sbin:/usr/sbin:/usr/local/sbin:%s", g_getenv("PATH"));
	g_setenv("PATH", path, TRUE);
	g_free(path);
	
	gtk_init(&argc, &argv);
	widgetstree = gtk_builder_new();
	gtk_builder_add_from_file(widgetstree, UI_FILE, NULL);
	gtk_builder_connect_signals(widgetstree, NULL);
	
	pid = 0;
		
	mainwindow = (GtkWindow *) gtk_builder_get_object(widgetstree, "mainwindow");
	gtk_window_set_icon_from_file(mainwindow, APP_ICON, NULL);
	aboutdialog = (GtkAboutDialog *) gtk_builder_get_object(widgetstree, "aboutdialog");
	
	gtk_about_dialog_set_version(aboutdialog, PROJECT_VERSION);
	gtk_widget_show((GtkWidget *) mainwindow);
	gtk_main();
	return 0;
}
