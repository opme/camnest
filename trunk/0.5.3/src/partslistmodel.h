#ifndef PARTSLISTMODEL_H
#define PARTSLISTMODEL_H
//
// C++ Interface: partslistmodel
//
// Description: 
//
//
// Author: invite <invite@invite-laptop>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include <QtGui>
#include <QWidget>
	  class PartsListModel : public QAbstractListModel{
     Q_OBJECT
	 public:
     PartsListModel(const QStringList &strings, QObject *parent = 0):
		   QAbstractListModel(parent), stringList(strings) {
     
     }
     int rowCount(const QModelIndex &parent = QModelIndex()) const;
     QVariant data(const QModelIndex &index, int role) const;
	 //Qt::ItemFlags flags(const QModelIndex &index) const;
     bool setData(const QModelIndex &index, const QVariant &value,int role = Qt::EditRole);
	 bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
     bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());
     ///bool removePart(QVariant data);
	 private:
     QStringList stringList;
	};
  
  #endif 	 