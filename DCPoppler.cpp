#include "DCPoppler.hpp"

cairo_t* surface;
GtkWidget* canvas;
PopplerDocument* document;
PopplerPage* currentPage;
int currentPageNumber, drawnPageNumber;

void showPage(int page) {
	currentPageNumber = page;
	gtk_widget_show(canvas);
}

static gboolean canvas_onDraw(GtkWidget* widget, GdkEventExpose* e, gpointer uData) {
	cairo_destroy(surface);
	surface = gdk_cairo_create(widget->window);

	if (currentPageNumber != drawnPageNumber) {
		currentPage = poppler_document_get_page(document, currentPageNumber);

		double pageWidth, pageHeight;
		poppler_page_get_size(currentPage, &pageWidth, &pageHeight);
		gtk_widget_set_size_request(widget, (int)pageWidth, (int)pageHeight);
	}

	poppler_page_render(currentPage, surface);

	drawnPageNumber = currentPageNumber;

	return FALSE;
}

thandle* ListLoad(thandle* ParentWin, char* FileToLoad, int ShowFlags) {
	currentPageNumber = 0;
	drawnPageNumber = 1;

	thandle *gFix;//, *GButton1, *GButton2;
	gFix = gtk_scrolled_window_new(NULL, NULL);
	gtk_container_add(GTK_CONTAINER((GtkWidget*)(ParentWin)), gFix);

	//GButton1 = gtk_button_new_with_label(FileToLoad);
	//gtk_container_add(GTK_CONTAINER(gFix), GButton1);
	//gtk_widget_set_usize(GButton1, 10, 10);
	//gtk_widget_show(GButton1);

	gchar* fileUri = g_filename_to_uri(FileToLoad, NULL, NULL);
	document = poppler_document_new_from_file(fileUri, "", NULL);
	canvas = gtk_drawing_area_new();
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(gFix), canvas);

	g_signal_connect(G_OBJECT(canvas), "expose_event", G_CALLBACK(canvas_onDraw), NULL);

	gtk_widget_show_all(gFix);
	return gFix;
}

void ListCloseWindow(thandle* ListWin) {
	gtk_widget_destroy(ListWin);
};
