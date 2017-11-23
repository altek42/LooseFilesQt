#ifndef SETTINGMACRO_H
#define SETTINGMACRO_H

#include <QSettings>

#define SETTING_INIT_H(CLASS) \
public: \
    static CLASS *getInstance(); \
private: \
    QSettings* _settings; \
    static CLASS *_instance;

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

#define CHANGE_GROUP(NAME) \
    _settings->beginGroup(GROUP_NAME);


#define SETTING_PROTOTYPE(TYPE,NAME) \
public: \
    Q_SIGNAL void NAME##Changed(); \
    void set_##NAME(TYPE value); \
    TYPE get_##NAME(); \
private: \
    Q_PROPERTY(TYPE NAME READ get_##NAME WRITE set_##NAME NOTIFY NAME##Changed)

#define SETTING_DEFINITION(CLASS,TYPE,NAME,DEFAULT_VALUE,TO) \
    void CLASS::set_##NAME(TYPE value){ \
        this->_settings->setValue(#NAME,value); \
    } \
    TYPE CLASS::get_##NAME(){ \
        return this->_settings->value(#NAME, DEFAULT_VALUE).TO();\
    }

#define DESTRUCTION() \
    this->_settings->sync();


#endif // SETTINGMACRO_H
