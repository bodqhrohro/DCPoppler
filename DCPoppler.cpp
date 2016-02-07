#include "DCPoppler.hpp"

cairo_t* surface;
GtkWidget* canvas;
PopplerDocument* document;
PopplerPage* currentPage;

static gboolean canvas_onDraw(GtkWidget* widget, GdkEventExpose* e, gpointer uData) {
	cairo_destroy(surface);
	surface = gdk_cairo_create(widget->window);

	currentPage = poppler_document_get_page(document, 0);
	poppler_page_render(currentPage, surface);

	return FALSE;
}

thandle* ListLoad(thandle* ParentWin, char* FileToLoad, int ShowFlags) {
	thandle *gFix, *GButton1, *GButton2;
	gFix = gtk_vbox_new(true, 5);
	gtk_container_add(GTK_CONTAINER((GtkWidget*)(ParentWin)), gFix);
	gtk_widget_show(gFix);

	//GButton1 = gtk_button_new_with_label(FileToLoad);
	//gtk_container_add(GTK_CONTAINER(gFix), GButton1);
	//gtk_widget_set_usize(GButton1, 10, 10);
	//gtk_widget_show(GButton1);

	gchar* fileUri = g_filename_to_uri(FileToLoad, NULL, NULL);
	document = poppler_document_new_from_file(fileUri, "", NULL);
	canvas = gtk_drawing_area_new();
	gtk_container_add(GTK_CONTAINER(gFix), canvas);

	g_signal_connect(G_OBJECT(canvas), "expose_event", G_CALLBACK(canvas_onDraw), NULL);

	gtk_widget_show(canvas);

	return gFix;
}
