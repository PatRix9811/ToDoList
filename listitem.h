#ifndef LISTITEM_H
#define LISTITEM_H

#include <QFrame>
#include <QLabel>
#include <QPushButton>

// List Item class

class ListItem : public QFrame
{
public:
    ListItem(QString details);
    ~ListItem() = default;

private:
    QLabel details;
    QPushButton del;
};

#endif // LISTITEM_H
