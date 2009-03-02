/****************************************************************************
** Meta object code from reading C++ file 'sheet.h'
**
** Created: Fri Feb 27 23:29:51 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/sheet.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sheet.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SheetMetal[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_SheetMetal[] = {
    "SheetMetal\0"
};

const QMetaObject SheetMetal::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SheetMetal,
      qt_meta_data_SheetMetal, 0 }
};

const QMetaObject *SheetMetal::metaObject() const
{
    return &staticMetaObject;
}

void *SheetMetal::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SheetMetal))
        return static_cast<void*>(const_cast< SheetMetal*>(this));
    return QWidget::qt_metacast(_clname);
}

int SheetMetal::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_Sheet[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_Sheet[] = {
    "Sheet\0"
};

const QMetaObject Sheet::staticMetaObject = {
    { &QGraphicsScene::staticMetaObject, qt_meta_stringdata_Sheet,
      qt_meta_data_Sheet, 0 }
};

const QMetaObject *Sheet::metaObject() const
{
    return &staticMetaObject;
}

void *Sheet::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Sheet))
        return static_cast<void*>(const_cast< Sheet*>(this));
    return QGraphicsScene::qt_metacast(_clname);
}

int Sheet::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_MainWindow[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      20,   11,   11,   11, 0x08,
      34,   11,   11,   11, 0x08,
      45,   11,   11,   11, 0x08,
      58,   11,   11,   11, 0x08,
      72,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0about()\0readDxfFile()\0"
    "openFile()\0clearScene()\0rotateParts()\0"
    "generatePath()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

const QMetaObject *MainWindow::metaObject() const
{
    return &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: about(); break;
        case 1: readDxfFile(); break;
        case 2: openFile(); break;
        case 3: clearScene(); break;
        case 4: rotateParts(); break;
        case 5: generatePath(); break;
        }
        _id -= 6;
    }
    return _id;
}
static const uint qt_meta_data_Part[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_Part[] = {
    "Part\0"
};

const QMetaObject Part::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Part,
      qt_meta_data_Part, 0 }
};

const QMetaObject *Part::metaObject() const
{
    return &staticMetaObject;
}

void *Part::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Part))
        return static_cast<void*>(const_cast< Part*>(this));
    if (!strcmp(_clname, "QGraphicsItem"))
        return static_cast< QGraphicsItem*>(const_cast< Part*>(this));
    return QObject::qt_metacast(_clname);
}

int Part::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
