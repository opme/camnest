#include "partslistmodel.h"
// C++ Implementation: partslistmodel
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
	 int PartsListModel::rowCount(const QModelIndex &parent) const {
     return stringList.count();
	}
	 
	QVariant PartsListModel::data(const QModelIndex &index, int role) const {
     if (!index.isValid())
         return QVariant();
     if (index.row() >= stringList.size())
         return QVariant();
     if (role == Qt::DisplayRole)
         return stringList.at(index.row());
     else
         return QVariant();
	}
	
	bool PartsListModel::insertRows(int position, int rows, const QModelIndex &parent)
 {
     beginInsertRows(QModelIndex(), position, position+rows-1);

     for (int row = 0; row < rows; ++row) {
         stringList.insert(position, "");
     }

     endInsertRows();
     return true;
 }
 	///@fixme make this inside listView and not Model
 	///bool PartsListModel::removePart(QVariant partStr){
	///for (int row = 0; row < rowCount(); ++row) {
	//qDebug()<<data(index(row),0);
		///if (data(index(row),0)==partStr) {
		///	qDebug()<<"removing part at index "<<row;
		///	return removeRows(row,1);
		///	}
		///}
	/// return false;
	///}
 
	bool PartsListModel::removeRows(int position, int rows, const QModelIndex &parent)
 {
     beginRemoveRows(QModelIndex(), position, position+rows-1);

     for (int row = 0; row < rows; ++row) {
         stringList.removeAt(position);
     }

     endRemoveRows();
     return true;
 }
	
	//Qt::ItemFlags PartsListModel::flags(const QModelIndex &index) const {
    // if (!index.isValid())     return Qt::ItemIsEnabled;
    // return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
	//}
	
	
	bool PartsListModel::setData(const QModelIndex &index,const QVariant &value, int role){
	qDebug()<<index<<value;
     if (index.isValid() && role == Qt::EditRole) {
         stringList.replace(index.row(), value.toString());
         emit dataChanged(index, index);
         return true;
     }
	 else {
		 qDebug()<<"invalid index";
		 return false;
		}
	}
	
	