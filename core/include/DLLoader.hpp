/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** description
*/

#ifndef OOP_ARCADE_2019_DLLOADER_HPP
#define OOP_ARCADE_2019_DLLOADER_HPP

#include <string>
#include <dlfcn.h>
#include <iostream>

namespace core {
template<typename T>
class DLLoader
{
  private:
    void *_handle;
    bool _loaded;
  public:
    explicit DLLoader (std::string libPath) : _handle(nullptr),
        _loaded(false), _getInstance(nullptr) {
        _handle = dlopen(libPath.c_str(), RTLD_LAZY);
        if (!_handle)
            std::cerr << "Library loading: " << dlerror() << std::endl;
        else {
            _getInstance = (T *(*) ()) dlsym(_handle, "entryPoint");
            if (!_getInstance)
                std::cerr << "Library loading: " << dlerror() << std::endl;
            else
                _loaded = true;
        }
    }

    ~DLLoader () {
        if (_loaded)
            dlclose(_handle);
    }

    bool loaded () { return _loaded; }

    bool switchLibrary (std::string newPath) {
        if (dlclose(_handle) != 0) {
            std::cerr << dlerror() << std::endl;
            return false;
        }
        _loaded = false;
        _handle = dlopen(newPath.c_str(), RTLD_LAZY);
        if (!_handle) {
            std::cerr << dlerror() << std::endl;
            return false;
        }
        _loaded = true;
        return true;
    }

    T *(*_getInstance) ();
};

} // namespace core

#endif //OOP_ARCADE_2019_DLLOADER_HPP
