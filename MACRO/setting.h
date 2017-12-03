/**
MIT License

Copyright (c) 2017 Przemysław Gawlas

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

#ifndef SETTING_MACRO_H
#define SETTING_MACRO_H

#include <QSettings>
#include "singletone.h"

/* file.h */
#define SETTING_INIT_H(CLASS) \
    SINGLETONE_INIT_H(CLASS) \
    SINGLETONE_QML_H(CLASS) \
private: \
    QSettings* _settings; \
    void __init();

#define SETTING_PROTOTYPE(TYPE,NAME) \
public: \
    Q_SIGNAL void NAME##Changed(); \
    void set_##NAME(TYPE value); \
    TYPE get_##NAME(); \
private: \
    Q_PROPERTY(TYPE NAME READ get_##NAME WRITE set_##NAME NOTIFY NAME##Changed)

/* file.cpp */
#define SETTING_INIT_CPP(CLASS, FILE_NAME, GROUP_NAME) \
    SINGLETONE_INIT_CPP(CLASS) \
    SINGLETONE_QML_CPP(CLASS) \
    void CLASS::__init(){\
    this->_settings = new QSettings(FILE_NAME,QSettings::IniFormat); \
    this->_settings->beginGroup(GROUP_NAME);\
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

//Use this in constructor
#define SETTING_CTOR() \
    this->__init();

//Use this in destructor
#define SETTING_DTOR() \
    this->_settings->sync();


#endif // SETTING_MACRO_H
