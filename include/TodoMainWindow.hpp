#pragma once
#include <gtkmm.h>
#include <string>
#include "ImageButton.hpp"
#include "MediaQuery.hpp"

class TodoMainWindow:public Gtk::Window{
public:
	static int defaultWidth;
	static int defaultHeight;
	static int defaultDrawerWidth;
	static std::string tailer;
	
	TodoMainWindow();
	virtual ~TodoMainWindow();
protected:
	void onWindowResize();
	void onWindowFullScreen();
	void onWindowMinimizeed();
	
	//max 400 mediaquery processor
	void max400Processor(int width);
	
private:
	//css-class: root-container
	Glib::RefPtr<Gtk::Box> rootContainer;
	//css-class: side-menu-container
	Glib::RefPtr<Gtk::Box> sideMenuContainer;
	//cssprovider
	Glib::RefPtr<Gtk::CssProvider> cssProvider;
	//on Home drawer opener button
	Glib::RefPtr<ImageButton> drawerOpener;
	//drawer closer button
	Glib::RefPtr<ImageButton> drawerCloser;
	//defining media query processor
	Glib::RefPtr<MediaQuery<TodoMainWindow>> mediaQuery;
	
private:
	void loadCSS();
	void createComponents();
	void addSignals();
	void configureMediaQuery();
};
