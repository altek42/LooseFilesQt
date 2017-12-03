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

#ifndef SINGLETONE_MACRO_H
#define SINGLETONE_MACRO_H

#include <QQmlApplicationEngine>

/* file.h */
#define SINGLETONE_INIT_H(CLASS) \
    public: \
        static CLASS *getInstance(); \
    private: \
        static CLASS *_instance;

#define SINGLETONE_QML_H(CLASS) \
    Q_DISABLE_COPY(CLASS) \
public: \
    void registerQml(const char* uri,const int verMajor, const int verMinor); \
private: \
    static QObject *getQmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);


/* file.cpp */
#define SINGLETONE_INIT_CPP(CLASS) \
    CLASS* CLASS::_instance = nullptr; \
    CLASS* CLASS::getInstance(){ \
        if(_instance == nullptr){ \
            _instance = new CLASS(); \
        } \
        return _instance; \
    }

#define SINGLETONE_QML_CPP(CLASS) \
QObject *CLASS::getQmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine) \
{ \
    Q_UNUSED(engine); \
    Q_UNUSED(scriptEngine); \
    return static_cast<QObject*>(CLASS::getInstance()); \
}\
void CLASS::registerQml(const char* uri,const int verMajor, const int verMinor){\
    qmlRegisterSingletonType<CLASS>(uri,verMajor,verMinor,#CLASS,&getQmlInstance);\
}


#endif // SINGLETONE_MACRO_H
