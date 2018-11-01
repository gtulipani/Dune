#include <QApplication>
#include <Editor.h>

int main(int argc, char *argv[]) {
	// Clase que contiene el loop principal
	QApplication app(argc, argv);
	// Instancio el greeter
	Editor editor;
	editor.show();
	// Arranca el loop de la UI
	return app.exec();
}
