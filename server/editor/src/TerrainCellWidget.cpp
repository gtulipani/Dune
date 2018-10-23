#include <utility>
#include "TerrainCellWidget.h"

TerrainCellWidget::TerrainCellWidget(std::string terrain, int type) :
		QTableWidgetItem(type), terrain(std::move(terrain)) {}

TerrainCellWidget::TerrainCellWidget(std::string terrain, const QString &text,
									 int type) :
		QTableWidgetItem(text, type),
		terrain(std::move(terrain)) {}

TerrainCellWidget::TerrainCellWidget(std::string terrain, const QIcon &icon,
									 const QString &text, int type) :
		QTableWidgetItem(icon, text, type),
		terrain(std::move(terrain)) {}

TerrainCellWidget::~TerrainCellWidget() {}
