#include <iostream>
#include <TerrainCellWidget.h>
#include "Editor.h"
#include "ui_Editor.h"

Editor::Editor(QWidget *parent) : QWidget(parent) {
	// Instancio la configuracion generada por el designer y uic
	Ui::Editor editor;
	// Configuro este widget para use esa configuracion
	editor.setupUi(this);
	connectEvents();
}

void Editor::onMapCellClicked(QTableWidget *table, int row, int column) {
	std::cout << "onMapCellClicked()" << std::endl;
	if (!terrainToFill.empty()) {
		std::cout << "Terrain not empty!" << std::endl;
		table->setItem(row, column, new TerrainCellWidget(terrainToFill, "0"));
	}

}

void Editor::onTerrainClicked(QPushButton *terrainButton) {
	std::cout << "onTerrainClicked()" << std::endl;
	terrainButton->setEnabled(false);
	terrainToFill = "Rock";
}

void Editor::connectEvents() {
	// Conecto el evento del boton
	auto *rockButton = findChild<QPushButton *>("rockButton");
	auto *mapTable = findChild<QTableWidget *>("mapTable");

	QObject::connect(rockButton, &QPushButton::clicked, [this, rockButton]() {
		onTerrainClicked(rockButton);
	});

	QObject::connect(mapTable, &QTableWidget::clicked, [this, mapTable]
			(const QModelIndex &index) {
		onMapCellClicked(mapTable, index.row(), index.column());
	});
}
