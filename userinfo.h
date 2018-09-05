#ifndef USERINFO_H
#define USERINFO_H

#include<QString>


class UserInfo
{
public:
    UserInfo()
    {
        uid = "conglanjun";
        pwd = "012502clj";
    }

public:
    QString uid;
    QString pwd;
    QString token;
};

#endif // USERINFO_H
