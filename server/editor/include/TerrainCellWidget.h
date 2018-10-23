#ifndef DUNE_TERRAINCELLWIDGET_H
#define DUNE_TERRAINCELLWIDGET_H

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

#endif //DUNE_TERRAINCELLWIDGET_H
