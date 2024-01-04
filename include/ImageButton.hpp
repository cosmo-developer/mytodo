#pragma once
#include <gtkmm.h>
#include <librsvg/rsvg.h>
class ImageButton:public Gtk::Button{
public:
	ImageButton(const char* imageFileSvg);
	virtual ~ImageButton();
private:
	RsvgHandle* rsvgHandle;
	Glib::RefPtr<Gio::Icon> gioIcon;
	Glib::RefPtr<Gtk::Image> image;
	
};
