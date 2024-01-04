#pragma once
#include <gtkmm.h>
#include <librsvg/rsvg.h>
class UButton : public Gtk::Button
{
private:
  /* data */
  RsvgHandle *rsvgHandle;
  Glib::RefPtr<Gio::Icon> trailingIcon;
  Glib::RefPtr<Gtk::Image> trailingImage;
  Glib::RefPtr<Gtk::Image> headingImage;
  Glib::RefPtr<Gtk::Box> container;
  Glib::RefPtr<Gtk::Label> label;

public:
  UButton(const char *headImageFile, const char *label, const char *trailingIconFileName);
  ~UButton();
};
