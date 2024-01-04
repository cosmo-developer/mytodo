#include <gtkmm.h>
#include "TodoMainWindow.hpp"

int main(int argc,char** argv){
	g_setenv ("GTK_CSD", "0", FALSE);
	Glib::RefPtr<Gtk::Application> app=Gtk::Application::create("org.cosmo.mytodo");
	return app->make_window_and_run<TodoMainWindow>(argc,argv);
}
