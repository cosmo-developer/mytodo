#pragma once
#include <gtkmm.h>

template<typename T,typename ...Args>
Glib::RefPtr<T> createManaged(Args... args){
	return Glib::RefPtr<T>(new T(args...));
}
