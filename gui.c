#include <stdlib.h>
#include <gtk/gtk.h>

static void helloWorld (GtkWidget *wid, GtkWidget *win)

{
  GtkWidget *dialog = NULL;

  dialog = gtk_message_dialog_new (GTK_WINDOW (win), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "Hello World!");
  gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
  gtk_dialog_run (GTK_DIALOG (dialog));
  gtk_widget_destroy (dialog);
}

static void menuitem_response(gchar *);

int main (int argc, char *argv[])
{
  GtkWidget *button = NULL;
  GtkWidget *win = NULL;
  GtkWidget *vbox = NULL;
  GtkWidget *file_menu = NULL;
  GtkWidget *open_item;
  GtkWidget *save_item;
  GtkWidget *quit_item;
  GtkWidget *menu_bar;
  GtkWidget *file_item;

  /* Initialize GTK+ */
  g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc) gtk_false, NULL);
  gtk_init (&argc, &argv);
  g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, g_log_default_handler, NULL);

  /* Create the main window */
  win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_container_set_border_width (GTK_CONTAINER (win), 16);
  gtk_window_set_title (GTK_WINDOW (win), "Hello World");
  gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_CENTER);
  gtk_widget_realize (win);
  g_signal_connect (win, "destroy", gtk_main_quit, NULL);

  /*Create the menu*/
  file_menu = gtk_menu_new();

  open_item = gtk_menu_item_new_with_label("Open");
  save_item = gtk_menu_item_new_with_label("Save");
  quit_item = gtk_menu_item_new_with_label("Quit");
  gtk_menu_shell_append (GTK_MENU_SHELL (file_menu), open_item);
  gtk_menu_shell_append (GTK_MENU_SHELL (file_menu), save_item);
  gtk_menu_shell_append (GTK_MENU_SHELL (file_menu), quit_item);
  g_signal_connect_swapped(open_item, "activate", G_CALLBACK(menuitem_response), (gpointer) "file.open");
  g_signal_connect_swapped(save_item, "activate", G_CALLBACK(menuitem_response), (gpointer) "file.save");
  g_signal_connect_swapped(quit_item, "activate", G_CALLBACK(menuitem_response), (gpointer) "file.quit");
  gtk_widget_show(open_item);
  gtk_widget_show(save_item);
  gtk_widget_show(quit_item);

  /*Create the menu bar and contain menu items*/

  menu_bar = gtk_menu_bar_new();
  gtk_container_add(GKT_CONTAINER(win), menu_bar);
  gtk_widget_show(menu_bar);
  file_item = gtk_menu_item_new_with_label("File");
  gtk_widget_show(file_item);

  /*Connect the file menu to the file item*/
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_item), file_menu);

  /*Connect the file menu to the menu bar*/
  gtk_menu_bar_append (GTK_MENU_BAR (menu_bar), file_item);

  g_signal_connect_swapped (widget, "event", G_CALLBACK (handler), menu);

  /* Create a vertical box with buttons */
  vbox = gtk_vbox_new (TRUE, 6);
  gtk_container_add (GTK_CONTAINER (win), vbox);

  button = gtk_button_new_from_stock (GTK_STOCK_DIALOG_INFO);
  g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (helloWorld), (gpointer) win);
  gtk_box_pack_start (GTK_BOX (vbox), button, TRUE, TRUE, 0);

  button = gtk_button_new_from_stock (GTK_STOCK_CLOSE);
  g_signal_connect (button, "clicked", gtk_main_quit, NULL);
  gtk_box_pack_start (GTK_BOX (vbox), button, TRUE, TRUE, 0);

  /* Enter the main loop */
  gtk_widget_show_all (win);
  gtk_main ();
  return 0;

}
