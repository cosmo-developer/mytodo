#include "TodoMainWindow.hpp"
#include <iostream>
#include "TodoUtility.hpp"
TodoMainWindow::TodoMainWindow()
{

	// setting title for this window to My Todo
	set_title(TodoMainWindow::tailer);
	// setting defaultWidth and defaultHeight to this window
	set_default_size(TodoMainWindow::defaultWidth, TodoMainWindow::defaultHeight);

	configureMediaQuery();

	property_default_width().signal_changed().connect(sigc::mem_fun(*this, &TodoMainWindow::onWindowResize));
	property_maximized().signal_changed().connect(sigc::mem_fun(*this, &TodoMainWindow::onWindowResize));

	loadCSS();
	createComponents();
	addSignals();
}

TodoMainWindow::~TodoMainWindow()
{
}

void TodoMainWindow::onWindowResize()
{
	int width, height;
	get_default_size(width, height);
	if (width == -1)
		return;

	mediaQuery->processMediaQuery(width);
}

void TodoMainWindow::loadCSS()
{
	cssProvider = Gtk::CssProvider::create();
	// loading from path todomain.css
	cssProvider->load_from_path("/usr/share/mytodo/styles/todomain.css");
	// adding css for whole application
	Gtk::StyleContext::add_provider_for_display(Gdk::Display::get_default(), cssProvider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}

void TodoMainWindow::createComponents()
{
	// root container
	rootContainer = Glib::RefPtr<Gtk::Box>(new Gtk::Box(Gtk::Orientation::HORIZONTAL));
	// setting css class
	rootContainer->get_style_context()->add_class("root-container");

	// side menu container
	sideMenuContainer = Glib::RefPtr<Gtk::Box>(new Gtk::Box(Gtk::Orientation::VERTICAL));
	// setting css class
	sideMenuContainer->get_style_context()->add_class("side-menu-container");
	// setting size of sideMenuContainer
	sideMenuContainer->set_size_request(TodoMainWindow::defaultDrawerWidth);

	// adding sideMeuContainer to rootContainer
	rootContainer->append(*sideMenuContainer);

	// creating drawer closer button
	drawerCloser = Glib::RefPtr<ImageButton>(new ImageButton("/usr/share/mytodo/icons/sample.svg"));
	sideMenuContainer->append(*drawerCloser);
	drawerCloser->set_valign(Gtk::Align::START);
	drawerCloser->set_halign(Gtk::Align::END);

	// creating drawer opener button
	drawerOpener = Glib::RefPtr<ImageButton>(new ImageButton("/usr/share/mytodo/icons/sample.svg"));
	drawerOpener->set_valign(Gtk::Align::START);
	rootContainer->append(*drawerOpener);
	drawerOpener->set_visible(false); // by default drawer is opened and drawerOpener is hidden and drawerCloser is visible

	// setting rootContainer as child of this window
	set_child(*rootContainer);
}

void TodoMainWindow::addSignals()
{
	drawerOpener->signal_clicked().connect([this]()
																				 {
	//on opening drawer
	this->sideMenuContainer->set_size_request(TodoMainWindow::defaultDrawerWidth);
	this->drawerCloser->set_visible(true);
	this->drawerOpener->set_visible(false); });

	drawerCloser->signal_clicked().connect([this]()
																				 {
		//on closing drawer
		
		this->sideMenuContainer->set_size_request(0);
		this->drawerCloser->set_visible(false);
		this->drawerOpener->set_visible(true); });
}

void TodoMainWindow::configureMediaQuery()
{
	mediaQuery = createManaged<MediaQuery<TodoMainWindow>>(this);
	mediaQuery->addCallback(MediaQueryCallbackSizeType::MAX, 400, &TodoMainWindow::max400Processor);
	// mediaQuery->addCallback(MediaQueryCallbackSizeType::MAX,600mm)
}

int TodoMainWindow::defaultWidth = 600;
int TodoMainWindow::defaultHeight = 500;
int TodoMainWindow::defaultDrawerWidth = 250;
std::string TodoMainWindow::tailer = "My Todo";