 /****************************************************************************
 **
 ** Copyright (C) 2008 Nokia Corporation and/or its subsidiary(-ies).
 ** Contact: Qt Software Information (qt-info@nokia.com)
 **
 ** This file is part of the example classes of the Qt Toolkit.
 **
 ** Commercial Usage
 ** Licensees holding valid Qt Commercial licenses may use this file in
 ** accordance with the Qt Commercial License Agreement provided with the
 ** Software or, alternatively, in accordance with the terms contained in
 ** a written agreement between you and Nokia.
 **
 **
 ** GNU General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU
 ** General Public License versions 2.0 or 3.0 as published by the Free
 ** Software Foundation and appearing in the file LICENSE.GPL included in
 ** the packaging of this file.  Please review the following information
 ** to ensure GNU General Public Licensing requirements will be met:
 ** http://www.fsf.org/licensing/licenses/info/GPLv2.html and
 ** http://www.gnu.org/copyleft/gpl.html.  In addition, as a special
 ** exception, Nokia gives you certain additional rights. These rights
 ** are described in the Nokia Qt GPL Exception version 1.3, included in
 ** the file GPL_EXCEPTION.txt in this package.
 **
 ** Qt for Windows(R) Licensees
 ** As a special exception, Nokia, as the sole copyright holder for Qt
 ** Designer, grants users of the Qt/Eclipse Integration plug-in the
 ** right for the Qt/Eclipse Integration to link to functionality
 ** provided by Qt Designer and its related libraries.
 **
 ** If you are unsure which license is appropriate for your use, please
 ** contact the sales department at qt-sales@nokia.com.
 **
 ****************************************************************************/

 #include <QtGui>

#include <math.h>
#include "renderpath.h"
#include "window.h"
#include "dl_dxf.h"
#include "dl_creationadapter.h"
#include "test_creationclass.h"


