#include <Windows.h>
#include <QApplication>
#include "dialog.hpp"

//int WINAPI WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
//{
//  int     argc = __argc;
//  char ** argv = __argv;

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  Dialog dlg;
  dlg.show();

  return app.exec();
}