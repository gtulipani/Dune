#ifndef __TERRAINCELLWIDGET_H__
#define __TERRAINCELLWIDGET_H__

#include <QtWidgets/QTableWidgetItem>

class TerrainCellWidget : public QTableWidgetItem {
public:
	explicit TerrainCellWidget(std::string terrain, int type = UserType);

	TerrainCellWidget(std::string terrain, const QString &text, int type =
	UserType);

	TerrainCellWidget(std::string terrain, const QIcon &icon, const QString
	&text, int type = UserType);

	~TerrainCellWidget();

private:
	std::string terrain;
};

#endif //__TERRAINCELLWIDGET_H__
