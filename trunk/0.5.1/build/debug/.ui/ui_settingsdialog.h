/********************************************************************************
** Form generated from reading ui file 'settingsdialog.ui'
**
** Created: Tue Apr 7 13:36:47 2009
**      by: Qt User Interface Compiler version 4.4.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFontComboBox>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStackedWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialog
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *Containerhor;
    QListWidget *pageList;
    QStackedWidget *pageStack;
    QWidget *page;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_8;
    QSpinBox *spinBox;
    QLabel *label_9;
    QSpinBox *spinBox_2;
    QLabel *label_10;
    QSpinBox *spinBox_3;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_6;
    QDoubleSpinBox *doubleSpinBox;
    QCheckBox *checkBox;
    QWidget *horizontalLayoutWidget_5;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_11;
    QSpacerItem *horizontalSpacer_5;
    QToolButton *toolButton;
    QWidget *horizontalLayoutWidget_6;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_12;
    QTextEdit *textEdit;
    QWidget *horizontalLayoutWidget_7;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_13;
    QTextEdit *textEdit_2;
    QWidget *page_4;
    QWidget *horizontalLayoutWidget_11;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_18;
    QSpacerItem *horizontalSpacer_9;
    QCheckBox *checkBox_2;
    QCheckBox *InnerTextCHK_2;
    QWidget *layoutWidget_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_6;
    QFontComboBox *fontCB;
    QLabel *label_7;
    QSpinBox *fontSizeSpin;
    QWidget *layoutWidget_3;
    QHBoxLayout *horizontalLayout_16;
    QLabel *penLB_3;
    QSpacerItem *horizontSp;
    QPushButton *penPB_5;
    QWidget *page_5;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label;
    QSpacerItem *horizontalSpa;
    QDoubleSpinBox *leadDistSB;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_17;
    QSpacerItem *horizontalSpac;
    QDoubleSpinBox *leadRadiusSB;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_8;
    QSpinBox *leadAngleSB;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_15;
    QSpacerItem *horizontalSpacer_7;
    QDoubleSpinBox *minLeadDistSB;
    QCheckBox *checkBox_3;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label_23;
    QSpacerItem *hozontalSpacer_6;
    QPushButton *penPB_4;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_22;
    QSpacerItem *horizoalSpacer_6;
    QPushButton *penPB_3;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_14;
    QSpacerItem *horizontalSpac_6;
    QPushButton *penPB_2;
    QWidget *page_6;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *penLB;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *penPB;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_16;
    QSpacerItem *horizontalSpacer_10;
    QSpinBox *spinBox_4;
    QCheckBox *InnerColorCHK;
    QHBoxLayout *horizontalLayout_2;
    QLabel *brushLB;
    QSpacerItem *horizontalSpacer;
    QPushButton *brushPB;
    QFrame *line;
    QLabel *label_24;
    QCheckBox *InnerTextCHK;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *texturePB;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_19;
    QSpacerItem *horizontalSpacer_11;
    QLabel *label_20;
    QSlider *horizontalSlider;
    QLabel *label_21;
    QCheckBox *checkBox_4;
    QWidget *page_7;
    QLabel *label_25;
    QCheckBox *checkBox_5;
    QCheckBox *checkBox_6;
    QSpinBox *spinBox_5;
    QLabel *label_26;
    QWidget *page_2;
    QCheckBox *checkBox_7;
    QCheckBox *checkBox_8;
    QCheckBox *checkBox_9;
    QCheckBox *checkBox_10;
    QWidget *layoutWidget_2;
    QHBoxLayout *_2;
    QSpacerItem *spacerbas;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QWidget *SettingsDialog)
    {
    if (SettingsDialog->objectName().isEmpty())
        SettingsDialog->setObjectName(QString::fromUtf8("SettingsDialog"));
    SettingsDialog->setWindowModality(Qt::ApplicationModal);
    SettingsDialog->setEnabled(true);
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(SettingsDialog->sizePolicy().hasHeightForWidth());
    SettingsDialog->setSizePolicy(sizePolicy);
    SettingsDialog->setMinimumSize(QSize(620, 450));
    SettingsDialog->setMaximumSize(QSize(1000, 450));
    layoutWidget = new QWidget(SettingsDialog);
    layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
    layoutWidget->setGeometry(QRect(0, 0, 681, 411));
    Containerhor = new QHBoxLayout(layoutWidget);
    Containerhor->setObjectName(QString::fromUtf8("Containerhor"));
    Containerhor->setContentsMargins(0, 0, 0, 0);
    pageList = new QListWidget(layoutWidget);
    QIcon icon;
    icon.addPixmap(QPixmap(QString::fromUtf8("../../../../sources/lastfm/Last.fm/tags/1.4.0.54514/data/icon.png")), QIcon::Normal, QIcon::Off);
    QListWidgetItem *__listItem = new QListWidgetItem(pageList);
    __listItem->setIcon(icon);
    new QListWidgetItem(pageList);
    new QListWidgetItem(pageList);
    QIcon icon1;
    icon1.addPixmap(QPixmap(QString::fromUtf8("../../../../sources/lastfm/Last.fm/tags/1.4.0.54514/res/app_55.bmp")), QIcon::Normal, QIcon::Off);
    QListWidgetItem *__listItem1 = new QListWidgetItem(pageList);
    __listItem1->setIcon(icon1);
    QIcon icon2;
    icon2.addPixmap(QPixmap(QString::fromUtf8("../../../../sources/lastfm/Last.fm/tags/1.4.0.54514/res/qrc/SideBarNowPlaying.png")), QIcon::Normal, QIcon::Off);
    QListWidgetItem *__listItem2 = new QListWidgetItem(pageList);
    __listItem2->setIcon(icon2);
    QIcon icon3;
    icon3.addPixmap(QPixmap(QString::fromUtf8(":/action/love.png")), QIcon::Normal, QIcon::Off);
    QListWidgetItem *__listItem3 = new QListWidgetItem(pageList);
    __listItem3->setIcon(icon3);
    new QListWidgetItem(pageList);
    new QListWidgetItem(pageList);
    pageList->setObjectName(QString::fromUtf8("pageList"));
    QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(pageList->sizePolicy().hasHeightForWidth());
    pageList->setSizePolicy(sizePolicy1);
    pageList->setMinimumSize(QSize(145, 0));
    pageList->setMaximumSize(QSize(145, 16777215));
    pageList->setFocusPolicy(Qt::NoFocus);
    pageList->setLayoutDirection(Qt::LeftToRight);
    pageList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    pageList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    pageList->setSelectionMode(QAbstractItemView::SingleSelection);
    pageList->setSelectionBehavior(QAbstractItemView::SelectRows);
    pageList->setIconSize(QSize(32, 32));
    pageList->setMovement(QListView::Static);
    pageList->setFlow(QListView::TopToBottom);
    pageList->setProperty("isWrapping", QVariant(false));
    pageList->setSpacing(0);
    pageList->setGridSize(QSize(120, 36));
    pageList->setViewMode(QListView::ListMode);
    pageList->setUniformItemSizes(true);

    Containerhor->addWidget(pageList);

    pageStack = new QStackedWidget(layoutWidget);
    pageStack->setObjectName(QString::fromUtf8("pageStack"));
    page = new QWidget();
    page->setObjectName(QString::fromUtf8("page"));
    horizontalLayoutWidget_3 = new QWidget(page);
    horizontalLayoutWidget_3->setObjectName(QString::fromUtf8("horizontalLayoutWidget_3"));
    horizontalLayoutWidget_3->setGeometry(QRect(10, 10, 351, 41));
    horizontalLayout_5 = new QHBoxLayout(horizontalLayoutWidget_3);
    horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
    horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
    label_3 = new QLabel(horizontalLayoutWidget_3);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    horizontalLayout_5->addWidget(label_3);

    horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_5->addItem(horizontalSpacer_4);

    label_8 = new QLabel(horizontalLayoutWidget_3);
    label_8->setObjectName(QString::fromUtf8("label_8"));

    horizontalLayout_5->addWidget(label_8);

    spinBox = new QSpinBox(horizontalLayoutWidget_3);
    spinBox->setObjectName(QString::fromUtf8("spinBox"));

    horizontalLayout_5->addWidget(spinBox);

    label_9 = new QLabel(horizontalLayoutWidget_3);
    label_9->setObjectName(QString::fromUtf8("label_9"));

    horizontalLayout_5->addWidget(label_9);

    spinBox_2 = new QSpinBox(horizontalLayoutWidget_3);
    spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));

    horizontalLayout_5->addWidget(spinBox_2);

    label_10 = new QLabel(horizontalLayoutWidget_3);
    label_10->setObjectName(QString::fromUtf8("label_10"));

    horizontalLayout_5->addWidget(label_10);

    spinBox_3 = new QSpinBox(horizontalLayoutWidget_3);
    spinBox_3->setObjectName(QString::fromUtf8("spinBox_3"));

    horizontalLayout_5->addWidget(spinBox_3);

    horizontalLayoutWidget_4 = new QWidget(page);
    horizontalLayoutWidget_4->setObjectName(QString::fromUtf8("horizontalLayoutWidget_4"));
    horizontalLayoutWidget_4->setGeometry(QRect(10, 60, 160, 31));
    horizontalLayout_6 = new QHBoxLayout(horizontalLayoutWidget_4);
    horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
    horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
    label_4 = new QLabel(horizontalLayoutWidget_4);
    label_4->setObjectName(QString::fromUtf8("label_4"));

    horizontalLayout_6->addWidget(label_4);

    horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_6->addItem(horizontalSpacer_6);

    doubleSpinBox = new QDoubleSpinBox(horizontalLayoutWidget_4);
    doubleSpinBox->setObjectName(QString::fromUtf8("doubleSpinBox"));

    horizontalLayout_6->addWidget(doubleSpinBox);

    checkBox = new QCheckBox(page);
    checkBox->setObjectName(QString::fromUtf8("checkBox"));
    checkBox->setGeometry(QRect(10, 100, 221, 23));
    horizontalLayoutWidget_5 = new QWidget(page);
    horizontalLayoutWidget_5->setObjectName(QString::fromUtf8("horizontalLayoutWidget_5"));
    horizontalLayoutWidget_5->setGeometry(QRect(10, 130, 261, 41));
    horizontalLayout_7 = new QHBoxLayout(horizontalLayoutWidget_5);
    horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
    horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
    label_11 = new QLabel(horizontalLayoutWidget_5);
    label_11->setObjectName(QString::fromUtf8("label_11"));

    horizontalLayout_7->addWidget(label_11);

    horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_7->addItem(horizontalSpacer_5);

    toolButton = new QToolButton(horizontalLayoutWidget_5);
    toolButton->setObjectName(QString::fromUtf8("toolButton"));

    horizontalLayout_7->addWidget(toolButton);

    horizontalLayoutWidget_6 = new QWidget(page);
    horizontalLayoutWidget_6->setObjectName(QString::fromUtf8("horizontalLayoutWidget_6"));
    horizontalLayoutWidget_6->setGeometry(QRect(10, 190, 421, 91));
    horizontalLayout_8 = new QHBoxLayout(horizontalLayoutWidget_6);
    horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
    horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
    label_12 = new QLabel(horizontalLayoutWidget_6);
    label_12->setObjectName(QString::fromUtf8("label_12"));

    horizontalLayout_8->addWidget(label_12);

    textEdit = new QTextEdit(horizontalLayoutWidget_6);
    textEdit->setObjectName(QString::fromUtf8("textEdit"));

    horizontalLayout_8->addWidget(textEdit);

    horizontalLayoutWidget_7 = new QWidget(page);
    horizontalLayoutWidget_7->setObjectName(QString::fromUtf8("horizontalLayoutWidget_7"));
    horizontalLayoutWidget_7->setGeometry(QRect(10, 290, 421, 91));
    horizontalLayout_9 = new QHBoxLayout(horizontalLayoutWidget_7);
    horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
    horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
    label_13 = new QLabel(horizontalLayoutWidget_7);
    label_13->setObjectName(QString::fromUtf8("label_13"));

    horizontalLayout_9->addWidget(label_13);

    textEdit_2 = new QTextEdit(horizontalLayoutWidget_7);
    textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));

    horizontalLayout_9->addWidget(textEdit_2);

    pageStack->addWidget(page);
    page_4 = new QWidget();
    page_4->setObjectName(QString::fromUtf8("page_4"));
    horizontalLayoutWidget_11 = new QWidget(page_4);
    horizontalLayoutWidget_11->setObjectName(QString::fromUtf8("horizontalLayoutWidget_11"));
    horizontalLayoutWidget_11->setGeometry(QRect(20, 30, 391, 31));
    horizontalLayout_18 = new QHBoxLayout(horizontalLayoutWidget_11);
    horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
    horizontalLayout_18->setContentsMargins(0, 0, 0, 0);
    label_18 = new QLabel(horizontalLayoutWidget_11);
    label_18->setObjectName(QString::fromUtf8("label_18"));

    horizontalLayout_18->addWidget(label_18);

    horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_18->addItem(horizontalSpacer_9);

    checkBox_2 = new QCheckBox(horizontalLayoutWidget_11);
    checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

    horizontalLayout_18->addWidget(checkBox_2);

    InnerTextCHK_2 = new QCheckBox(page_4);
    InnerTextCHK_2->setObjectName(QString::fromUtf8("InnerTextCHK_2"));
    InnerTextCHK_2->setGeometry(QRect(10, 90, 449, 23));
    InnerTextCHK_2->setChecked(true);
    layoutWidget_4 = new QWidget(page_4);
    layoutWidget_4->setObjectName(QString::fromUtf8("layoutWidget_4"));
    layoutWidget_4->setGeometry(QRect(80, 140, 350, 31));
    horizontalLayout_4 = new QHBoxLayout(layoutWidget_4);
    horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
    horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
    label_6 = new QLabel(layoutWidget_4);
    label_6->setObjectName(QString::fromUtf8("label_6"));

    horizontalLayout_4->addWidget(label_6);

    fontCB = new QFontComboBox(layoutWidget_4);
    fontCB->setObjectName(QString::fromUtf8("fontCB"));

    horizontalLayout_4->addWidget(fontCB);

    label_7 = new QLabel(layoutWidget_4);
    label_7->setObjectName(QString::fromUtf8("label_7"));

    horizontalLayout_4->addWidget(label_7);

    fontSizeSpin = new QSpinBox(layoutWidget_4);
    fontSizeSpin->setObjectName(QString::fromUtf8("fontSizeSpin"));
    fontSizeSpin->setMinimum(2);
    fontSizeSpin->setMaximum(70);

    horizontalLayout_4->addWidget(fontSizeSpin);

    layoutWidget_3 = new QWidget(page_4);
    layoutWidget_3->setObjectName(QString::fromUtf8("layoutWidget_3"));
    layoutWidget_3->setGeometry(QRect(20, 190, 449, 42));
    horizontalLayout_16 = new QHBoxLayout(layoutWidget_3);
    horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
    horizontalLayout_16->setContentsMargins(0, 0, 0, 0);
    penLB_3 = new QLabel(layoutWidget_3);
    penLB_3->setObjectName(QString::fromUtf8("penLB_3"));
    penLB_3->setMinimumSize(QSize(84, 0));

    horizontalLayout_16->addWidget(penLB_3);

    horizontSp = new QSpacerItem(200, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

    horizontalLayout_16->addItem(horizontSp);

    penPB_5 = new QPushButton(layoutWidget_3);
    penPB_5->setObjectName(QString::fromUtf8("penPB_5"));

    horizontalLayout_16->addWidget(penPB_5);

    pageStack->addWidget(page_4);
    page_5 = new QWidget();
    page_5->setObjectName(QString::fromUtf8("page_5"));
    verticalLayoutWidget_2 = new QWidget(page_5);
    verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
    verticalLayoutWidget_2->setGeometry(QRect(10, 20, 461, 351));
    verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_2);
    verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
    verticalLayout_3->setContentsMargins(0, 0, 0, 0);
    horizontalLayout_11 = new QHBoxLayout();
    horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
    label = new QLabel(verticalLayoutWidget_2);
    label->setObjectName(QString::fromUtf8("label"));

    horizontalLayout_11->addWidget(label);

    horizontalSpa = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_11->addItem(horizontalSpa);

    leadDistSB = new QDoubleSpinBox(verticalLayoutWidget_2);
    leadDistSB->setObjectName(QString::fromUtf8("leadDistSB"));

    horizontalLayout_11->addWidget(leadDistSB);


    verticalLayout_3->addLayout(horizontalLayout_11);

    horizontalLayout_17 = new QHBoxLayout();
    horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
    label_17 = new QLabel(verticalLayoutWidget_2);
    label_17->setObjectName(QString::fromUtf8("label_17"));

    horizontalLayout_17->addWidget(label_17);

    horizontalSpac = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_17->addItem(horizontalSpac);

    leadRadiusSB = new QDoubleSpinBox(verticalLayoutWidget_2);
    leadRadiusSB->setObjectName(QString::fromUtf8("leadRadiusSB"));

    horizontalLayout_17->addWidget(leadRadiusSB);


    verticalLayout_3->addLayout(horizontalLayout_17);

    horizontalLayout_12 = new QHBoxLayout();
    horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
    label_2 = new QLabel(verticalLayoutWidget_2);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    horizontalLayout_12->addWidget(label_2);

    horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_12->addItem(horizontalSpacer_8);

    leadAngleSB = new QSpinBox(verticalLayoutWidget_2);
    leadAngleSB->setObjectName(QString::fromUtf8("leadAngleSB"));

    horizontalLayout_12->addWidget(leadAngleSB);


    verticalLayout_3->addLayout(horizontalLayout_12);

    horizontalLayout_13 = new QHBoxLayout();
    horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
    label_15 = new QLabel(verticalLayoutWidget_2);
    label_15->setObjectName(QString::fromUtf8("label_15"));

    horizontalLayout_13->addWidget(label_15);

    horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_13->addItem(horizontalSpacer_7);

    minLeadDistSB = new QDoubleSpinBox(verticalLayoutWidget_2);
    minLeadDistSB->setObjectName(QString::fromUtf8("minLeadDistSB"));

    horizontalLayout_13->addWidget(minLeadDistSB);


    verticalLayout_3->addLayout(horizontalLayout_13);

    checkBox_3 = new QCheckBox(verticalLayoutWidget_2);
    checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));
    checkBox_3->setChecked(true);

    verticalLayout_3->addWidget(checkBox_3);

    horizontalLayout_20 = new QHBoxLayout();
    horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
    label_23 = new QLabel(verticalLayoutWidget_2);
    label_23->setObjectName(QString::fromUtf8("label_23"));

    horizontalLayout_20->addWidget(label_23);

    hozontalSpacer_6 = new QSpacerItem(100, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_20->addItem(hozontalSpacer_6);

    penPB_4 = new QPushButton(verticalLayoutWidget_2);
    penPB_4->setObjectName(QString::fromUtf8("penPB_4"));

    horizontalLayout_20->addWidget(penPB_4);


    verticalLayout_3->addLayout(horizontalLayout_20);

    horizontalLayout_19 = new QHBoxLayout();
    horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
    label_22 = new QLabel(verticalLayoutWidget_2);
    label_22->setObjectName(QString::fromUtf8("label_22"));

    horizontalLayout_19->addWidget(label_22);

    horizoalSpacer_6 = new QSpacerItem(100, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_19->addItem(horizoalSpacer_6);

    penPB_3 = new QPushButton(verticalLayoutWidget_2);
    penPB_3->setObjectName(QString::fromUtf8("penPB_3"));

    horizontalLayout_19->addWidget(penPB_3);


    verticalLayout_3->addLayout(horizontalLayout_19);

    horizontalLayout_10 = new QHBoxLayout();
    horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
    label_14 = new QLabel(verticalLayoutWidget_2);
    label_14->setObjectName(QString::fromUtf8("label_14"));

    horizontalLayout_10->addWidget(label_14);

    horizontalSpac_6 = new QSpacerItem(100, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_10->addItem(horizontalSpac_6);

    penPB_2 = new QPushButton(verticalLayoutWidget_2);
    penPB_2->setObjectName(QString::fromUtf8("penPB_2"));

    horizontalLayout_10->addWidget(penPB_2);


    verticalLayout_3->addLayout(horizontalLayout_10);

    pageStack->addWidget(page_5);
    page_6 = new QWidget();
    page_6->setObjectName(QString::fromUtf8("page_6"));
    verticalLayoutWidget = new QWidget(page_6);
    verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
    verticalLayoutWidget->setGeometry(QRect(20, 40, 471, 311));
    verticalLayout = new QVBoxLayout(verticalLayoutWidget);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    penLB = new QLabel(verticalLayoutWidget);
    penLB->setObjectName(QString::fromUtf8("penLB"));

    horizontalLayout->addWidget(penLB);

    horizontalSpacer_2 = new QSpacerItem(100, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer_2);

    penPB = new QPushButton(verticalLayoutWidget);
    penPB->setObjectName(QString::fromUtf8("penPB"));

    horizontalLayout->addWidget(penPB);


    verticalLayout->addLayout(horizontalLayout);

    horizontalLayout_14 = new QHBoxLayout();
    horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
    label_16 = new QLabel(verticalLayoutWidget);
    label_16->setObjectName(QString::fromUtf8("label_16"));

    horizontalLayout_14->addWidget(label_16);

    horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_14->addItem(horizontalSpacer_10);

    spinBox_4 = new QSpinBox(verticalLayoutWidget);
    spinBox_4->setObjectName(QString::fromUtf8("spinBox_4"));

    horizontalLayout_14->addWidget(spinBox_4);


    verticalLayout->addLayout(horizontalLayout_14);

    InnerColorCHK = new QCheckBox(verticalLayoutWidget);
    InnerColorCHK->setObjectName(QString::fromUtf8("InnerColorCHK"));

    verticalLayout->addWidget(InnerColorCHK);

    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    brushLB = new QLabel(verticalLayoutWidget);
    brushLB->setObjectName(QString::fromUtf8("brushLB"));

    horizontalLayout_2->addWidget(brushLB);

    horizontalSpacer = new QSpacerItem(100, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_2->addItem(horizontalSpacer);

    brushPB = new QPushButton(verticalLayoutWidget);
    brushPB->setObjectName(QString::fromUtf8("brushPB"));
    brushPB->setEnabled(false);
    QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(brushPB->sizePolicy().hasHeightForWidth());
    brushPB->setSizePolicy(sizePolicy2);
    brushPB->setBaseSize(QSize(50, 16));
    brushPB->setCheckable(true);
    brushPB->setChecked(true);

    horizontalLayout_2->addWidget(brushPB);


    verticalLayout->addLayout(horizontalLayout_2);

    line = new QFrame(verticalLayoutWidget);
    line->setObjectName(QString::fromUtf8("line"));
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    verticalLayout->addWidget(line);

    label_24 = new QLabel(verticalLayoutWidget);
    label_24->setObjectName(QString::fromUtf8("label_24"));
    sizePolicy.setHeightForWidth(label_24->sizePolicy().hasHeightForWidth());
    label_24->setSizePolicy(sizePolicy);
    label_24->setAlignment(Qt::AlignCenter);

    verticalLayout->addWidget(label_24);

    InnerTextCHK = new QCheckBox(verticalLayoutWidget);
    InnerTextCHK->setObjectName(QString::fromUtf8("InnerTextCHK"));

    verticalLayout->addWidget(InnerTextCHK);

    horizontalLayout_3 = new QHBoxLayout();
    horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
    label_5 = new QLabel(verticalLayoutWidget);
    label_5->setObjectName(QString::fromUtf8("label_5"));

    horizontalLayout_3->addWidget(label_5);

    horizontalSpacer_3 = new QSpacerItem(100, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_3->addItem(horizontalSpacer_3);

    texturePB = new QPushButton(verticalLayoutWidget);
    texturePB->setObjectName(QString::fromUtf8("texturePB"));
    texturePB->setEnabled(false);
    texturePB->setCheckable(true);

    horizontalLayout_3->addWidget(texturePB);


    verticalLayout->addLayout(horizontalLayout_3);

    horizontalLayout_15 = new QHBoxLayout();
    horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
    label_19 = new QLabel(verticalLayoutWidget);
    label_19->setObjectName(QString::fromUtf8("label_19"));

    horizontalLayout_15->addWidget(label_19);

    horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_15->addItem(horizontalSpacer_11);

    label_20 = new QLabel(verticalLayoutWidget);
    label_20->setObjectName(QString::fromUtf8("label_20"));

    horizontalLayout_15->addWidget(label_20);

    horizontalSlider = new QSlider(verticalLayoutWidget);
    horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
    horizontalSlider->setMaximum(4);
    horizontalSlider->setSliderPosition(2);
    horizontalSlider->setOrientation(Qt::Horizontal);

    horizontalLayout_15->addWidget(horizontalSlider);

    label_21 = new QLabel(verticalLayoutWidget);
    label_21->setObjectName(QString::fromUtf8("label_21"));

    horizontalLayout_15->addWidget(label_21);


    verticalLayout->addLayout(horizontalLayout_15);

    checkBox_4 = new QCheckBox(verticalLayoutWidget);
    checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));

    verticalLayout->addWidget(checkBox_4);

    pageStack->addWidget(page_6);
    page_7 = new QWidget();
    page_7->setObjectName(QString::fromUtf8("page_7"));
    label_25 = new QLabel(page_7);
    label_25->setObjectName(QString::fromUtf8("label_25"));
    label_25->setGeometry(QRect(60, 50, 181, 19));
    checkBox_5 = new QCheckBox(page_7);
    checkBox_5->setObjectName(QString::fromUtf8("checkBox_5"));
    checkBox_5->setGeometry(QRect(50, 80, 111, 23));
    checkBox_6 = new QCheckBox(page_7);
    checkBox_6->setObjectName(QString::fromUtf8("checkBox_6"));
    checkBox_6->setGeometry(QRect(50, 110, 301, 23));
    spinBox_5 = new QSpinBox(page_7);
    spinBox_5->setObjectName(QString::fromUtf8("spinBox_5"));
    spinBox_5->setGeometry(QRect(160, 180, 62, 29));
    label_26 = new QLabel(page_7);
    label_26->setObjectName(QString::fromUtf8("label_26"));
    label_26->setGeometry(QRect(20, 180, 141, 19));
    pageStack->addWidget(page_7);
    page_2 = new QWidget();
    page_2->setObjectName(QString::fromUtf8("page_2"));
    checkBox_7 = new QCheckBox(page_2);
    checkBox_7->setObjectName(QString::fromUtf8("checkBox_7"));
    checkBox_7->setGeometry(QRect(80, 90, 281, 23));
    checkBox_8 = new QCheckBox(page_2);
    checkBox_8->setObjectName(QString::fromUtf8("checkBox_8"));
    checkBox_8->setGeometry(QRect(70, 130, 281, 23));
    checkBox_9 = new QCheckBox(page_2);
    checkBox_9->setObjectName(QString::fromUtf8("checkBox_9"));
    checkBox_9->setGeometry(QRect(80, 50, 141, 25));
    checkBox_10 = new QCheckBox(page_2);
    checkBox_10->setObjectName(QString::fromUtf8("checkBox_10"));
    checkBox_10->setGeometry(QRect(80, 170, 341, 25));
    pageStack->addWidget(page_2);

    Containerhor->addWidget(pageStack);

    layoutWidget_2 = new QWidget(SettingsDialog);
    layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
    layoutWidget_2->setGeometry(QRect(10, 420, 581, 31));
    _2 = new QHBoxLayout(layoutWidget_2);
    _2->setObjectName(QString::fromUtf8("_2"));
    _2->setContentsMargins(0, 0, 0, 0);
    spacerbas = new QSpacerItem(126, 8, QSizePolicy::Expanding, QSizePolicy::Minimum);

    _2->addItem(spacerbas);

    okButton = new QPushButton(layoutWidget_2);
    okButton->setObjectName(QString::fromUtf8("okButton"));

    _2->addWidget(okButton);

    cancelButton = new QPushButton(layoutWidget_2);
    cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

    _2->addWidget(cancelButton);


#ifndef QT_NO_SHORTCUT
    label_3->setBuddy(spinBox);
    label_8->setBuddy(spinBox);
    label_9->setBuddy(spinBox_2);
    label_10->setBuddy(spinBox_3);
    label_11->setBuddy(toolButton);
    label_12->setBuddy(textEdit);
    label_13->setBuddy(textEdit_2);
    label_18->setBuddy(checkBox_2);
    label_6->setBuddy(fontCB);
    label_7->setBuddy(fontSizeSpin);
    penLB_3->setBuddy(penPB_5);
    label_17->setBuddy(leadRadiusSB);
    label_2->setBuddy(leadAngleSB);
    label_15->setBuddy(minLeadDistSB);
    label_23->setBuddy(penPB_4);
    label_22->setBuddy(penPB_3);
    label_14->setBuddy(penPB_2);
    penLB->setBuddy(penPB);
    label_16->setBuddy(spinBox_4);
    brushLB->setBuddy(brushPB);
    label_5->setBuddy(texturePB);
    label_19->setBuddy(horizontalSlider);
    label_26->setBuddy(spinBox_5);
#endif // QT_NO_SHORTCUT

    QWidget::setTabOrder(InnerColorCHK, brushPB);
    QWidget::setTabOrder(brushPB, InnerTextCHK);
    QWidget::setTabOrder(InnerTextCHK, texturePB);
    QWidget::setTabOrder(texturePB, okButton);
    QWidget::setTabOrder(okButton, cancelButton);

    retranslateUi(SettingsDialog);
    QObject::connect(pageList, SIGNAL(currentRowChanged(int)), pageStack, SLOT(setCurrentIndex(int)));
    QObject::connect(cancelButton, SIGNAL(clicked()), SettingsDialog, SLOT(close()));
    QObject::connect(okButton, SIGNAL(clicked()), SettingsDialog, SLOT(save()));
    QObject::connect(InnerColorCHK, SIGNAL(toggled(bool)), brushPB, SLOT(setEnabled(bool)));
    QObject::connect(InnerTextCHK, SIGNAL(toggled(bool)), texturePB, SLOT(setEnabled(bool)));
    QObject::connect(InnerTextCHK_2, SIGNAL(toggled(bool)), fontCB, SLOT(setEnabled(bool)));
    QObject::connect(InnerTextCHK_2, SIGNAL(toggled(bool)), fontSizeSpin, SLOT(setEnabled(bool)));
    QObject::connect(InnerTextCHK_2, SIGNAL(toggled(bool)), penPB_5, SLOT(setEnabled(bool)));
    QObject::connect(checkBox_3, SIGNAL(toggled(bool)), penPB_4, SLOT(setEnabled(bool)));

    pageList->setCurrentRow(-1);
    pageStack->setCurrentIndex(5);


    QMetaObject::connectSlotsByName(SettingsDialog);
    } // setupUi

    void retranslateUi(QWidget *SettingsDialog)
    {
    SettingsDialog->setWindowTitle(QApplication::translate("SettingsDialog", "Camnest Settings", 0, QApplication::UnicodeUTF8));

    const bool __sortingEnabled = pageList->isSortingEnabled();
    pageList->setSortingEnabled(false);
    pageList->item(0)->setText(QApplication::translate("SettingsDialog", "G code", 0, QApplication::UnicodeUTF8));
    pageList->item(1)->setText(QApplication::translate("SettingsDialog", "Fichiers", 0, QApplication::UnicodeUTF8));
    pageList->item(2)->setText(QApplication::translate("SettingsDialog", "Lead-in/out", 0, QApplication::UnicodeUTF8));
    pageList->item(3)->setText(QApplication::translate("SettingsDialog", "Autres", 0, QApplication::UnicodeUTF8));
    pageList->item(4)->setText(QApplication::translate("SettingsDialog", "Couleur/police", 0, QApplication::UnicodeUTF8));
    pageList->item(5)->setText(QApplication::translate("SettingsDialog", "Controle", 0, QApplication::UnicodeUTF8));
    pageList->item(6)->setText(QApplication::translate("SettingsDialog", "Animation", 0, QApplication::UnicodeUTF8));
    pageList->item(7)->setText(QApplication::translate("SettingsDialog", "Preview", 0, QApplication::UnicodeUTF8));

    pageList->setSortingEnabled(__sortingEnabled);
    label_3->setText(QApplication::translate("SettingsDialog", "Home :", 0, QApplication::UnicodeUTF8));
    label_8->setText(QApplication::translate("SettingsDialog", "X", 0, QApplication::UnicodeUTF8));
    label_9->setText(QApplication::translate("SettingsDialog", "Y", 0, QApplication::UnicodeUTF8));
    label_10->setText(QApplication::translate("SettingsDialog", "Z", 0, QApplication::UnicodeUTF8));
    label_4->setText(QApplication::translate("SettingsDialog", "Tolerance", 0, QApplication::UnicodeUTF8));
    checkBox->setText(QApplication::translate("SettingsDialog", "Plamsa/Laser cutter mode:", 0, QApplication::UnicodeUTF8));
    label_11->setText(QApplication::translate("SettingsDialog", "Post-Processor file :", 0, QApplication::UnicodeUTF8));
    toolButton->setText(QApplication::translate("SettingsDialog", "...", 0, QApplication::UnicodeUTF8));
    label_12->setText(QApplication::translate("SettingsDialog", "File header :", 0, QApplication::UnicodeUTF8));
    label_13->setText(QApplication::translate("SettingsDialog", "File Footer :", 0, QApplication::UnicodeUTF8));
    label_18->setText(QApplication::translate("SettingsDialog", "Allow item moving :", 0, QApplication::UnicodeUTF8));
    checkBox_2->setText(QApplication::translate("SettingsDialog", "CheckBox", 0, QApplication::UnicodeUTF8));
    InnerTextCHK_2->setText(QApplication::translate("SettingsDialog", "Number Loops", 0, QApplication::UnicodeUTF8));
    label_6->setText(QApplication::translate("SettingsDialog", "Font :", 0, QApplication::UnicodeUTF8));
    label_7->setText(QApplication::translate("SettingsDialog", "Size :", 0, QApplication::UnicodeUTF8));
    penLB_3->setText(QApplication::translate("SettingsDialog", "Text Color :", 0, QApplication::UnicodeUTF8));
    penPB_5->setText(QApplication::translate("SettingsDialog", "Set Color", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("SettingsDialog", "Lead distance:", 0, QApplication::UnicodeUTF8));

#ifndef QT_NO_WHATSTHIS
    label_17->setWhatsThis(QApplication::translate("SettingsDialog", "This is only for Graphical representation of the laser beam, it won't affect the Generated code.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS

    label_17->setText(QApplication::translate("SettingsDialog", "Lead Radius:", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("SettingsDialog", "Circle Lead Angle:", 0, QApplication::UnicodeUTF8));

#ifndef QT_NO_WHATSTHIS
    label_15->setWhatsThis(QApplication::translate("SettingsDialog", "If a part contains a hole, i.e a circular hole, which radius is less than the supplied value an error is emitted as the hole can't be properly cut.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS

    label_15->setText(QApplication::translate("SettingsDialog", "Minimal lead distance:", 0, QApplication::UnicodeUTF8));
    checkBox_3->setText(QApplication::translate("SettingsDialog", "Show Arrow", 0, QApplication::UnicodeUTF8));
    label_23->setText(QApplication::translate("SettingsDialog", "Arrow Color :", 0, QApplication::UnicodeUTF8));
    penPB_4->setText(QApplication::translate("SettingsDialog", "Set Color", 0, QApplication::UnicodeUTF8));
    label_22->setText(QApplication::translate("SettingsDialog", "Lead Out Color :", 0, QApplication::UnicodeUTF8));
    penPB_3->setText(QApplication::translate("SettingsDialog", "Set Color", 0, QApplication::UnicodeUTF8));
    label_14->setText(QApplication::translate("SettingsDialog", "Lead In Color :", 0, QApplication::UnicodeUTF8));
    penPB_2->setText(QApplication::translate("SettingsDialog", "Set Color", 0, QApplication::UnicodeUTF8));
    penLB->setText(QApplication::translate("SettingsDialog", "Part Outline :", 0, QApplication::UnicodeUTF8));
    penPB->setText(QApplication::translate("SettingsDialog", "Set Color", 0, QApplication::UnicodeUTF8));
    label_16->setText(QApplication::translate("SettingsDialog", "Pen width :", 0, QApplication::UnicodeUTF8));
    InnerColorCHK->setText(QApplication::translate("SettingsDialog", "Colorize Part inner", 0, QApplication::UnicodeUTF8));
    brushLB->setText(QApplication::translate("SettingsDialog", "Part Inner :", 0, QApplication::UnicodeUTF8));
    brushPB->setText(QApplication::translate("SettingsDialog", "Set Color", 0, QApplication::UnicodeUTF8));
    label_24->setText(QApplication::translate("SettingsDialog", "Advanced Features ", 0, QApplication::UnicodeUTF8));
    InnerTextCHK->setText(QApplication::translate("SettingsDialog", "Texturize Part inner", 0, QApplication::UnicodeUTF8));
    label_5->setText(QApplication::translate("SettingsDialog", "Inner Texture :", 0, QApplication::UnicodeUTF8));
    texturePB->setText(QApplication::translate("SettingsDialog", "Set Texture", 0, QApplication::UnicodeUTF8));
    label_19->setText(QApplication::translate("SettingsDialog", "Rendering Quality :", 0, QApplication::UnicodeUTF8));
    label_20->setText(QApplication::translate("SettingsDialog", "Low", 0, QApplication::UnicodeUTF8));
    label_21->setText(QApplication::translate("SettingsDialog", "High", 0, QApplication::UnicodeUTF8));
    checkBox_4->setText(QApplication::translate("SettingsDialog", "Use OpenGl Acceleration", 0, QApplication::UnicodeUTF8));
    label_25->setText(QApplication::translate("SettingsDialog", "Show Warnings for:", 0, QApplication::UnicodeUTF8));
    checkBox_5->setText(QApplication::translate("SettingsDialog", "Open Loops", 0, QApplication::UnicodeUTF8));
    checkBox_6->setText(QApplication::translate("SettingsDialog", "Duplicate Entities (drawing corruption)", 0, QApplication::UnicodeUTF8));
    label_26->setText(QApplication::translate("SettingsDialog", "Drawing tolerance :", 0, QApplication::UnicodeUTF8));
    checkBox_7->setText(QApplication::translate("SettingsDialog", "Confirmbefore clearing scene", 0, QApplication::UnicodeUTF8));
    checkBox_8->setText(QApplication::translate("SettingsDialog", "Confirm before quiting", 0, QApplication::UnicodeUTF8));

#ifndef QT_NO_WHATSTHIS
    checkBox_9->setWhatsThis(QApplication::translate("SettingsDialog", "If enabled, parts are only rendered for view. G-code generation is thus disabled.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS

    checkBox_9->setText(QApplication::translate("SettingsDialog", "Viewer Only Mode", 0, QApplication::UnicodeUTF8));
    checkBox_10->setText(QApplication::translate("SettingsDialog", "Auto zoom fit when inserting part to scene", 0, QApplication::UnicodeUTF8));
    okButton->setText(QApplication::translate("SettingsDialog", "OK", 0, QApplication::UnicodeUTF8));
    cancelButton->setText(QApplication::translate("SettingsDialog", "Cancel", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(SettingsDialog);
    } // retranslateUi

};

namespace Ui {
    class SettingsDialog: public Ui_SettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H
