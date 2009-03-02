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

 #include "renderpath.h"

 RenderArea::RenderArea(const QPainterPath &path, QWidget *parent)
     : QWidget(parent), path(path)
 {
     penWidth = 1;
     rotationAngle = 0;
     setBackgroundRole(QPalette::Base);
 }

 QSize RenderArea::minimumSizeHint() const
 {
     return QSize(50, 50);
 }

 QSize RenderArea::sizeHint() const
 {
     return QSize(300, 300);
 }

 void RenderArea::setFillRule(Qt::FillRule rule)
 {
     path.setFillRule(rule);
     update();
 }

 void RenderArea::setFillGradient(const QColor &color1, const QColor &color2)
 {
     fillColor1 = color1;
     fillColor2 = color2;
     update();
 }

 void RenderArea::setPenWidth(int width)
 {
     penWidth = width;
     update();
 }

 void RenderArea::setPenColor(const QColor &color)
 {
     penColor = color;
     update();

	 
 }

 void RenderArea::setRotationAngle(int degrees)
 {
     rotationAngle = degrees;
     update();
 }

 void RenderArea::paintEvent(QPaintEvent *)
 {
     QPainter painter(this);
	 painter.setRenderHint(QPainter::Antialiasing);
     painter.scale(width() / 100.0, height() / 100.0);
     painter.translate(50.0, 50.0);
     painter.rotate(-rotationAngle);
     painter.translate(-50.0, -50.0);

     painter.setPen(QPen(penColor, penWidth, Qt::SolidLine, Qt::RoundCap,Qt::RoundJoin));
     QLinearGradient gradient(0, 0, 0, 100);
     gradient.setColorAt(0.0, fillColor1);
     gradient.setColorAt(1.0, fillColor2);
     painter.setBrush(gradient);
     painter.drawPath(path);
 }