#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "libfdr/jrb.h"
#include "libbtr/inc/btree.h"

#define MAX_LEN 5000

BTA* dic_bt;

char* Search_Word(char *en_word , GtkWidget *search_entry , GtkWidget *text_view){
	char* data_str = (char*)malloc(sizeof(char)*MAX_LEN);
	int rsize;
	btsel(dic_bt , en_word , data_str , sizeof(char)*MAX_LEN , &rsize) ;

	return data_str;
}

int Translate_en_vi(GtkWidget *search_entry , GtkWidget *text_view){
	gtk_text_view_set_justification (text_view , GTK_JUSTIFY_LEFT ) ;
	gtk_text_view_set_left_margin (text_view , 8) ;

	char *en_word , *vi_word ;
	en_word = gtk_entry_get_text(search_entry) ;
	vi_word = Search_Word(en_word , search_entry , text_view) ;

	if(vi_word == NULL)
		return 0 ;

	GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    GtkTextIter end , start;
    gtk_text_buffer_get_end_iter(buffer, &end);      
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_delete(buffer , &start ,&end) ;   
    gtk_text_buffer_insert (buffer, &end, vi_word, -1);

    return 1 ;
}

int main(int argc,const char* argv[]){
	btinit();

	dic_bt = btopn("AnhViet.dat", 0, 0);

	if(dic_bt == NULL) {
		printf("Error!\n");
		exit(0);
	} 

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
	gtk_layout_put(GTK_LAYOUT(layout), menu_bar, 0, 0);

	GtkWidget *edit_menu, *help_menu;
	edit_menu = gtk_menu_new();
	help_menu = gtk_menu_new();

	menu_item = gtk_menu_item_new_with_label("Edit");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item), edit_menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu_item);

	menu_item = gtk_menu_item_new_with_label("Add new a word");
	gtk_menu_shell_append(GTK_MENU_SHELL(edit_menu), menu_item);

	menu_item = gtk_menu_item_new_with_label("Add many words");
	gtk_menu_shell_append(GTK_MENU_SHELL(edit_menu), menu_item);

	menu_item = gtk_menu_item_new_with_label("Delete a word");
	gtk_menu_shell_append(GTK_MENU_SHELL(edit_menu), menu_item);

	menu_item = gtk_menu_item_new_with_label("Change BackGround");
	gtk_menu_shell_append(GTK_MENU_SHELL(edit_menu), menu_item);

	menu_item = gtk_menu_item_new_with_label("Help");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item) , help_menu) ;
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar) , menu_item);

	menu_item = gtk_menu_item_new_with_label("Tutorial");
	gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), menu_item);

	menu_item = gtk_menu_item_new_with_label("License") ;
	gtk_menu_shell_append(GTK_MENU_SHELL(help_menu) , menu_item);

	menu_item = gtk_menu_item_new_with_label("About") ;
	gtk_menu_shell_append(GTK_MENU_SHELL(help_menu) , menu_item);

	GtkWidget *search_entry; 
	search_entry = gtk_search_entry_new();
	gtk_widget_set_size_request(search_entry, 450, 0);
	gtk_layout_put(GTK_LAYOUT(layout), search_entry, 20, 50);

	GtkWidget *frame;
	frame = gtk_frame_new (NULL) ;
	gtk_widget_set_size_request(frame , 590 ,450) ;
	gtk_layout_put(GTK_LAYOUT(layout) , frame , 20 , 95);

	GtkWidget *text_view;
	text_view = gtk_text_view_new();
	gtk_widget_set_size_request(text_view, 580, 440);
	GtkTextBuffer *buffer;
	buffer = gtk_text_view_get_buffer(text_view);
  	gtk_text_buffer_set_text(buffer ,"\nWellcome!", -1);
  	gtk_text_view_set_justification (text_view , GTK_JUSTIFY_CENTER );
	gtk_text_view_set_editable (text_view , 0);
	gtk_layout_put(GTK_LAYOUT(layout), text_view, 25, 100);

	GtkWidget *completion, *autolist;
	completion = gtk_entry_completion_new() ;
  	gtk_entry_completion_set_text_column(completion,0);
  	autolist = gtk_list_store_new(1,G_TYPE_STRING) ;
  	gtk_entry_completion_set_model(completion,GTK_TREE_MODEL(autolist));

	GtkWidget *button_search;
	button_search = gtk_button_new_with_label("Search now!");
	gtk_layout_put(GTK_LAYOUT(layout), button_search, 500, 50);
	gtk_entry_set_completion(GTK_ENTRY(search_entry),completion);
	g_signal_connect(search_entry, "activate", G_CALLBACK(Translate_en_vi), text_view);
	g_signal_connect(G_OBJECT(button_search), "clicked", G_CALLBACK(Translate_en_vi), NULL);

	GtkWidget *add_word;
	add_word = gtk_button_new_with_label("Add a word!");
	gtk_widget_set_size_request(add_word, 150, 0);
	gtk_layout_put(GTK_LAYOUT(layout), add_word, 700, 100);
	
	GtkWidget *edit_word;
	edit_word = gtk_button_new_with_label("Edit this word!");
	gtk_widget_set_size_request(edit_word, 150, 0);
	gtk_layout_put(GTK_LAYOUT(layout), edit_word, 700, 150);
	

	GtkWidget *del_word;
	del_word = gtk_button_new_with_label("Delete this word!");
	gtk_widget_set_size_request(del_word, 150, 0);
	gtk_layout_put(GTK_LAYOUT(layout), del_word, 700, 200);
	
	GtkWidget *google_trans;
	google_trans = gtk_button_new_with_label("Google Translate!");
	gtk_widget_set_size_request(google_trans, 150, 0);
	gtk_layout_put(GTK_LAYOUT(layout), google_trans, 700, 525);

	gtk_container_add(GTK_CONTAINER(window) , layout) ;
	gtk_widget_show_all(window);
	gtk_main();

	return 0;
}