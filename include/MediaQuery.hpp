// MediaQuery.hpp
#pragma once
#include <gtkmm.h>
#include <vector>
#include "TodoUtility.hpp"
#include <iostream>

enum class MediaQueryCallbackSizeType
{
    MIN,
    MAX
};

template <typename T_obj>
struct MediaQueryCallbackStructure
{

    MediaQueryCallbackSizeType type;
    int size;
    void (T_obj::*callback)(int);

    MediaQueryCallbackStructure(MediaQueryCallbackSizeType type, int size, void (T_obj::*callback)(int))
        : type(type), size(size), callback(callback) {}
    ~MediaQueryCallbackStructure()
    {
    }
};

template <typename T_obj>
class MediaQuery
{
public:
    MediaQuery(T_obj *obj) : object(obj) {}
    virtual ~MediaQuery()
    {
        mediaQueryCallbacks.clear();
    }

    void addCallback(MediaQueryCallbackSizeType type, int size, void (T_obj::*callback)(int))
    {
        mediaQueryCallbacks.push_back(Glib::RefPtr<MediaQueryCallbackStructure<T_obj>>(new MediaQueryCallbackStructure<T_obj>(type, size, callback)));
    }

    void addCallback(Glib::RefPtr<MediaQueryCallbackStructure<T_obj>> callbackStructure)
    {
        mediaQueryCallbacks.push_back(callbackStructure);
    }

    void processMediaQuery(int width)
    {

        for (int i = 0; i < mediaQueryCallbacks.size(); i++)
        {
            auto glibRefPtrMQCS = mediaQueryCallbacks[i];
            if (glibRefPtrMQCS->type == MediaQueryCallbackSizeType::MIN && width >= glibRefPtrMQCS->size)
            {
                auto func = glibRefPtrMQCS->callback;
                (object->*func)(width);
                continue;
            }

            if (width <= glibRefPtrMQCS->size)
            {
                auto func = glibRefPtrMQCS->callback;
                (object->*func)(width);
            }
        }
    }

protected:
    std::vector<Glib::RefPtr<MediaQueryCallbackStructure<T_obj>>> mediaQueryCallbacks = std::vector<Glib::RefPtr<MediaQueryCallbackStructure<T_obj>>>();
    T_obj *object;
};