//const float Pi = 3.14159265358979323846f;
 
 
 Window::Window()
 {
     QPainterPath rectPath;
     rectPath.moveTo(20.0, 30.0);
     rectPath.lineTo(80.0, 30.0);
     rectPath.lineTo(80.0, 70.0);
     rectPath.lineTo(20.0, 70.0);
     rectPath.closeSubpath();
	 
     renderAreas = new RenderArea(rectPath);
     
     //Q_ASSERT(NumRenderAreas == 9);
	 loadFileButton = new QPushButton;
	 
     fillRuleComboBox = new QComboBox;
     fillRuleComboBox->addItem(tr("Odd Even"), Qt::OddEvenFill);
     fillRuleComboBox->addItem(tr("Winding"), Qt::WindingFill);

     fillRuleLabel = new QLabel(tr("Fill &Rule:"));
     fillRuleLabel->setBuddy(fillRuleComboBox);

     fillColor1ComboBox = new QComboBox;
     populateWithColors(fillColor1ComboBox);
     fillColor1ComboBox->setCurrentIndex(
     fillColor1ComboBox->findText("mediumslateblue"));

     fillColor2ComboBox = new QComboBox;
     populateWithColors(fillColor2ComboBox);
     fillColor2ComboBox->setCurrentIndex(
     fillColor2ComboBox->findText("cornsilk"));

     fillGradientLabel = new QLabel(tr("&Fill Gradient:"));
     fillGradientLabel->setBuddy(fillColor1ComboBox);

     fillToLabel = new QLabel(tr("to"));
     fillToLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

     penWidthSpinBox = new QSpinBox;
     penWidthSpinBox->setRange(0, 20);

     penWidthLabel = new QLabel(tr("&Pen Width:"));
     penWidthLabel->setBuddy(penWidthSpinBox);

     penColorComboBox = new QComboBox;
     populateWithColors(penColorComboBox);
     penColorComboBox->setCurrentIndex(
     penColorComboBox->findText("darkslateblue"));

     penColorLabel = new QLabel(tr("Pen &Color:"));
     penColorLabel->setBuddy(penColorComboBox);

     rotationAngleSpinBox = new QSpinBox;
     rotationAngleSpinBox->setRange(0, 359);
     rotationAngleSpinBox->setWrapping(true);
     rotationAngleSpinBox->setSuffix("\xB0");

     rotationAngleLabel = new QLabel(tr("&Rotation Angle:"));
     rotationAngleLabel->setBuddy(rotationAngleSpinBox);

     connect(fillRuleComboBox, SIGNAL(activated(int)),
             this, SLOT(fillRuleChanged()));
     connect(fillColor1ComboBox, SIGNAL(activated(int)),
             this, SLOT(fillGradientChanged()));
     connect(fillColor2ComboBox, SIGNAL(activated(int)),
             this, SLOT(fillGradientChanged()));
     connect(penColorComboBox, SIGNAL(activated(int)),
             this, SLOT(penColorChanged()));
			 
			connect( loadFileButton, SIGNAL (clicked()),this, SLOT(readDxfFile()) );

     //for (int i = 0; i < NumRenderAreas; ++i) {
         connect(penWidthSpinBox, SIGNAL(valueChanged(int)),
                 renderAreas, SLOT(setPenWidth(int)));
         connect(rotationAngleSpinBox, SIGNAL(valueChanged(int)),
                 renderAreas, SLOT(setRotationAngle(int)));
     //}

   

     QGridLayout *mainLayout = new QGridLayout;
     mainLayout->addWidget(renderAreas, 0, 0, 1, 4);
	
     mainLayout->addWidget(fillRuleLabel, 1, 0);
     mainLayout->addWidget(fillRuleComboBox, 1, 1, 1, 3);
     mainLayout->addWidget(fillGradientLabel, 2, 0);
     mainLayout->addWidget(fillColor1ComboBox, 2, 1);
     mainLayout->addWidget(fillToLabel, 2, 2);
     mainLayout->addWidget(fillColor2ComboBox, 2, 3);
     mainLayout->addWidget(penWidthLabel, 3, 0);
     mainLayout->addWidget(penWidthSpinBox, 3, 1, 1, 3);
     mainLayout->addWidget(penColorLabel, 4, 0);
     mainLayout->addWidget(penColorComboBox, 4, 1, 1, 3);
     mainLayout->addWidget(rotationAngleLabel, 5, 0);
     mainLayout->addWidget(rotationAngleSpinBox, 5, 1, 1, 3);
	 mainLayout->addWidget(loadFileButton, 6, 1);
     setLayout(mainLayout);

     fillRuleChanged();
     fillGradientChanged();
     penColorChanged();
     penWidthSpinBox->setValue(2);

 }

 void Window::fillRuleChanged()
 {
     Qt::FillRule rule = (Qt::FillRule)currentItemData(fillRuleComboBox).toInt();

     
         renderAreas->setFillRule(rule);
 }

 void Window::fillGradientChanged()
 {
     QColor color1 = qvariant_cast<QColor>(currentItemData(fillColor1ComboBox));
     QColor color2 = qvariant_cast<QColor>(currentItemData(fillColor2ComboBox));

     
         renderAreas->setFillGradient(color1, color2);
 }

 void Window::penColorChanged()
 {
     QColor color = qvariant_cast<QColor>(currentItemData(penColorComboBox));

     
         renderAreas->setPenColor(color);
 }

 void Window::populateWithColors(QComboBox *comboBox)
 {
     QStringList colorNames = QColor::colorNames();
     foreach (QString name, colorNames)
         comboBox->addItem(name, QColor(name));
 }

 QVariant Window::currentItemData(QComboBox *comboBox)
 {
	 return comboBox->itemData(comboBox->currentIndex());
 }
 
 


void Window::readDxfFile() {
	  // get the dxf entities
	 QString file = QFileDialog::getOpenFileName(0,"Find Files", QDir::currentPath(),"DXF Files (*.dxf)");
     if (!file.isEmpty()) {
	  qDebug() << "File chosen " << file ;
	 }	
     // Load DXF file into memory:
     std::cout << "Reading file " << file.toStdString() << "...\n";
     Test_CreationClass* creationClass = new Test_CreationClass();
     DL_Dxf* dxf = new DL_Dxf();
     if (!dxf->in(file.toStdString(), creationClass)) { // if file open failed
        std::cerr << file.toStdString() << " could not be opened.\n";
        return;
     }
     delete dxf;
     delete creationClass;
}
 