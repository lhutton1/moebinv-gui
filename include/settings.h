#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>


class settings : public QSettings
{

public:
    settings();
    ~settings();

    settings(const settings &) = delete;
    void operator= (const settings &) = delete;
};

#endif // SETTINGS_H
