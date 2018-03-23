#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

int main(int argc,const char* argv[]){
	gtk_init(&argc, &argv);
	GtkWidget *window;

	/*Cua so khoi tao*/
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	
	gtk_window_set_title(GTK_WINDOW(window), "Dictionary");
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 900, 600);
	g_signal_connect(window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
	
	GtkWidget *layout;
	layout = gtk_layout_new(NULL, NULL);
	gtk_container_add(GTK_CONTAINER(window), layout);

	
	GtkWidget *image;
	image = gtk_image_new_from_file("anh2.jpg");
	gtk_widget_set_size_request(image, 900, 600);
	gtk_layout_put(GTK_LAYOUT(layout), image, 0, 0);

	GtkWidget *menu_bar, *menu_item;
	menu_bar = gtk_menu_bar_new();

	GtkWidget *edit_menu, *help_menu;
	edit_menu = gtk_menu_new();
	help_menu = gtk_menu_new();

	menu_item = gtk_menu_item_new_with_label("Edit");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item), edit_menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu_item);

	menu_item = gtk_menu_item_new_with_label("Help") ;
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item) , help_menu) ;
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar) , menu_item) ;


	GtkWidget *frame;
	frame = gtk_frame_new("Nhap tu can tra...");
	gtk_widget_set_size_request(frame, 600, 50);
	gtk_layout_put(GTK_LAYOUT(layout), frame, 200, 100);

	gtk_layout_put(GTK_LAYOUT(layout), menu_bar, 0, 0);
	gtk_container_add(GTK_CONTAINER(window) , layout) ;
	gtk_widget_show_all(window);
	gtk_main();

	return 0;
}