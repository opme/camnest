/****************************************************************************
** Meta object code from reading C++ file 'sheet.h'
**
** Created: Tue Apr 7 14:10:06 2009
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
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      19,    7,    6,    6, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_Sheet[] = {
    "Sheet\0\0currentLoop\0progressionDone(int)\0"
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
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: progressionDone((*reinterpret_cast< const int(*)>(_a[1]))); break;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void Sheet::progressionDone(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_SettingsDialog[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x0a,
      30,   15,   15,   15, 0x0a,
      46,   15,   15,   15, 0x0a,
      57,   15,   15,   15, 0x0a,
      64,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SettingsDialog[] = {
    "SettingsDialog\0\0setPenColor()\0"
    "setBrushColor()\0setInner()\0save()\0"
    "loadSettings()\0"
};

const QMetaObject SettingsDialog::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SettingsDialog,
      qt_meta_data_SettingsDialog, 0 }
};

const QMetaObject *SettingsDialog::metaObject() const
{
    return &staticMetaObject;
}

void *SettingsDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SettingsDialog))
        return static_cast<void*>(const_cast< SettingsDialog*>(this));
    return QWidget::qt_metacast(_clname);
}

int SettingsDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setPenColor(); break;
        case 1: setBrushColor(); break;
        case 2: setInner(); break;
        case 3: save(); break;
        case 4: loadSettings(); break;
        }
        _id -= 5;
    }
    return _id;
}
static const uint qt_meta_data_PartsListModel[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_PartsListModel[] = {
    "PartsListModel\0"
};

const QMetaObject PartsListModel::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_PartsListModel,
      qt_meta_data_PartsListModel, 0 }
};

const QMetaObject *PartsListModel::metaObject() const
{
    return &staticMetaObject;
}

void *PartsListModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PartsListModel))
        return static_cast<void*>(const_cast< PartsListModel*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int PartsListModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_MainWindow[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      27,   11,   11,   11, 0x0a,
      50,   38,   11,   11, 0x0a,
      71,   11,   11,   11, 0x08,
      85,   79,   11,   11, 0x08,
     116,  111,   11,   11, 0x08,
     134,   11,   11,   11, 0x08,
     152,   79,   11,   11, 0x08,
     174,   11,   11,   11, 0x08,
     193,   11,  188,   11, 0x08,
     205,   11,   11,   11, 0x08,
     224,  218,   11,   11, 0x08,
     241,   11,   11,   11, 0x28,
     255,   11,   11,   11, 0x08,
     270,   11,   11,   11, 0x08,
     283,   11,   11,   11, 0x08,
     293,   11,   11,   11, 0x08,
     304,   11,   11,   11, 0x08,
     318,   11,   11,   11, 0x08,
     327,   11,  188,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0partInserted()\0openFile()\0"
    "currentLoop\0progressionDone(int)\0"
    "about()\0index\0openSelected(QModelIndex)\0"
    "desc\0descStep(QString)\0showPreviewDock()\0"
    "showPart(QModelIndex)\0setRotAngle()\0"
    "bool\0saveGCode()\0clearScene()\0angle\0"
    "rotateParts(int)\0rotateParts()\0"
    "showSettings()\0stepByStep()\0zoomFit()\0"
    "optimize()\0deleteItems()\0insert()\0"
    "confirmAction()\0"
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
        case 0: partInserted(); break;
        case 1: openFile(); break;
        case 2: progressionDone((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: about(); break;
        case 4: openSelected((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 5: descStep((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: showPreviewDock(); break;
        case 7: showPart((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 8: setRotAngle(); break;
        case 9: { bool _r = saveGCode();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 10: clearScene(); break;
        case 11: rotateParts((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: rotateParts(); break;
        case 13: showSettings(); break;
        case 14: stepByStep(); break;
        case 15: zoomFit(); break;
        case 16: optimize(); break;
        case 17: deleteItems(); break;
        case 18: insert(); break;
        case 19: { bool _r = confirmAction();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        }
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::partInserted()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
