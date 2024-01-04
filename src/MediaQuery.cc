#include "MediaQuery.hpp"
#include "TodoUtility.hpp"

MediaQuery::MediaQuery(){}

MediaQuery::~MediaQuery(){
	mediaQueryCallbacks.clear();
}

template<typename T_obj>
void MediaQuery<T_obj>::addCallback(MediaQueryCallbackSizeType type,int size,void(T_obj::*callback)(int)){	
	//creating mediaquerycallbackstrucutre instance with constructure type and callback and adding it to mediQueryCallback vector
	mediaQueryCallbacks.push_back(createManaged<MediaQueryCallbackStructure>(type,size,callback));	
}
template<typename T_obj>
void MediaQuery<T_obj>::addCallback(Glib::RefPtr<MediaQueryCallbackStructure<T_obj>> callbackStructure){
	//adding callBackStructure from parameter to mediaQueryCallback vector
	mediaQueryCallbacks.push_back(callbackStructure);
}

template<typename T_obj>
void MediaQuery<T_obj>::processMediaQuery(int width){
	//iterating all callbacks and checking min and max type to determine when to call them
	for (auto glibRefPtrMQCS:mediaQueryCallbacks){
		//for min type callbacks 
		//if sizeofscreen(width parameter) >= givenSize(size defined in MQCS structure) then invoke Callback
		if (glibRefPtrMQCS->type == MediaQueryCallbackSizeType::MIN && width>=glibRefPtrMQCS->size){
			glibRefPtrMQCS->callback(width);
			continue;			
		}
		//as we know from above min is checked and continued so in bottom only max can come
		//so only we need to check size not type because size is user defined
		
		if (width <= glibRefPtrMQCS->size){
			glibRefPtrMQCS->callback(width);
		}
	}
}
