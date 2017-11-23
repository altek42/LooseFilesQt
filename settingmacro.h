/**
MIT License

Copyright (c) 2017 Przemys³aw Gawlas

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
**/

#ifndef SETTINGMACRO_H
#define SETTINGMACRO_H

#include <QSettings>

/* file.h */
#define SETTING_INIT_H(CLASS) \
public: \
    static CLASS *getInstance(); \
private: \
    QSettings* _settings; \
    static CLASS *_instance;

#define SETTING_PROTOTYPE(TYPE,NAME) \
public: \
    Q_SIGNAL void NAME##Changed(); \
    void set_##NAME(TYPE value); \
    TYPE get_##NAME(); \
private: \
    Q_PROPERTY(TYPE NAME READ get_##NAME WRITE set_##NAME NOTIFY NAME##Changed)

/* file.cpp */
#define SETTING_INIT_CPP(CLASS, FILE_NAME, GROUP_NAME) \
    CLASS* CLASS::_instance = nullptr; \
    CLASS* CLASS::getInstance(){ \
        if(_instance == nullptr){ \
            _instance = new CLASS(); \
            _instance->_settings = new QSettings(FILE_NAME,QSettings::IniFormat); \
            _instance->_settings->beginGroup(GROUP_NAME);        \
        } \
        return _instance; \
    }

#define SETTING_DEFINITION(CLASS,TYPE,NAME,DEFAULT_VALUE,TO) \
    void CLASS::set_##NAME(TYPE value){ \
        this->_settings->setValue(#NAME,value); \
    } \
    TYPE CLASS::get_##NAME(){ \
        return this->_settings->value(#NAME, DEFAULT_VALUE).TO();\
    }

#define CHANGE_GROUP(NAME) \
    _settings->beginGroup(GROUP_NAME);

//Use this in destructor
#define DESTRUCTION() \
    this->_settings->sync();


#endif // SETTINGMACRO_H
