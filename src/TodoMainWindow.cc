#include "TodoMainWindow.hpp"
#include <iostream>
#include "TodoUtility.hpp"
#include "Resource.hpp"
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
	cssProvider->load_from_path(TODOMAIN_CSS);
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
	drawerCloser = Glib::RefPtr<ImageButton>(new ImageButton(SAMPLE_SVG));

	drawerCloser->set_halign(Gtk::Align::END);

	// creating drawer opener button
	drawerOpener = Glib::RefPtr<ImageButton>(new ImageButton(SAMPLE_SVG));
	drawerOpener->set_valign(Gtk::Align::START);
	rootContainer->append(*drawerOpener);
	drawerOpener->set_visible(false); // by default drawer is opened and drawerOpener is hidden and drawerCloser is visible

	// creatingg topSideMenuHeader
	topSideMenuHeader = createManaged<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 75);
	topSideMenuHeader->set_vexpand(false);
	topSideMenuHeader->set_valign(Gtk::Align::START);
	topSideMenuHeader->set_size_request(TodoMainWindow::defaultDrawerWidth);

	// adding topSideMenuHeader into first row of sideMenuContainer
	sideMenuContainer->append(*topSideMenuHeader);
	// addding drawerCloser into topSideMenuHeader
	topSideMenuHeader->append(*drawerCloser);
	topSideMenuHeader->set_halign(Gtk::Align::FILL);
	/// creating user profile viewer
	prrofileViewer = createManaged<UButton>(SAMPLE_IMAGE, "Sonu", CHEVRON_DOWN_SVG);

	topSideMenuHeader->prepend(*prrofileViewer);

	prrofileViewer->set_halign(Gtk::Align::START);
	prrofileViewer->set_valign(Gtk::Align::CENTER);

	//  setting rootContainer as child of this window
	set_child(*rootContainer);
}

void TodoMainWindow::addSignals()
{
	drawerOpener->signal_clicked().connect([this]()
																				 {
	//on opening drawer
	this->sideMenuContainer->set_size_request(TodoMainWindow::defaultDrawerWidth);
	this->drawerCloser->set_visible(true);
	this->drawerOpener->set_visible(false); 
	this->prrofileViewer->set_visible(true);
	this->topSideMenuHeader->set_visible(true); });

	drawerCloser->signal_clicked().connect([this]()
																				 {
		//on closing drawer
		
		this->sideMenuContainer->set_size_request(0);
		this->drawerCloser->set_visible(false);
		this->drawerOpener->set_visible(true); 
		this->prrofileViewer->set_visible(false); 
		this->topSideMenuHeader->set_visible(false); });
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