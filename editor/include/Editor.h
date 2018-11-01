#ifndef __EDITOR_H__
#define __EDITOR_H__

#include <QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

class Editor : public QWidget {
public:
	explicit Editor(QWidget *parent = 0);

private:
	std::string terrainToFill;
	void connectEvents();

	slots
	void onMapCellClicked(QTableWidget *item, int row, int column);
	void onTerrainClicked(QPushButton *terrainButton);
};

#endif //__EDITOR_H__
