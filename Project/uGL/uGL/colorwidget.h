#ifndef COLORWIDGET_H
#define COLORWIDGET_H

#include <%BASECLASS%>
#include "%UI_HDR%"

%NAMESPACE_BEGIN%class %CLASS% : public %BASECLASS%
{
    Q_OBJECT

public:
    %CLASS%(QWidget *parent = 0);
    ~%CLASS%();

private:
    Ui::%CLASS% ui;
};

%NAMESPACE_END%#endif // COLORWIDGET_H
