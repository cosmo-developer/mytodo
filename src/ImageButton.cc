#include "ImageButton.hpp"

ImageButton::ImageButton(const char *svgFile)
{
	rsvgHandle = rsvg_handle_new_from_file(svgFile, NULL);

	gioIcon = Gio::Icon::create(rsvg_handle_get_base_uri(rsvgHandle));

	image = Glib::RefPtr<Gtk::Image>(new Gtk::Image());

	image->set(gioIcon);

	image->set_icon_size(Gtk::IconSize::LARGE);

	get_style_context()->add_class("image-button");

	image->get_style_context()->add_class("image");

	set_child(*image);
}

ImageButton::~ImageButton()
{
	g_object_unref(rsvgHandle);
}
