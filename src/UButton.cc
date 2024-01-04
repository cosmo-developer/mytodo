#include "UButton.hpp"

UButton::UButton(const char *imageFile, const char *label, const char *trailingIconName)
{
  rsvgHandle = rsvg_handle_new_from_file(trailingIconName, NULL);

  trailingIcon = Gio::Icon::create(rsvg_handle_get_base_uri(rsvgHandle));

  trailingImage = Glib::RefPtr<Gtk::Image>(new Gtk::Image());

  trailingImage->set(trailingIcon);

  trailingImage->set_icon_size(Gtk::IconSize::LARGE);

  get_style_context()->add_class("u-button");

  trailingImage->get_style_context()->add_class("trailing-image");

  headingImage = Glib::RefPtr<Gtk::Image>(new Gtk::Image(imageFile));

  headingImage->set_icon_size(Gtk::IconSize::LARGE);

  headingImage->get_style_context()->add_class("heading-image");

  container = Glib::RefPtr<Gtk::Box>(new Gtk::Box(Gtk::Orientation::HORIZONTAL, 10));

  container->set_homogeneous(true);

  this->label = Glib::RefPtr<Gtk::Label>(new Gtk::Label(label));

  container->append(*headingImage);
  container->append(*(this->label));
  container->append(*trailingImage);

  headingImage->set_valign(Gtk::Align::CENTER);
  this->label->set_valign(Gtk::Align::CENTER);
  trailingImage->set_valign(Gtk::Align::CENTER);

  headingImage->set_halign(Gtk::Align::START);
  this->label->set_halign(Gtk::Align::CENTER);
  trailingImage->set_halign(Gtk::Align::END);

  container->set_halign(Gtk::Align::FILL);

  set_child(*container);
}

UButton::~UButton()
{
  g_object_unref(rsvgHandle);
}
